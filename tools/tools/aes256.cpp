#include "aes256.hpp"

const uint8_t AES256::S_BOX[] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76, 0xCA, 0x82, 0xC9,
    0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0, 0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F,
    0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15, 0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07,
    0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75, 0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3,
    0x29, 0xE3, 0x2F, 0x84, 0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58,
    0xCF, 0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8, 0x51, 0xA3,
    0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2, 0xCD, 0x0C, 0x13, 0xEC, 0x5F,
    0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73, 0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88,
    0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB, 0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC,
    0x62, 0x91, 0x95, 0xE4, 0x79, 0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A,
    0xAE, 0x08, 0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A, 0x70,
    0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E, 0xE1, 0xF8, 0x98, 0x11,
    0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF, 0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42,
    0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16,
};

const uint8_t AES256::S_BOX_INV[] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB, 0x7C, 0xE3, 0x39,
    0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB, 0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2,
    0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E, 0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76,
    0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25, 0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC,
    0x5D, 0x65, 0xB6, 0x92, 0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D,
    0x84, 0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06, 0xD0, 0x2C,
    0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B, 0x3A, 0x91, 0x11, 0x41, 0x4F,
    0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73, 0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85,
    0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E, 0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62,
    0x0E, 0xAA, 0x18, 0xBE, 0x1B, 0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD,
    0x5A, 0xF4, 0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F, 0x60,
    0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF, 0xA0, 0xE0, 0x3B, 0x4D,
    0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61, 0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6,
    0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D,
};

const uint8_t AES256::ROUND_CONSTANT[] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f,
    0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72,
};

const uint8_t AES256::MIX_COLUMN_TABLE[ROW][COL] = { 0x02, 0x03, 0x01, 0x01, 0x01, 0x02, 0x03, 0x01,
                                                     0x01, 0x01, 0x02, 0x03, 0x03, 0x01, 0x01, 0x02 };

const uint8_t AES256::MIX_COLUMN_TABLE_INV[ROW][COL] = { 0x0E, 0x0B, 0x0D, 0x09, 0x09, 0x0E, 0x0B, 0x0D,
                                                         0x0D, 0x09, 0x0E, 0x0B, 0x0B, 0x0D, 0x09, 0x0E };

std::string AES256::Encrypt(const Ptr& ptr, ssize_t size, const std::string& key)
{
    if(key.size() != AES256::KEY_SIZE_BYTE) {
        throw std::invalid_argument("It doesn't seem to be an encrpyted string.");
    }

    // init
    AES256 aes = AES256();
    aes.KeyScheduling(key.c_str());

    // check size
    uint8_t padding = size % AES256::BLOCK_SIZE; // remaind byte

    // not full
    if(padding) {
        padding = AES256::BLOCK_SIZE - padding;
    }

    std::string result;

    ssize_t index = 0; // Data cursor
    while(size > 0) {
        ssize_t blockSize  = size >= AES256::BLOCK_SIZE ? AES256::BLOCK_SIZE : size; // check remaind size
        size              -= AES256::BLOCK_SIZE;                                     // read complete

        uint8_t buffer[AES256::BLOCK_SIZE]; // 16 byte to encrypt

        std::memcpy(buffer, ptr + index, blockSize);
        if(size <= 0) {
            std::memset(buffer + AES256::BLOCK_SIZE + size, padding, -size); // size is negative
        }
        index += AES256::BLOCK_SIZE; // next

        aes.Encrypt256(buffer); // write to buffer
        result.append(reinterpret_cast<char*>(buffer), AES256::BLOCK_SIZE);
    }

    return result;
}

std::string AES256::Decrypt(const Ptr& ptr, size_t size, const std::string& key, OUT OPT int* padding)
{
    if(size % AES256::BLOCK_SIZE) {
        throw std::invalid_argument("It doesn't seem to be an encrpyted string.");
    }

    if(key.size() != AES256::KEY_SIZE_BYTE) {
        throw std::invalid_argument("Key size is not 32 byte");
    }

    std::string result;

    // Init
    AES256 aes = AES256();
    aes.KeyScheduling(key.c_str());

    for(ssize_t i = 0; i < size; i += AES256::BLOCK_SIZE) {
        uint8_t buffer[AES256::BLOCK_SIZE]; // 16 byte to decrypt

        std::memcpy(buffer, ptr + i, AES256::BLOCK_SIZE);
        aes.Decrypt256(buffer);
        result.append(reinterpret_cast<char*>(buffer), AES256::BLOCK_SIZE);
    }

    // Check Padding
    uint8_t last = result[size - 1]; // get last byte;

    if(padding != nullptr) {
        if(last >= AES256::BLOCK_SIZE) {
            *padding = 0;
        }
        else {
            *padding = last;
        }
    }

    // Delete Padding
    else if(last < AES256::BLOCK_SIZE) {
        while(last-- > 0) {
            result.pop_back();
        }
    }

    return result;
}

void AES256::Encrypt256(OUT Ptr data)
{
    uint8_t* cursor = data;

    // copy
    for(int row = 0; row < 4; ++row) {
        for(int col = 0; col < 4; ++col) {
            stateMatrix[row][col] = cursor[row * COL + col];
        }
    }

    uint8_t* currKey = exKey;

    // round initialization
    AddRoundKey(currKey);
    currKey += BLOCK_SIZE;

    // 13 rounds
    int loop = ROUND_COUNT - 1;
    for(int i = 0; i < loop; ++i) {
        SubBytes();
        ShiftRows();
        MixColumns();
        AddRoundKey(currKey);

        currKey += BLOCK_SIZE;
    }

    // 14, final round
    SubBytes();
    ShiftRows();
    AddRoundKey(currKey);

    // out
    for(int row = 0; row < 4; ++row) {
        for(int col = 0; col < 4; ++col) {
            cursor[row * COL + col] = stateMatrix[row][col];
        }
    }
}

void AES256::Decrypt256(OUT Ptr data)
{
    uint8_t* cursor = data;

    // copy
    for(int row = 0; row < 4; ++row) {
        for(int col = 0; col < 4; ++col) {
            stateMatrix[row][col] = cursor[row * COL + col];
        }
    }

    // reverse
    uint8_t* currKey = exKey + BLOCK_SIZE * ROUND_COUNT;

    // round initialization
    AddRoundKey(currKey);
    ShiftRowsInverse();
    SubBytesInverse();
    currKey -= BLOCK_SIZE;

    // 13 rounds
    int loop = ROUND_COUNT - 1;
    for(int i = 0; i < loop; ++i) {
        AddRoundKey(currKey);
        MixColumnsInverse();
        ShiftRowsInverse();
        SubBytesInverse();

        currKey -= BLOCK_SIZE;
    }

    // 14, final round
    AddRoundKey(currKey);

    // out
    for(int row = 0; row < 4; ++row) {
        for(int col = 0; col < 4; ++col) {
            cursor[row * COL + col] = stateMatrix[row][col];
        }
    }
}

void AES256::KeyScheduling(const Ptr key)
{
    uint8_t* roundKey = key;

    for(int i = 0; i < KEY_SIZE_BYTE; ++i) {
        exKey[i] = roundKey[i];
    }

    int byteGenerated = KEY_SIZE_BYTE; // loop: generated
    int rconIterator  = 1;             // stendard

    while(byteGenerated < EXPANDED_SIZE) {
        uint8_t temp[4] = { 0 }; // 4 byte

        // last 4 byte of extendted key
        for(int i = 0; i < 4; ++i) {
            temp[i] = exKey[byteGenerated - 4 + i];
        }

        // rot word, sub word, round constant
        if(!(byteGenerated % KEY_SIZE_BYTE)) {
            uint8_t byte = temp[0];
            temp[0]      = temp[1];
            temp[1]      = temp[2];
            temp[2]      = temp[3];
            temp[3]      = byte;

            for(int i = 0; i < 4; i++) {
                temp[i] = S_BOX[temp[i]];
            }

            temp[0] ^= ROUND_CONSTANT[rconIterator++];
        }

        // generate => xor
        for(int i = 0; i < 4; i++) {
            exKey[byteGenerated] = exKey[byteGenerated - KEY_SIZE_BYTE] ^ temp[i];
            byteGenerated++;
        }
    }
}

uint8_t AES256::GaloisField(uint8_t l, uint8_t r)
{
    uint8_t result = 0;

    for(int i = 0; i < 8; ++i) {
        if(r & 1) {
            result ^= l;
        }
        uint8_t msb   = l & 0b10000000; // Check carry
        l           <<= 1;
        if(msb) {
            l ^= 0x1B;
        }
        r >>= 1;
    }

    return result;
}

// xor: state matrix ^ current key
void AES256::AddRoundKey(const uint8_t* key)
{
    for(int64_t row = 0; row < ROW; ++row) {
        for(int64_t col = 0; col < COL; ++col) {
            stateMatrix[row][col] ^= key[row * COL + col];
        }
    }
}

void AES256::SubBytes()
{
    for(int64_t row = 0; row < ROW; ++row) {
        for(int64_t col = 0; col < COL; ++col) {
            stateMatrix[row][col] = S_BOX[stateMatrix[row][col]];
        }
    }
}

void AES256::SubBytesInverse()
{
    for(int64_t row = 0; row < ROW; ++row) {
        for(int64_t col = 0; col < COL; ++col) {
            stateMatrix[row][col] = S_BOX_INV[stateMatrix[row][col]];
        }
    }
}

void AES256::ShiftRows()
{
    uint8_t temp;

    // row 2 => shift 1 to left
    temp              = stateMatrix[1][0];
    stateMatrix[1][0] = stateMatrix[1][1];
    stateMatrix[1][1] = stateMatrix[1][2];
    stateMatrix[1][2] = stateMatrix[1][3];
    stateMatrix[1][3] = temp;

    // row 3 => shift 2 to left
    temp              = stateMatrix[2][0];
    stateMatrix[2][0] = stateMatrix[2][2];
    stateMatrix[2][2] = temp;
    temp              = stateMatrix[2][1];
    stateMatrix[2][1] = stateMatrix[2][3];
    stateMatrix[2][3] = temp;

    // row 4 => shift 3 to left
    temp              = stateMatrix[3][0];
    stateMatrix[3][0] = stateMatrix[3][3];
    stateMatrix[3][3] = stateMatrix[3][2];
    stateMatrix[3][2] = stateMatrix[3][1];
    stateMatrix[3][1] = temp;
}

void AES256::ShiftRowsInverse()
{
    uint8_t temp;

    // row 2 => shift 1 to right
    temp              = stateMatrix[1][3];
    stateMatrix[1][3] = stateMatrix[1][2];
    stateMatrix[1][2] = stateMatrix[1][1];
    stateMatrix[1][1] = stateMatrix[1][0];
    stateMatrix[1][0] = temp;

    // row 3 => shift 2 to right
    temp              = stateMatrix[2][2];
    stateMatrix[2][2] = stateMatrix[2][0];
    stateMatrix[2][0] = temp;
    temp              = stateMatrix[2][3];
    stateMatrix[2][3] = stateMatrix[2][1];
    stateMatrix[2][1] = temp;

    // row 4 => shift 3 to right
    temp              = stateMatrix[3][1];
    stateMatrix[3][1] = stateMatrix[3][2];
    stateMatrix[3][2] = stateMatrix[3][3];
    stateMatrix[3][3] = stateMatrix[3][0];
    stateMatrix[3][0] = temp;
}

void AES256::MixColumns()
{
    uint8_t buffer[ROW][COL] = { 0 };

    for(int col = 0; col < COL; col++) {
        for(int row = 0; row < ROW; row++) {

            buffer[row][col] = 0;
            for(int i = 0; i < 4; i++) {
                buffer[row][col] ^= GaloisField(MIX_COLUMN_TABLE[row][i], stateMatrix[i][col]);
            }

        } // end row
    }     // end col

    for(int row = 0; row < ROW; row++) {
        for(int col = 0; col < COL; col++) {
            stateMatrix[row][col] = buffer[row][col];
        }
    }
}

void AES256::MixColumnsInverse()
{
    uint8_t buffer[ROW][COL] = { 0 };

    for(int col = 0; col < COL; col++) {
        for(int row = 0; row < ROW; row++) {

            buffer[row][col] = 0;
            for(int i = 0; i < 4; i++) {
                buffer[row][col] ^= GaloisField(MIX_COLUMN_TABLE_INV[row][i], stateMatrix[i][col]);
            }

        } // end row
    }     // end col

    for(int row = 0; row < ROW; row++) {
        for(int col = 0; col < COL; col++) {
            stateMatrix[row][col] = buffer[row][col];
        }
    }
}
