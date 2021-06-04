#include <iostream>

#include "ahocorasick.hpp"

int main() {

    AhoCorasick aho_corasick;

    int patt_amount;
    std::string patt, temp; 

    std::cin >> temp;
    std::cin >> patt_amount;

    for(int i = 0; i < patt_amount; ++i) {
        std::cin >> patt;
        aho_corasick.add_string(patt);    
    }

    aho_corasick.init();

    
    auto ans = aho_corasick.search(temp);

    for(const auto& pair: ans) {
        std::cout << pair.first << " " << pair.second << "\n";
    }

    return 0;
}