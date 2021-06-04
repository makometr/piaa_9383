#include <iostream>
#include <string>
#include <vector>

#include "bohr.h"
#include "aho_corasick.hpp"


int main() {
    std::string text;
    std::getline(std::cin, text);

    std::string joker_pattern;
    std::getline(std::cin, joker_pattern);

    char joker;
    std::cin >> joker;

    auto info_pair = BohrNode::BuildForestWithJoker(joker_pattern, joker);
    auto answer = AhoCorasick(info_pair.first, info_pair.second, joker_pattern.size(), text);

    for (int index : answer) {
        std::cout << index << std::endl;
    }

    return 0;
}