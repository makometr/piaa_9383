#include "lab5_2.h"

int main(int argc, char *argv[]) {
    std::string text, pattern;
    std::cin >> text >> pattern;

    char wild_card;
    std::cin >> wild_card;
    
    Trie* root = new Trie;
    int count = split(root, pattern, wild_card);
    build(root);

    std::vector<int> result = Aho_Corasick(root, text, count, pattern.size());
    for (auto position : result) {
        std::cout << position << std::endl;
    }

    delete root;
    return 0;
}