#include "KMP/KMP.h"

void printAnswer(std::vector<int>& answer) {
    if (answer.empty()) {
        std::cout << -1;
        return;
    }
    std::cout << answer[0];
}


int main() {
    std::string A, B;
    readStrings(A, B, std::cin);
    if(A.size() != B.size()) {
        std::cout << -1;
        return 0;
    }

    if(A == B) {
        std::cout << 0;
        return 0;
    }
    A = A + A;
    std::vector<int> answer = KMP(B, A);
    printAnswer(answer);
}