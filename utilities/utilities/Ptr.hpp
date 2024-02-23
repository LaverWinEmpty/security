#ifndef LWE__SECURITY_PTR_HPP__
#define LWE__SECURITY_PTR_HPP__

#include "../../common/common/defines.hpp"

struct Ptr
{
    /**
     * @brief constructure
     */
    Ptr(IN const void* param = nullptr);

    /**
     * @brief copy
     */
    Ptr& operator=(IN const void* param);

    /**
     * @brief move 1 byte
     */
    Ptr& operator++();

    /**
     * @brief move 1 byte
     */
    Ptr& operator--();

    /**
     * @brief move 1 byte
     */
    Ptr operator++(int);

    /**
     * @brief move 1 byte
     */
    Ptr operator--(int);

    /**
     * @brief move byte
     */
    Ptr operator+(IN ssize_t param) const;

    /**
     * @brief move byte
     */
    Ptr operator-(IN ssize_t param) const;

    /**
     * @brief move byte
     */
    Ptr& operator+=(IN ssize_t param);

    /**
     * @brief move byte
     */
    Ptr& operator-=(IN ssize_t param);

    /**
     * @brief compares
     */
    bool operator==(IN const Ptr&) const;

    /**
     * @brief compares
     */
    bool operator!=(IN const Ptr&) const;

    /**
     * @brief compares
     */
    bool operator>(IN const Ptr&) const;

    /**
     * @brief compares
     */
    bool operator<(IN const Ptr&) const;

    /**
     * @brief compares
     */
    bool operator>=(IN const Ptr&) const;

    /**
     * @brief compares
     */
    bool operator<=(IN const Ptr&) const;

    /**
     * @brief and for hiword / loword, etc.
     */
    Ptr operator&(IN const Ptr&) const;

    /**
     * @brief and for hiword / loword, etc.
     */
    Ptr& operator&=(IN const Ptr&);

    /**
     * @brief or for hiword / loword, etc.
     *
     * @param Ptr
     * @return Ptr
     */
    Ptr operator|(IN const Ptr&) const;

    /**
     * @brief or for hiword / loword, etc.
     */
    Ptr& operator|=(IN const Ptr&);

    /**
     * @brief xor for hiword / loword, etc.
     */
    Ptr operator^(IN const Ptr&) const;

    /**
     * @brief xor for hiword / loword, etc.
     */
    Ptr& operator^=(IN const Ptr&);

    /**
     * @brief distance byte between pointer
     */
    size_t operator-(IN const Ptr&) const;

    /**
     * @brief get byte
     */
    char& operator[](IN size_t);

    /**
     * @brief get byte readonly
     */
    char operator[](IN size_t) const;

    /**
     * @brief get as a pointer
     */
    template<typename T, typename std::enable_if<std::is_pointer<T>::value>::type* = nullptr> operator T() const;

    /**
     * @brief get as a value
     */
    template<typename T, typename std::enable_if<!std::is_pointer<T>::value>::type* = nullptr> operator T() const;

private:
    void* address;
};

#include "Ptr.ipp"

#endif