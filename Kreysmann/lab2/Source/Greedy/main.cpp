#include "greedy.hpp"

int main()
{  
    Vertex* start,*finish;
    std::ifstream file("Input.txt");
    Graph graph = initGraph(file,&start,&finish);
    file.close();
    std::optional<Path> path = findPath(start,finish);
    if(path)
    {
        printPath(path.value(),std::cout);
    }
    else
    {
        std::cerr<<"the path does not exist"<<'\n';
    }

    freeMemory(graph);
    return 0;
}