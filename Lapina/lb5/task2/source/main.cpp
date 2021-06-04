#include "lb5_2.hpp"

int main () {
    std::string text;
    std::cin >> text;
    std::string pattern;
    std::cin >> pattern;
    char joker;
    std::cin >> joker;
    std::vector<std::pair<std::string, int>> patterns;
    std::string subPattern;
    int endJokers;
    for (int i = 0; i < pattern.size(); i++) {
        if (pattern[i] == joker) {
            if (!subPattern.empty())
                patterns.emplace_back(subPattern, i);
            subPattern = "";
            endJokers++;
        } else {
            subPattern += pattern[i];
            endJokers = 0;
        }
    }
    if (!subPattern.empty()) {
        patterns.emplace_back(subPattern, pattern.size());
    }
    Machine machine(patterns, endJokers);
    auto result = machine.AhoCorasick(text);
    for (auto &obj : result) {
        std::cout << obj << '\n';
    }
    return 0;
}
