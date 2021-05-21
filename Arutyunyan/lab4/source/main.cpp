#include <iostream>
#include <algorithm>

#include "knutmorrispratt.h"

int main() {
    std::string source, substring;

    std::getline(std::cin, substring);
    std::getline(std::cin, source);

    auto answer = KnutMorrisPratt(source, substring);
    std::cout << "Ответ: ";
    for (int v : answer) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}