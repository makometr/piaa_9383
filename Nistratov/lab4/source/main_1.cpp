#include "lab4_1.hpp"

int main(){
    std::string P, T;
    std::cin >> P >> T;
    auto answer = KMP(P, T);
    if (!answer.size()){
        std::cout << -1 << std::endl;
    }
    for (auto symbol : answer){
        if (symbol != answer.back()) std::cout << symbol << ',';
        else std::cout << symbol << std::endl; 
    }
    return 0;
}