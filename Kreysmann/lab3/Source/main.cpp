#include "ford_fulkerson.hpp"

int main()
{

    Graph graph,flowGraph;
    Vertex*start,*finish;
    std::vector<Vertex*> vertexes;

    std::ifstream file("input.txt");
    graph = initGraph(std::cin,&start,&finish,vertexes);
    file.close();

    flowGraph=graph;

    int maxFlow = FordFulkerson(flowGraph,graph ,start,finish,vertexes);
    printResult(graph,flowGraph,maxFlow,std::cout);

    return 0;
}