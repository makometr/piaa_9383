#include "task1.hpp"

int main()
{
    std::string P, T;
    input(P, T, std::cin);
    Result result = KMP(P, T);
    output(result, std::cout);
    return 0;
}