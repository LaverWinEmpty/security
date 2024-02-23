#ifndef LWE__AES256_HEADER__
#define LWE__AES256_HEADER__

#include "string"
#include "utilities/utilities/Block.hpp"
#include "utilities/utilities/Ptr.hpp"

class AES256
{
private:
    static constexpr int64_t BLOCK_SIZE    = 16;                                    // AES
    static constexpr int64_t KEY_SIZE_BYTE = 32;                                    // AES-256
    static constexpr int64_t ROUND_COUNT   = 14;                                    // AES-256
    static constexpr int64_t EXPANDED_SIZE = BLOCK_SIZE * ROUND_COUNT + BLOCK_SIZE; // 240 Byte
    static constexpr int64_t ROW           = 4;                                     // Matrix row
    static constexpr int64_t COL           = 4;                                     // Matrix column

public:
    /**
     * @brief encrypt
     *
     * @param Ptr         [in] data
     * @param size_t      [in] data size
     * @param std::string [in] key
     * @throw std::invalid_argument: key size is not 32 byte
     * @return std::string
     */
    static std::string Encrypt(IN const Ptr&, IN ssize_t, IN const std::string&);

    /**
     * @brief decrypt
     * @note  last data is 1: ambiguity, so get is optional
     *
     * @param  Ptr         [in] data
     * @param  size_t      [in] data size
     * @param  std::string [in] key
     * @param  int         [out] get padding size (optional: use when checking padding is required)
     * @throw  std::invalid_argument: key size is not 32 byte
     * @return std::string
     */
    static std::string Decrypt(IN const Ptr&, IN size_t, IN const std::string&, OUT OPT int* = nullptr);

private:
    /**
     * @brief encrypt 32 byte module
     *
     * @param Ptr [in/out] block to encrypt
     */
    void Encrypt256(IN OUT Ptr);

    /**
     * @brief decrypt 32 byte module
     *
     * @param Ptr [in/out] block to decrypt
     */
    void Decrypt256(IN OUT Ptr);

private:
    /**
     * @brief module
     */
    void KeyScheduling(IN const Ptr);

    /**
     * @brief module
     */
    uint8_t GaloisField(IN uint8_t l, IN uint8_t r);

    /**
     * @brief module
     */
    void AddRoundKey(IN const uint8_t*);

    /**
     * @brief module
     */
    void SubBytes();

    /**
     * @brief module
     */
    void SubBytesInverse();

    /**
     * @brief module
     */
    void ShiftRows();

    /**
     * @brief module
     */
    void ShiftRowsInverse();

    /**
     * @brief module
     */
    void MixColumns();

    /**
     * @brief module
     */
    void MixColumnsInverse();

private:
    static const uint8_t S_BOX[];
    static const uint8_t S_BOX_INV[];
    static const uint8_t ROUND_CONSTANT[];
    static const uint8_t MIX_COLUMN_TABLE[ROW][COL];
    static const uint8_t MIX_COLUMN_TABLE_INV[ROW][COL];

    uint8_t stateMatrix[ROW][COL] = { 0 };
    uint8_t exKey[EXPANDED_SIZE]  = { 0 };
    Block   key;
    // uint8_t key[KEY_SIZE_BYTE];
};

#endif