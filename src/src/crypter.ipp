#include "crypter.hpp"

std::string Crypter::Encrypt(const std::string& data, const std::string& key)
{
    std::string after = AES256::Encrypt(data.c_str(), data.length(), SHA256::Hashing(key.c_str(), key.length()));
    return Base64::Encode(after);
}

std::string Crypter::Decrypt(const std::string& data, const std::string& key, int* padding)
{
    std::string after = Base64::Decode(data);
    return AES256::Decrypt(after.c_str(), after.length(), SHA256::Hashing(key.c_str(), key.length()), padding);
}

std::string Crypter::Hasing(const std::string& data)
{
    return SHA256::Hashing(data.c_str(), data.length());
}

std::string Crypter::CryptoHashing(const std::string& data, const std::string& salt, ssize_t count)
{
    return SHA256::Encrypt(data.c_str(), data.length(), salt.c_str(), salt.length(), count);
}

std::string Crypter::Helper::ToHex(IN const std::string& param)
{
    char buffer[65] = { 0 };
    for(int i = 0; i < 32; ++i) {
        sprintf(buffer + (i * 2), "%02hhX", param[i]);
    }
    return buffer;
}

std::string Crypter::Helper::ToString(IN const Ptr& ptr, IN size_t size)
{
    std::string str;
    for(int i = 0; i < size; ++i) {
        str.push_back(ptr[i]);
    }
    return str;
}