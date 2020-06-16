#include "read_words.hpp"
#include <utility>
#include <fstream>

std::vector<std::string> readAllWords(std::string file, int reserveCapacity) {
    std::vector<std::string> words{};
    words.reserve(reserveCapacity);

    std::ifstream fileStream(file);
    if (!fileStream) {
        throw std::runtime_error("Cannot open file " + file);
    }

    std::string line;
    while (std::getline(fileStream, line)) {
        words.push_back(line);
    }

    words.shrink_to_fit();
    return std::move(words);
}

