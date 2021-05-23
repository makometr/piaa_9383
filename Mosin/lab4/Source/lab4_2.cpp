#include "API.h"

int main(int argc, char *argv[]) {
    std::string P, T;
    std::cout << "first string: ";
    std::cin >> P;
    std::cout << "second string: ";
    std::cin >> T;
    
    if (P == T) {
        std::cout << 0 << std::endl;
    }
    else if (P.size() != T.size()) {
        std::cout << -1 << std::endl;
    }
    else {
        P += P;
        std::vector<int> indices = KMP(T, P);
        if (indices.empty()) {
            std::cout << -1 << std::endl;
        }
        else {
            std::cout << indices[0] << std::endl;
        }
    }
    return 0;
}