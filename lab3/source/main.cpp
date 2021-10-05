#include "solution.h"

int main()
{
    char start, finish;
    int N;
    std::cin >> N;
    std::cin >> start;
    std::cin >> finish;
    Graph G, G2;
    read_graph(G);
    G2 = G;
    int max_flow = Ford_Fulkerson(G, start, finish);
    std::cout << max_flow << "\n";
    std::vector <Answer> answer = get_edges(G, G2);
    for (int i = 0; i != answer.size(); i++) {
        std::cout << answer[i].out << " " << answer[i].in << " " << answer[i].weight << "\n";
    }
	return 0;
}