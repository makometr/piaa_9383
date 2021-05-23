#include "lab4_2.hpp"

int main(){
    std::string P, T;
    std::cin >> P >> T;

    if (P == T){
        std::cout << 0 << std::endl;
        return 0;
    }

    if (P.size() != T.size()){
        std::cout << -1 << std::endl;
        return 0;
    }

    auto answer = KMP(P, T);

    if (!answer.size()){
        std::cout << -1 << std::endl;
        return 0;
    }

    for (auto symbol : answer){
        if (symbol != answer.back()) std::cout << symbol << ',';
        else std::cout << symbol << std::endl; 
    }
    
    return 0;
}