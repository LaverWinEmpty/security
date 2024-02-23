// used it in visual 
#define _CRT_SECURE_NO_WARNINGS

#include "iostream"
#include "tools/tools/aes256.cpp"
#include "tools/tools/sha256.cpp"
#include "tools/tools/base64.cpp"
#include "src/src/crypter.hpp"

int main()
{
    std::string text = "This is short plain text for testing purposes";
    std::string key  = "1234"; // 3AC674216F3E15C761EE1A5E255F067953623C8B388B4459E13F978D7C846F4

    // key hashing SHA-256 => text encrypt AES-256 => text encode Base64
    text = Crypter::Encrypt(text, key);
    std::cout << "Encrypted: " << text << std::endl;

    // key hashing SHA-256 => text decode Base64 => text decrypt AES-256
    text = Crypter::Decrypt(text, key, nullptr);
    std::cout << "Decrypted: " << text << "\n" << std::endl;

    // or

    // salt only
    key = SHA256::Encrypt(key.c_str(), key.size(), key.c_str(), key.size(), 0);
    std::cout << "Salted Key: " << Crypter::Helper::ToHex(key) << std::endl;
    
    // stretching only
    key = SHA256::Encrypt(key.c_str(), key.size(), "", 0, 1);
    std::cout << "Stretched Key: " <<  Crypter::Helper::ToHex(key) << std::endl;

    // encrypt
    text = AES256::Encrypt(text.c_str(), text.size(), key);
    std::cout << "Encrypted Text: " << text << std::endl;

    // encode
    text = Base64::Encode(text);
    std::cout << "Encoded Text: " << text << std::endl;

    // decode
    text = Base64::Decode(text);
    std::cout << "Decoded Text: " << text << std::endl;

    // decrypt
    text = AES256::Decrypt(text.c_str(), text.size(), key);
    std::cout << "Decrypted Text: " << text << std::endl;

}