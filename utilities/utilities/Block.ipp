#include "Block.hpp"

uint8_t& Block::operator[](IN ssize_t index)
{
    return data[index];
}

Block::Block(const int8_t* str): data{ 0 }
{
    for(int i = 0; str[i] || i < 32; ++i) {
        data[i] = str[i];
    }
}

template<typename... Args> Block::Block(Args... args): data{ 0 }
{
    Constructure(0, args...);
}

template<typename T> Block::operator T()
{
    return reinterpret_cast<T>(data);
}

template<typename T, typename... Args> void Block::Constructure(ssize_t index, T arg, Args... args)
{
    data[index] = static_cast<T>(arg);
    if(index >= 32) {
        throw std::out_of_range("parameter size exceeds 32 byte");
    }
    Constructure(index + 1, args...);
}

void Block::Constructure(ssize_t index)
{
    return;
}