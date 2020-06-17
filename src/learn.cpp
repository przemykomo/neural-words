#include "learn.hpp"
#include <cstdlib>
#include "convert.hpp"
#include <random>

constexpr double good{1.0};
constexpr double bad{0.0};

void learn(genann* ann, std::vector<std::string> &positiveWords, std::vector<std::string> &negativeWords, int repetitionsMultiplier) {
    int repetitions = (positiveWords.size() + negativeWords.size()) * repetitionsMultiplier;
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> posDis{0, int(positiveWords.size() - 1)};
    std::uniform_int_distribution<int> negDis{0, int(negativeWords.size() - 1)};

    for(int i{}; i < repetitions; ++i) {
        std::string &goodWord = positiveWords[posDis(gen)];
        genann_train(ann, convertToInputs(goodWord.c_str(), goodWord.size()).data(), &good, 3);
        
        std::string &badWord = negativeWords[negDis(gen)];
        genann_train(ann, convertToInputs(badWord.c_str(), badWord.size()).data(), &bad, 3);
    }
}
