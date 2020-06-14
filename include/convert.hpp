#pragma once
#include <vector>
#include <array>

constexpr std::size_t maxLength{24}; //max word length
constexpr std::size_t possibleLetters{26}; //english alphabet

// convert text to data which we can give neural network
std::array<double, maxLength * possibleLetters> convertToInputs(const char* text, int length);
