#include "ford_falk.h"

int main(){
    FFsolver solver;
    solver.input();
    auto answer = solver.FordFulkerson();
    std::cout << answer.first << std::endl;
    solver.print_edges(answer.second);
    return 0;
}