#include "KMP/KMP.h"

void printAnswer(std::vector<int>& answer) {
    if (answer.size() == 0) {
        std::cout << -1;
        return;
    }
    for(size_t i = 0; i < answer.size(); i++) {
        if(i < answer.size() - 1) std::cout << answer[i] << ',';
        else std::cout << answer[i] << '\n';
    }
}


int main() {
    std::string substring, text;
    readStrings(substring, text, std::cin);
    std::vector<int> answer = KMP(substring, text);
    printAnswer(answer);
}