#include "lb5_1.hpp"

int main () {
    std::string text;
    std::cin >> text;
    int n;
    std::cin >> n;
    std::vector<std::string> patterns;
    std::string pattern;
    for (int i = 0; i < n; i++) {
        std::cin >> pattern;
        patterns.push_back(pattern);
    }
    Machine machine(patterns);
    auto result = machine.AhoCorasick(text);
    for (auto &obj : result) {
        std::cout << obj.first << ' ' << obj.second << '\n';
    }
    return 0;
}

