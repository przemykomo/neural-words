#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstdio>
#include "convert.hpp"
#include "read_words.hpp"
#include "genann.h"
#include <thread>
#include <functional>
#include "learn.hpp"

int main(int argc, char *argv[]) {

    if (argc <= 1) {
        if (argv[0]) {
            std::cout << "Usage: " << argv[0] << " <output file>\n";
        } else {
            std::cout << "Usage: <program> <output file>\n";
        }
        return 0;
    }


    std::srand(std::time(0));

    //                       inputs,         hidden_layers, neurons_per_hidden_layer, outputs
    genann* ann{ genann_init(networkEntries, 1,             3,                        1) };

    // last argument is initial vector capacity so I give current dataset size (in lines)
    std::vector<std::string> positiveWords{ readAllWords("assets/positive", 2005) };
    std::vector<std::string> negativeWords{ readAllWords("assets/negative", 4782) };

    std::thread thread1(learn, ann, std::ref(positiveWords), std::ref(negativeWords), 1000);
    //std::thread thread2(learn, ann, std::ref(positiveWords), std::ref(negativeWords), 500);

    thread1.join();
    //thread2.join();

    //Testing:
    const char* word{"good"};
    const char* word2{"negative"};
    const char* word3{"positive"};
    const char* word4{"bad"};
    const char* word5{"yay"};
    std::cout << "Word \"" << word << "\" is " << *genann_run(ann, convertToInputs(word, 4).data()) << " positive.\n";
    std::cout << "Word \"" << word2 << "\" is " << *genann_run(ann, convertToInputs(word2, 8).data()) << " positive.\n";
    std::cout << "Word \"" << word3 << "\" is " << *genann_run(ann, convertToInputs(word3, 8).data()) << " positive.\n";
    std::cout << "Word \"" << word4 << "\" is " << *genann_run(ann, convertToInputs(word4, 3).data()) << " positive.\n";
    std::cout << "Word \"" << word5 << "\" is " << *genann_run(ann, convertToInputs(word5, 3).data()) << " positive.\n";


    std::FILE* file = std::fopen(argv[1], "w");
    genann_write(ann, file);
    std::fclose(file);

    genann_free(ann);
    return 0;
}
