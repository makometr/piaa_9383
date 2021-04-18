#include <iostream>
#include "graph.h"

int main()
{
    char start, end;
    std::cin >> start >> end;
    Graph *graph = new Graph(start, end);
    char v1, v2;
	float h1, h2;
    float weight;
    std::string answer;
	int prevsize = 0;
	float heuristic;

	std::cout << "Input graph in this format: Node1 Node2 Weight Heuristic1 Heuristic2" << std::endl ;
    while (std::cin >> v1 >> v2 >> weight >> h1 >> h2)
    {
		graph->inputNode(v1, v2, abs(weight));
		graph->getNodeByName(v1)->heuristic = h1;
		graph->getNodeByName(v2)->heuristic = h2;
    }
    graph->AStar();
    graph->printAnswer();
    return 0;
}