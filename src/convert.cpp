#include "convert.hpp"
#include <iostream>
#include <utility>

std::array<double, networkEntries> convertToInputs(const char* text, int length)  {
    std::array<double, networkEntries> data{};

    for(int i{0}; i < length; ++i) {
        if(text[i] == ' ' || text[i] == '-') {
            continue;
        }

        if(text[i] >= 'a' && text[i] <= 'z') {
            data[i * possibleLetters + text[i] - 'a'] = 1.0;
        } else {
            std::cout << "Invalid char: " << text[i] << ' ' << static_cast<int>(text[i]) << '\n';
        }
    }

    /*
    constexpr bitsPerLetter{8};

    for (int i{0}; i < length; ++i) {
        if (text[i] == ' ' || text[i] == '-') {
            continue;
        }
        
        std::size_t startIndex{i * bitsPerLetter};

        data[startIndex + 0] = static_cast<double>((text[i] & 0x01) >> 0);
        data[startIndex + 1] = static_cast<double>((text[i] & 0x02) >> 1);
        data[startIndex + 2] = static_cast<double>((text[i] & 0x02) >> 2);
        data[startIndex + 3] = static_cast<double>((text[i] & 0x02) >> 3);
        data[startIndex + 4] = static_cast<double>((text[i] & 0x02) >> 4);
        data[startIndex + 5] = static_cast<double>((text[i] & 0x02) >> 5);
        data[startIndex + 6] = static_cast<double>((text[i] & 0x02) >> 6);
        data[startIndex + 7] = static_cast<double>((text[i] & 0x02) >> 7);
    } */
    
    return data; // I'd move it but idk
}

