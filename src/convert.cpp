#include "convert.hpp"
#include <iostream>

std::array<double, maxLength * possibleLetters> convertToInputs(const char* text, int length)  {
    std::array<double, maxLength * possibleLetters> data{};
    
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
    
    return data;
}

