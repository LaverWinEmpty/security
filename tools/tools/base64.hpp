#ifndef LWE__SECURITY_BASE64_HPP__
#define LWE__SECURITY_BASE64_HPP__

#include "string"
#include "../../common/common/defines.hpp"

class Base64
{
    Base64()        = delete;
    Base64(Base64&) = delete;

private:
    /**
     * @brief table
     */
    static const char* TABLE;

    /**
     * @brief ascii to index of table
     */
    static int ToIndex(IN char ascii);

public:
    /**
     * @brief encode
     */
    static std::string Encode(IN const std::string& str);

    /**
     * @brief decode
     */
    static std::string Decode(IN const std::string& str);
};

#endif