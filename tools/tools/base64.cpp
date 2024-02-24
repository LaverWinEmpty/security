#include "base64.hpp"

const int8_t Base64::ENCODING_TABLE[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" };
const int8_t Base64::DECODING_TABLE[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                          -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                          -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60,
                                          61, -1, -1, -1, 64, -1, -1, -1, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                                          11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1,
                                          -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
                                          43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1 };

int_fast8_t Base64::Encoding(int_fast8_t value)
{
    return ENCODING_TABLE[value & 0x3F];
}

int_fast8_t Base64::Decoding(int8_t ascii)
{
    return (ascii & 0x80) ? -1 : DECODING_TABLE[ascii];
}

std::string Base64::Encode(const std::string& str)
{
    std::string result;
    int_fast8_t current, remind; // for shift
    ssize_t     cursor = -1;     // index
    ssize_t     prev   = -1;     // previous index

    int64_t size = str.size();
    while(++cursor < size) {
        switch(cursor % 3) {
        // 11111100 00000000 00000000
        case 0:
            current = static_cast<uint_fast8_t>(str[cursor]) >> 2;
            result.push_back(ENCODING_TABLE[current]);
            break;

        // 00000011 11110000 00000000
        case 1:
            prev    = cursor - 1;
            remind  = (static_cast<uint_fast8_t>(str[prev]) & 0b00000011) << 4;
            current = (static_cast<uint_fast8_t>(str[cursor]) & 0b11110000) >> 4;
            result.push_back(ENCODING_TABLE[current | remind]);
            break;

        // 00000000 00001111 11000000
        // 00000000 00000000 00111111
        case 2:
            prev    = cursor - 1;
            remind  = (static_cast<uint_fast8_t>(str[prev]) & 0b00001111) << 2;
            current = (static_cast<uint_fast8_t>(str[cursor]) & 0b11000000) >> 6;
            result.push_back(ENCODING_TABLE[current | remind]);
            result.push_back(Encoding(str[cursor])); // last byte & 0x3F
            break;
        }
    }

    // Last
    switch(size % 3) {
    case 0: break;

    case 1:
        prev = cursor - 1;
        result.push_back(Encoding(str[prev] & 0b00000011) << 4); // remaind 2 bit
        result.append("==");
        break;

    case 2:
        prev = cursor - 1;
        result.push_back(Encoding(str[prev] & 0b00001111) << 2); // remaind 4 bit
        result.push_back('=');
        break;
    }

    return result;
}

std::string Base64::Decode(const std::string& str)
{
    size_t size = str.size();

    if(size % 4) {
        throw std::invalid_argument("It doesn't seem to be an encoded string.");
    }

    int padding = 0;
    if(str[size - 1] == '=') {
        ++padding;
        if(str[size - 2] == '=') {
            ++padding;
        }
    }

    std::string result;

    int         loop = 0, cursor = 0, next = 1;
    int_fast8_t left, right; // for bitwise operation
    int_fast8_t temp;

    while(str[cursor]) {
        left  = Decoding(str[cursor]);
        right = Decoding(str[next]);
        if(left == -1 || right == -1) {
            throw std::invalid_argument("It doesn't seem to be an encoded string.");
        }

        switch(loop % 3) {
        case 0: temp = (left << 2) | (right & 0b110000) >> 4; break;

        case 1: temp = ((left & 0b001111) << 4) | ((right & 0b111100) >> 2); break;

        case 2:
            temp = ((left & 0b000011) << 6) | right;
            ++cursor;
            ++next;
            break;
        }

        result.push_back(temp);
        ++cursor;
        ++next;
        ++loop;
    }

    // remove padding ("==")
    while(padding-- > 0) {
        result.pop_back();
    }

    return result;
}
