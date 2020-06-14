#pragma once
#include <vector>
#include "genann.h"
#include <string>

void learn(genann* ann, std::vector<std::string> &positiveWords, std::vector<std::string> &negativeWords, int repetitionsMultiplier);
