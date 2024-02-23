#include "base64.hpp"

const char* Base64::TABLE = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Throw ErrMsg
int Base64::ToIndex(char ascii)
{
    if(ascii < '/') {
        if(ascii == '+') {
            return 62;
        }
    }

    else if(ascii < 'A') {
        if(ascii == '/') {
            return 63;
        }
        if(ascii == '=') {
            return 0; // unused
        }
        if(ascii <= '9') {
            return ascii + 4; // - '0' + 52
        }
    }

    else if(ascii <= 'z') {
        if(ascii <= 'Z') {
            return ascii - 65; // - 'A' + 0
        }
        if(ascii >= 'a') {
            return ascii - 71; // - 'a' + 26
        }
    }

    throw std::invalid_argument("This character is not in the table.");
}

std::string Base64::Encode(const std::string& str)
{
    int         cursor = -1;
    std::string result;
    uint8_t     current, remind; // For shift
    int         prev;            // Previous cursor position

    int64_t size = str.size();
    while(++cursor < size) {
        switch(cursor % 3) {

        // 11111100 00000000 00000000
        case 0:
            current = static_cast<uint8_t>(str[cursor]) >> 2;
            result.push_back(TABLE[current]);
            break;

        // 00000011 11110000 00000000
        case 1:
            prev    = cursor - 1;
            remind  = static_cast<uint8_t>(str[prev] & 0b00000011) << 4;
            current = static_cast<uint8_t>(str[cursor] & 0b11110000) >> 4;
            result.push_back(TABLE[current | remind]);
            break;

        // 00000000 00001111 11000000
        // 00000000 00000000 00111111
        case 2:
            prev    = cursor - 1;
            remind  = static_cast<uint8_t>(str[prev] & 0b00001111) << 2;
            current = static_cast<uint8_t>(str[cursor] & 0b11000000) >> 6;
            result.push_back(TABLE[current | remind]);

            current = (str[cursor] & 0b00111111);
            result.push_back(TABLE[(str[cursor] & 0b00111111)]);
            break;
        }
    }

    // Last
    switch(size % 3) {
    case 0: break;

    case 1:
        prev = cursor - 1;
        result.push_back(TABLE[(str[prev] & 0b00000011) << 4]);
        result.append("==");
        break;

    case 2:
        prev = cursor - 1;
        result.push_back(TABLE[(str[prev] & 0b00001111) << 2]);
        result.push_back('=');
        break;
    }

    return result;
}

// Throw ErrMsg
std::string Base64::Decode(const std::string& str)
{
    if(str.size() % 4) {
        throw std::invalid_argument("It doesn't seem to be an encoded string.");
    }

    int padding = 0;
    if(str[str.size() - 1] == '=') {
        ++padding;
    }
    if(str[str.size() - 2] == '=') {
        ++padding;
    }

    std::string result;

    int loop = 0, cursor = 0;
    while(str[cursor]) {
        int next = cursor + 1; // Next cursor position

        switch(loop % 3) {
        case 0: result.push_back(((ToIndex(str[cursor])) << 2) | (ToIndex(str[next]) & 0b110000) >> 4); break;

        case 1:
            result.push_back(((ToIndex(str[cursor]) & 0b001111) << 4) | ((ToIndex(str[next]) & 0b111100) >> 2));
            break;

        case 2:
            result.push_back(((ToIndex(str[cursor]) & 0b000011) << 6) | ToIndex(str[next]));
            ++cursor;
            break;
        }

        ++cursor;
        ++loop;
    }

    while(padding-- > 0) {
        result.pop_back();
    }

    return result;
}