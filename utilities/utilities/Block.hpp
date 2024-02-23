#ifndef LWE__SECURITY_BLOCK_HPP
#define LWE__SECURITY_BLOCK_HPP

#include "../../common/common/defines.hpp"

struct Block
{
    /**
     * @brief getter
     */
    uint8_t& operator[](IN ssize_t index);

    /**
     * @brief constructure by byte array
     */
    Block(const int8_t* str);

    /**
     * @brief constructure
     */
    template<typename... Args> Block(Args... args);

    /**
     * @brief getter
     */
    template<typename T> operator T();

private:
    /**
     * @brief constructure implementation
     */
    template<typename T, typename... Args> void Constructure(ssize_t index, T arg, Args... args);

    /**
     * @brief constructure implementation conclusion
     */
    void Constructure(ssize_t index);

    /**
     * @brief variable
     */
    uint8_t data[32];
};

#include "Block.ipp"

#endif