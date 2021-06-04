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

    for (const auto& aho_pair : answer)
        std::cout << aho_pair.start_index << " " << aho_pair.pattern_index << std::endl;

    std::cout << "Количество вершин в автомате: " << forest->CountStates() << std::endl;

    std::vector<AhoPair> found = std::vector<AhoPair>{answer.begin(), answer.end()};
    std::cout << "Найденные пересечения:" << std::endl;
    for (int i = 0; i < found.size() - 1; ++i) {
        if (found[i].start_index - 1 + substrings[found[i].pattern_index - 1].size() > found[i+1].start_index - 1) {
            std::cout << "Пересечение " << substrings[found[i].pattern_index - 1] << " и "
                      << substrings[found[i+1].pattern_index - 1] << " с индекса "
                      << found[i+1].start_index - 1
                      << std::endl;
        }
    }

    return 0;
}