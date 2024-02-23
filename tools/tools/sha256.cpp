#include "sha256.hpp"

const bool SHA256::IS_LITTLE_ENDIAN = CHECK_LITTLE_ENDIAN();

const uint32_t SHA256::CONSTANTS[64] = {
    0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
    0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
    0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
    0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
    0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
    0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
    0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
    0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
};

SHA256::SHA256()
{
    Initialize();
}

std::string SHA256::Hashing(const Ptr message, size_t size)
{
    SHA256 hasher;
    hasher.Compress(message, static_cast<uint32_t>(size));
    return std::string(static_cast<char*>(hasher.Final(message)), DIGEST_VALUE_LEN);
}

std::string SHA256::Encrypt(const Ptr message, size_t msgSize, const Ptr salt, size_t saltSize, ssize_t stretching)
{
    std::string result     = std::string(static_cast<char*>(message), msgSize);
    std::string saltString = std::string(static_cast<char*>(salt), saltSize);
    size_t      saltedSize = msgSize + saltSize;

    SHA256 hasher;

    result += saltString;
    hasher.Compress(result.c_str(), static_cast<uint32_t>(saltedSize));
    result = std::string(static_cast<char*>(hasher.Final(message)), DIGEST_VALUE_LEN);

    saltedSize = 32 + saltSize;
    while(--stretching >= 0) {
        result += saltString;
        hasher.Initialize();
        hasher.Compress(result.c_str(), static_cast<uint32_t>(saltedSize));
        result = std::string(static_cast<char*>(hasher.Final(result.c_str())), DIGEST_VALUE_LEN);
    }

    return result;
}

void SHA256::Initialize()
{
    state.chainVar[0] = 0x6A09E667;
    state.chainVar[1] = 0xBB67AE85;
    state.chainVar[2] = 0x3C6EF372;
    state.chainVar[3] = 0xA54FF53A;
    state.chainVar[4] = 0x510E527F;
    state.chainVar[5] = 0x9B05688C;
    state.chainVar[6] = 0x1F83D9AB;
    state.chainVar[7] = 0x5BE0CD19;

    state.highLength = 0;
    state.lowLength  = 0;
    state.remainNum  = 0;
}

void SHA256::Compress(Ptr message, uint32_t size)
{
    uint32_t remainBuffer = state.remainNum;

    if((state.lowLength += (size << 3)) < 0) {
        ++state.highLength;
    }
    state.highLength += (size >> 29);

    uint32_t flag = size + remainBuffer;
    while(flag >= DIGEST_BLOCK_LEN) {
        memcpy(state.buffer + remainBuffer, message, static_cast<size_t>(DIGEST_BLOCK_LEN));
        Transform(reinterpret_cast<uint32_t*>(state.buffer), state.chainVar);
        message      += DIGEST_BLOCK_LEN - remainBuffer;
        size         -= DIGEST_BLOCK_LEN - remainBuffer;
        remainBuffer  = 0;

        flag = size + remainBuffer;
    }

    memcpy(state.buffer + remainBuffer, message, size);
    state.remainNum = remainBuffer + size;
}

Block SHA256::Final(Ptr message)
{
    uint32_t index        = (state.lowLength >> 3) % DIGEST_BLOCK_LEN;
    state.buffer[index++] = static_cast<int8_t>(0x80);

    if(index >= DIGEST_BLOCK_LEN - 8) {
        memset(state.buffer + index, 0, DIGEST_BLOCK_LEN - index);
        Transform(reinterpret_cast<uint32_t*>(state.buffer), state.chainVar);
        memset(state.buffer, 0, DIGEST_BLOCK_LEN - 8);
    }

    else {
        int n = DIGEST_BLOCK_LEN - index - 8;
        memset(state.buffer + index, 0, DIGEST_BLOCK_LEN - index - 8);
    }

    if(IS_LITTLE_ENDIAN) {
        state.lowLength  = REVERSE_ENDIAN_32(state.lowLength);
        state.highLength = REVERSE_ENDIAN_32(state.highLength);
    }

    reinterpret_cast<uint32_t*>(state.buffer)[(DIGEST_BLOCK_LEN >> 2) - 2] = state.highLength;
    reinterpret_cast<uint32_t*>(state.buffer)[(DIGEST_BLOCK_LEN >> 2) - 1] = state.lowLength;

    Transform(reinterpret_cast<uint32_t*>(state.buffer), state.chainVar);

    uint32_t* temp;
    Block     digest = { 0 };

    // 32 Byte, unit 4 Byte, loop => 8
    int loop = DIGEST_VALUE_LEN >> 2;

    if(IS_LITTLE_ENDIAN) {
        for(int i = 0; i < loop; ++i) {
            temp    = digest;
            temp[i] = REVERSE_ENDIAN_32(state.chainVar[i]);
        }
    }

    else {
        for(int i = 0; i < loop; ++i) {
            temp    = digest;
            temp[i] = state.chainVar[i];
        }
    }

    return digest;
}

void SHA256::Transform(uint32_t* msg, uint32_t* chainVar)
{
    uint32_t n[8] = { 0 }, t1 = 0, x[64] = { 0 };

    auto fnFF = [this, &t1, &x](uint32_t  a,
                                uint32_t  b,
                                uint32_t  c,
                                uint32_t& d,
                                uint32_t  e,
                                uint32_t  f,
                                uint32_t  g,
                                uint32_t& h,
                                uint32_t  index) {
        t1  = h + Sigma1(e) + Choose(e, f, g) + CONSTANTS[index] + x[index];
        d  += t1;
        h   = t1 + Sigma0(a) + Majority(a, b, c);
    };

    if(IS_LITTLE_ENDIAN) {
        for(int i = 0; i < 16; ++i) {
            x[i] = REVERSE_ENDIAN_32(msg[i]);
        }
    }

    else {
        for(int i = 0; i < 16; ++i) {
            x[i] = msg[i];
        }
    }

    for(int i = 16; i < 64; ++i) {
        int a = i - 2, b = i - 7, c = i - 15, d = i - 16;

        x[i] = RHO1(x[a]) + x[b] + RHO0(x[c]) + x[d];
    }

    for(int i = 0; i < 8; ++i) {
        n[i] = chainVar[i];
    }

    for(int i = 0; i < 64; i += 8) {
        fnFF(n[0], n[1], n[2], n[3], n[4], n[5], n[6], n[7], i + 0);
        fnFF(n[7], n[0], n[1], n[2], n[3], n[4], n[5], n[6], i + 1);
        fnFF(n[6], n[7], n[0], n[1], n[2], n[3], n[4], n[5], i + 2);
        fnFF(n[5], n[6], n[7], n[0], n[1], n[2], n[3], n[4], i + 3);
        fnFF(n[4], n[5], n[6], n[7], n[0], n[1], n[2], n[3], i + 4);
        fnFF(n[3], n[4], n[5], n[6], n[7], n[0], n[1], n[2], i + 5);
        fnFF(n[2], n[3], n[4], n[5], n[6], n[7], n[0], n[1], i + 6);
        fnFF(n[1], n[2], n[3], n[4], n[5], n[6], n[7], n[0], i + 7);
    }

    for(int i = 0; i < 8; ++i) {
        chainVar[i] += n[i];
    }
}

uint32_t SHA256::RR(uint32_t x, uint32_t n)
{
    return SHIFT_ROT_R_UNSIGNED(x, n);
}

uint32_t SHA256::SS(uint32_t x, uint32_t n)
{
    return (x >> n);
}

uint32_t SHA256::Choose(uint32_t x, uint32_t y, uint32_t z)
{
    return ((x & y) ^ ((~x) & z));
}

uint32_t SHA256::Majority(uint32_t x, uint32_t y, uint32_t z)
{
    return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t SHA256::Sigma0(uint32_t x)
{
    return (RR(x, 2) ^ RR(x, 13) ^ RR(x, 22));
}

uint32_t SHA256::Sigma1(uint32_t x)
{
    return (RR(x, 6) ^ RR(x, 11) ^ RR(x, 25));
}

uint32_t SHA256::RHO0(uint32_t x)
{
    return (RR(x, 7) ^ RR(x, 18) ^ SS(x, 3));
}

uint32_t SHA256::RHO1(uint32_t x)
{
    return (RR(x, 17) ^ RR(x, 19) ^ SS(x, 10));
}