#include "astar.hpp"

int main()
{
    Vertex* start, * finish1, * finish2;
    std::ifstream file("Input.txt");
    Graph graph = initGraph(file, &start, &finish1, &finish2);

    file.close();

    PairPaths paths = findTwoPaths(graph, start, finish1, finish2);
    
    std::optional<Path> path1to2;
    std::optional<Path> path2to1;
    if (paths.first && paths.second)
    {
        clearMarksAndPrev(graph);
        path1to2 = findPathWithoutOneVertex(graph, finish1, finish2, start);
        clearMarksAndPrev(graph);
        path2to1 = findPathWithoutOneVertex(graph, finish2, finish1, start);
    }
    
    printAnswer(paths.first, paths.second, path1to2, path2to1, std::cout);
    freeMemory(graph);
    return 0;
}
