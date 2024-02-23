#include "Ptr.hpp"

Ptr::Ptr(const void* param): address(const_cast<void*>(param)) {}

Ptr& Ptr::Ptr::operator=(IN const void* param)
{
    return address = const_cast<void*>(param), *this;
}

Ptr& Ptr::operator++()
{
    return address = static_cast<int8_t*>(address) + 1, *this;
}

Ptr& Ptr::operator--()
{
    return address = static_cast<int8_t*>(address) - 1, *this;
}

Ptr Ptr::operator++(int)
{
    Ptr p   = *this;
    address = reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(address) + 1);
    return p;
}

Ptr Ptr::operator--(int)
{
    Ptr p   = *this;
    address = reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(address) - 1);
    return p;
}

Ptr Ptr::operator+(ssize_t param) const
{
    return Ptr(reinterpret_cast<int8_t*>(address) + param);
}

Ptr Ptr::operator-(ssize_t param) const
{
    return Ptr(reinterpret_cast<int8_t*>(address) - param);
}

Ptr& Ptr::operator+=(ssize_t param)
{
    return address = static_cast<int8_t*>(address) + param, *this;
}

Ptr& Ptr::operator-=(ssize_t param)
{
    return address = static_cast<int8_t*>(address) - param, *this;
}

Ptr Ptr::operator|(const Ptr& param) const
{
    return reinterpret_cast<void*>(reinterpret_cast<size_t>(address) | reinterpret_cast<size_t>(param.address));
}

Ptr Ptr::operator&(const Ptr& param) const
{
    return reinterpret_cast<void*>(reinterpret_cast<size_t>(address) & reinterpret_cast<size_t>(param.address));
}

Ptr Ptr ::operator^(const Ptr& param) const
{
    return reinterpret_cast<void*>(reinterpret_cast<size_t>(address) ^ reinterpret_cast<size_t>(param.address));
}

Ptr& Ptr::operator|=(const Ptr& param)
{
    *this = *this | param;
    return *this;
}

Ptr& Ptr::operator&=(const Ptr& param)
{
    *this = *this & param;
    return *this;
}

Ptr& Ptr::operator^=(const Ptr& param)
{
    *this = *this ^ param;
    return *this;
}

size_t Ptr::operator-(const Ptr& param) const
{
    return reinterpret_cast<char*>(address) - reinterpret_cast<char*>(param.address);
}

char& Ptr::operator[](size_t index)
{
    return reinterpret_cast<char*>(address)[index];
}

char Ptr::operator[](size_t index) const
{
    return reinterpret_cast<char*>(address)[index];
}

template<typename T, typename std::enable_if<std::is_pointer<T>::value>::type*> Ptr::operator T() const
{
    return reinterpret_cast<T>(address);
}

template<typename T, typename std::enable_if<!std::is_pointer<T>::value>::type*> Ptr::operator T() const
{
    return *reinterpret_cast<T*>(address);
}