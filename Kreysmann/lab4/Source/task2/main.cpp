#include "task2.hpp"


int main()
{
    std::string A, B;
    input(A, B, std::cin);
    int result = KMP(A, B);
    std::cout<<result;
    return 0;
}