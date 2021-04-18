#include "lb2.hpp"

int main(){
    char start, finish;
    std::cin>>start;
    std::cin>>finish;
    Graph G;
    std::vector <char> v_for_check;
    v_for_check.push_back(start);
    v_for_check.push_back(finish);
    Read(G, v_for_check);
    float priority = 0;    //путь до предыдущей вершины
    std::string result = Algoritm_A(priority, start, finish, G);
    std::cout << result << '\n';
    Check_h(v_for_check, finish, priority, G);

    return 0;
}

