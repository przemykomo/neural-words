#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ostream>
#include <string>
#include <vector>
#include <cstdio>
#include "convert.hpp"
#include "read_words.hpp"
#include "genann.h"
#include <thread>
#include <functional>
#include "learn.hpp"

void printNetworkGuess(std::ostream& ostream, genann* ann, const std::string& word) {
	// Does this ptr need to be destroyed?
	const double* result = genann_run(ann, convertToInputs(word.c_str(), word.length()).data());

	ostream << "Word \"" << word << "\" is " << result[0] << " positive." << std::endl;
}

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

    thread1.join();

    //Testing:
	printNetworkGuess(std::cout, ann, "good");
	printNetworkGuess(std::cout, ann, "negative");
	printNetworkGuess(std::cout, ann, "positive");
	printNetworkGuess(std::cout, ann, "bad");
	printNetworkGuess(std::cout, ann, "yay");

    std::FILE* file = std::fopen(argv[1], "w");
    genann_write(ann, file);
    std::fclose(file);

    genann_free(ann);
    return 0;
}
