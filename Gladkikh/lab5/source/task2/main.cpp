#include <iostream>

#include "ahocorasick.hpp"

int main() {

    std::string patt, temp;
    char joker;

    std::cin >> temp;
    std::cin >> patt;
    std::cin >> joker;

    AhoCorasick aho_corasick;

    aho_corasick.add_pattern_with_jokers(patt, joker);


    aho_corasick.init();


    auto ans = aho_corasick.search(temp);

    for(const auto& it: ans) {
        std::cout << it << "\n";
    }

    return 0;
}