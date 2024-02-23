#ifndef SBL_SHA256_HEADER__
#define SBL_SHA256_HEADER__

#include "../../utilities/utilities/Block.hpp"
#include "../../utilities/utilities/Ptr.hpp"
#include "../../common/common/macros.hpp"

class SHA256
{
private:
    static constexpr size_t DIGEST_BLOCK_LEN = 64;
    static constexpr size_t DIGEST_VALUE_LEN = 32;
    static const uint32_t   CONSTANTS[64];

private:
    /**
     * @brief state
     */
    struct
    {
        uint32_t chainVar[DIGEST_VALUE_LEN >> 2];
        uint32_t highLength;
        uint32_t lowLength;
        uint32_t remainNum;
        uint8_t  buffer[DIGEST_BLOCK_LEN];
    } state;

private:
    /**
     * @brief initialization
     */
    SHA256();

public:
    /**
     * @brief hashing
     *
     * @param message [in] data
     * @param size    [in] data size
     * @return std::string hash code
     */
    static std::string Hashing(IN const Ptr message, IN size_t size);

    /**
     * @brief cryptographic hashing
     *
     * @param  message     [in] data
     * @param  messageSize [in] data size
     * @param  salt        [in] additional data
     * @param  saltSize    [in] additional data size
     * @param  stretching  [in] number of hashing attemps
     * @return std::string
     */
    static std::string Encrypt(IN const Ptr message, IN size_t messageSize, IN const Ptr salt, IN size_t saltSize,
                               IN ssize_t stretching);

private:
    /**
     * @brief module
     */
    void Initialize();

    /**
     * @brief module
     */
    void Compress(IN Ptr message, IN uint32_t size);

    /**
     * @brief module
     */
    Block Final(IN Ptr message);

    /**
     * @brief module
     */
    void Transform(IN uint32_t* msg, IN uint32_t* chainVar);

private:
    /**
     * @brief module
     */
    static uint32_t RR(IN uint32_t x, uint32_t n);

    /**
     * @brief module
     */
    static uint32_t SS(IN uint32_t x, uint32_t n);

    /**
     * @brief module
     */
    static uint32_t Choose(IN uint32_t x, IN uint32_t y, IN uint32_t z);

    /**
     * @brief module
     */
    static uint32_t Majority(IN uint32_t x, IN uint32_t y, IN uint32_t z);

    /**
     * @brief module
     */
    static uint32_t Sigma0(IN uint32_t x);

    /**
     * @brief module
     */
    static uint32_t Sigma1(IN uint32_t x);

    /**
     * @brief module
     */
    static uint32_t RHO0(IN uint32_t x);

    /**
     * @brief module
     */
    static uint32_t RHO1(IN uint32_t x);

private:
    static const bool IS_LITTLE_ENDIAN;
};

#endif