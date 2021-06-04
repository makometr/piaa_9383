#include <iostream>
#include <string>
#include <vector>

#include "bohr.h"
#include "aho_corasick.hpp"


int main() {
    std::string text;
    std::getline(std::cin, text);

    int n;
    std::vector<std::string> substrings;
    std::cin >> n;
    getchar();

    substrings.reserve(n);
    for (int i = 0; i < n; ++i) {
        std::string substring;
        std::getline(std::cin, substring);
        substrings.push_back(std::move(substring));
    }

    auto forest = BohrNode::BuildForest(substrings);
    auto answer = AhoCorasick(forest, substrings, text);

    for (const auto& pair : answer) {
        std::cout << pair.start_index << " " << pair.pattern_index << std::endl;
    }

    return 0;
}