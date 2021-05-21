#include "API.h"

int main(int argc, char *argv[]) {
    std::string P, T;
    std::cout << "substring: ";
    std::cin >> P;
    std::cout << "text: ";
    std::cin >> T;

    std::vector<int> indices = KMP(P, T);
    if (indices.empty()) {
        std::cout << -1 << std::endl;
    }
    else {
        for (auto index : indices) {
            std::cout << index;
            if (index != indices.back()) {
                std::cout << ',';
            }
        }
        std::cout << std::endl;
    }

    return 0;
}