#include "lb3.hpp"

int main(){
    char start, finish;
    int N;
    std::cin>>N;
    std::cin>>start;
    std::cin>>finish;
    Graph G, G2;
    Read_inform_about_edge(G);
    G2 = G; //для хранения исначальных данных
    int max_potok = Algoritm(G, start, finish);
    std::cout << max_potok << "\n";
    std::vector <answ> result = for_answer(G, G2);
    for (int i = 0; i!=result.size(); i++){
        std::cout << result[i].source << " " << result[i].dest << " " << result[i].metrika << "\n";
    }
    return 0;
}
