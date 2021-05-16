#include <iostream>
#include <algorithm>

#include "knutmorrispratt.hpp"
#include "stringwrapper.hpp"


int main() {
    std::string source, substring;

    std::getline(std::cin, substring);
    std::getline(std::cin, source);

    auto answer = CycleShiftDetect(source, substring);
    std::cout << answer << std::endl;

    return 0;
}