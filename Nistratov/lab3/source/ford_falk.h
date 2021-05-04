#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

#define EDGE_MAP std::map<char, std::map<char, int>>

class FFsolver
{
public:
    FFsolver() {};

    EDGE_MAP edges;
    char start, finish;
    std::vector<char> visited, cameFrom;

    std::pair<int, EDGE_MAP> FordFulkerson();

    void print_edges(EDGE_MAP cEdges);

    void input();

    void setInput(std::stringstream& ss);

    bool isVisited(char node);

    bool findPath(EDGE_MAP& cEdges);

    char findMaxFlow(std::map<char, int> node);
};