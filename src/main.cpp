#include <time.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <fstream>
#include <vector>
#include <cstdio>

#include "genann.h"

//TODO: move that to other compilation unit
constexpr std::size_t maxLength{24}; //max word length
constexpr std::size_t possibleLetters{26}; //english alphabet

// convert text to data which we can give neural network
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

int main(int argc, char *argv[]) {
    std::srand(std::time(0));

    genann* ann{ genann_init(maxLength * possibleLetters, 3, 3, 1) };

    double good{1.0};
    double bad{0.0};

    std::vector<std::string> positiveWords{};
    std::vector<std::string> negativeWords{};

    {
        std::ifstream positive("assets/positive");
        
        if(!positive) {
            std::cout << "Can't open positive file!\n";
            return 1;
        }

        std::string line;
        while(std::getline(positive, line)) {
            positiveWords.push_back(line);
        }
    }

    {
        std::ifstream negative("assets/negative");

        if(!negative) {
            std::cout << "Can't open negative file!\n";
            return 1;
        }

        std::string line;
        while(std::getline(negative, line)) {
            negativeWords.push_back(line);
        }
    }

    for(int i{}; i < (positiveWords.size() + negativeWords.size()) * 1000; ++i) {
        std::string word{positiveWords[std::rand() % positiveWords.size()]};
        genann_train(ann, convertToInputs(word.c_str(), word.size()).data(), &good, 3);
        word = negativeWords[std::rand() % negativeWords.size()];
        genann_train(ann, convertToInputs(word.c_str(), word.size()).data(), &bad, 3);
    }

    //Testing:
    const char* word{"good"};
    const char* word2{"negative"};
    const char* word3{"positive"};
    std::cout << "Word \"" << word << "\" is " << *genann_run(ann, convertToInputs(word, 4).data()) << " positive.\n";
    std::cout << "Word \"" << word2 << "\" is " << *genann_run(ann, convertToInputs(word2, 8).data()) << " positive.\n";
    std::cout << "Word \"" << word3 << "\" is " << *genann_run(ann, convertToInputs(word3, 8).data()) << " positive.\n";

    std::FILE* file = std::fopen("network.ann", "w");
    genann_write(ann, file);
    std::fclose(file);

    genann_free(ann);
    return 0;
}
