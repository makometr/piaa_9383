#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <fstream>

struct Vertex
{
    Vertex(char name = ' ') :name(name) {}
    char name;
    bool visited = false;
    Vertex* prev = nullptr;
};
struct cmpVertexes
{
    bool operator()(Vertex* v1,Vertex* v2)
    {
        return v1->name<v2->name;
    }
};
using Graph = std::map<Vertex*,std::map<Vertex*,int,cmpVertexes>,cmpVertexes>;
using Path  = std::vector<Vertex*>;
void currentResult(Path path,int maxFlow, int pathFlow);
Path findPath(Vertex *start, Vertex *finish,Graph& graph);
int FordFulkerson(Graph &graph,Graph &originGraph,Vertex*start,Vertex*finish,std::vector<Vertex*> vertexes);
int indexByName(std::vector<Vertex*> vec,char name);
Graph initGraph(std::istream& in, Vertex** start, Vertex** end,std::vector<Vertex*> &vertexes);
void printResult(Graph &graph,Graph &flowGraph,int maxFlow,std::ostream& out);
