#ifndef LWE__SECURITY_BASE64_HPP__
#define LWE__SECURITY_BASE64_HPP__

#include "string"
#include "../../common/common/defines.hpp"

class Base64
{
    Base64()        = delete;
    Base64(Base64&) = delete;

private:
    static const int8_t ENCODING_TABLE[];
    static const int8_t DECODING_TABLE[];

public:
    /**
     * @brief use table
     *
     * @param  int_fast8_t [in] plain character. converted to 6 bits
     * @return int_fast8_t encoded character
     */
    inline static int_fast8_t Encoding(IN int_fast8_t);

    /**
     * @brief use table
     *
     * @param  int8_t [in] encoded character
     * @return int_fast8_t encoded character. if not in table, return -1
     */
    inline static int_fast8_t Decoding(IN int8_t);

public:
    /**
     * @brief encode
     */
    static std::string Encode(IN const std::string& str);

    /**
     * @brief decode
     *
     * @throw std::invalid_argument
     */
    static std::string Decode(IN const std::string& str);
};

#endif