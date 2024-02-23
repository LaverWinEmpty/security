/**
 * @file    crypter.hpp
 * @author  LaverWinEmpty@google.com
 * @brief   lite crypter
 * @version 1.0
 * @date    2024-02-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef LWE__SECURITY_CRYPTER_HPP__
#define LWE__SECURITY_CRYPTER_HPP__

#include "../../tools/tools/aes256.hpp"
#include "../../tools/tools/sha256.hpp"
#include "../../tools/tools/base64.hpp"

class Crypter
{
    Crypter()         = delete;
    Crypter(Crypter&) = delete;

public:
    /**
     * @brief utility
     */
    class Helper
    {
        Helper()        = delete;
        Helper(Helper&) = delete;

    public:
        /**
         * @brief hash to hex string (e.g. 0x01 => "01")
         */
        static std::string ToHex(IN const std::string&);

        /**
         * @brief pointer to string, simple serializer
         * @note
         */
        static std::string ToString(IN const Ptr&, IN size_t);
    };

public:
    /**
     * @brief AES-256 encrypt
     *
     * @param  data [in]
     * @param  key  [in]
     * @return std::string encoded in base64
     */
    static std::string Encrypt(IN const std::string& data, IN const std::string& key);

    /**
     * @brief AES-256 decrypt
     *
     * @param  data    [in]
     * @param  key     [in]
     * @param  padding [out]
     * @return std::string
     */
    static std::string Decrypt(IN const std::string& data, IN const std::string& key, OUT OPT int* padding = nullptr);

    /**
     * @brief SHA-256 hasing
     */
    static std::string Hasing(IN const std::string& data);

    /**
     * @brief SHA-256 cryptographic hashing
     *
     * @param  msg         [in] string
     * @param  salt        [in] additional string
     * @param  stretching  [in] number of hashing attemps
     * @return std::string hash code
     */
    static std::string CryptoHashing(IN const std::string& data, IN const std::string& salt, IN ssize_t count);
};

#include "crypter.ipp"

#endif