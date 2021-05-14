#include "astar.hpp"

auto vertexComparator = [](Vertex* vertex1, Vertex* vertex2)
{
    return (vertex1->mark) == (vertex2->mark) ? vertex1->name<vertex2->name : vertex1->mark>vertex2->mark;
};

int heuristic(char a, char b)
{
    return abs(a - b);
}

bool checkLinksInput(char nameOut, char nameIn, double weight)
{
    return std::isalpha(nameOut) && isalpha(nameIn) && weight >= 0;
}

bool checkStartFinishInput(char start, char finish1, char finish2)
{
    return isalpha(start) && isalpha(finish1) && isalpha(finish2) && start != finish1 && start != finish2 && finish2 != finish1;
}

int findVertexIndexByName(const Graph& graph, char name)
{
    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[i]->name == name)
        {
            return i;
        }
    }
    return -1;
}

Graph initGraph(std::istream& in, Vertex** start, Vertex** finish1, Vertex** finish2)
{
    Graph graph;
    char nameVertexOut, nameVertexIn;
    double weight;
    char nameStart, nameFinish1, nameFinish2;

    while (in >> nameStart >> nameFinish1 >> nameFinish2)
    {
        if (checkStartFinishInput(nameStart, nameFinish1, nameFinish2))
        {
            break;
        }
        std::cerr << "Error input" << '\n';
    }
    *start = new Vertex(nameStart);
    *finish1 = new Vertex(nameFinish1);
    *finish2 = new Vertex(nameFinish2);
    graph.push_back(*start);
    graph.push_back(*finish1);
    graph.push_back(*finish2);


    while (in >> nameVertexOut >> nameVertexIn >> weight)
    {
        if (!checkLinksInput(nameVertexOut, nameVertexIn, weight))
        {
            std::cerr << "Error input!" << '\n';
            continue;
        }
        Vertex* vertexOut = new Vertex(nameVertexOut);
        Vertex* vertexIn = new Vertex(nameVertexIn);

        int indexOut = findVertexIndexByName(graph, nameVertexOut);
        if (indexOut == -1)
        {
            graph.push_back(vertexOut);
            indexOut = findVertexIndexByName(graph, nameVertexOut);
        }

        int indexIn = findVertexIndexByName(graph, nameVertexIn);
        if (indexIn == -1)
        {
            graph.push_back(vertexIn);
            indexIn = findVertexIndexByName(graph, nameVertexIn);
        }
        graph[indexOut]->linksHeap.push_back(Link(graph[indexIn], weight));
    }
    return graph;
}

PairPaths findTwoPaths(Graph graph, Vertex* start, Vertex* finish1, Vertex* finish2)
{
    Path pathStartFinish1, pathStartFinish2;
    start->mark = heuristic(start->name, (finish1->name + finish2->name) / 2);
    while (!graph.empty())
    {
        std::make_heap(graph.begin(), graph.end(), vertexComparator);
        Vertex* current = graph.front();
        if (current->mark == DBL_MAX)
        {
            break;
        }
        if (current == finish1 )
        {
            Vertex* temp = current;
            while (temp != start)
            {
                pathStartFinish1.push(temp->name);
                temp = temp->prev;
            }
            pathStartFinish1.push(temp->name);
            if (!pathStartFinish2.empty())
            {
                break;
            }
        }
        if (current == finish2)
        {
            Vertex* temp = current;
            while (temp != start)
            {
                pathStartFinish2.push(temp->name);
                temp = temp->prev;
            }
            pathStartFinish2.push(temp->name);
            if (!pathStartFinish1.empty())
            {
                break;
            }
        }
        for (auto i : current->linksHeap)
        {
            if (i.first->mark > current->mark - heuristic(current->name, (finish1->name + finish2->name) / 2) + i.second)
            {
                i.first->mark = current->mark - heuristic(current->name, (finish1->name + finish2->name) / 2) + heuristic(i.first->name, (finish1->name + finish2->name) / 2) + i.second;
                i.first->prev = current;
            }
        }
        std::pop_heap(graph.begin(), graph.end(), vertexComparator);
        graph.pop_back();
    }
    if (pathStartFinish1.empty() && pathStartFinish2.empty())
    {
        return PairPaths(std::nullopt, std::nullopt);
    }
    if (pathStartFinish1.empty() && !pathStartFinish2.empty())
    {
        return PairPaths(std::nullopt, pathStartFinish2);
    }
    if (!pathStartFinish1.empty() && pathStartFinish2.empty())
    {
        return PairPaths(pathStartFinish1, std::nullopt);
    }
    return PairPaths(pathStartFinish1, pathStartFinish2);
}

std::optional<Path> findPathWithoutOneVertex(Graph graph, Vertex* start, Vertex* finish, Vertex* noneVertex)
{
    Path path;
    start->mark = heuristic(start->name, finish->name);
    while (!graph.empty())
    {
        std::make_heap(graph.begin(), graph.end(), vertexComparator);
        Vertex* current = graph.front();
        if (current->mark == DBL_MAX)
        {
            return std::nullopt;
        }
        if (current == finish)
        {
            while (current != start)
            {
                path.push(current->name);
                current = current->prev;
            }
            path.push(current->name);
            break;
        }
        if (current == noneVertex)
        {
            std::pop_heap(graph.begin(), graph.end(), vertexComparator);
            graph.pop_back();
            continue;
        }
        for (auto i : current->linksHeap)
        {
            if (i.first == noneVertex)
            {
                continue;
            }
            if (i.first->mark > current->mark - heuristic(current->name, finish->name) + i.second)
            {
                i.first->mark = current->mark - heuristic(current->name, finish->name) + heuristic(i.first->name, finish->name) + i.second;
                i.first->prev = current;
            }
        }
        std::pop_heap(graph.begin(), graph.end(), vertexComparator);
        graph.pop_back();
    }
    if (path.empty())
    {
        return std::nullopt;
    }
    return path;
}

void freeMemory(Graph graph)
{
    for (auto i : graph)
    {
        delete i;
    }
}

void printPath(std::optional<Path> path, std::ostream& out)
{
    if (!path)
    {
        out << "could not be found\n";
        return;
    }
    while (!path.value().empty())
    {
        out << path.value().top();
        path.value().pop();
    }
    out << '\n';
}

void clearMarksAndPrev(Graph& graph)
{
    for (auto i : graph)
    {
        i->mark = DBL_MAX;
        i->prev = nullptr;
    }
}

void printAnswer(std::optional<Path> pathStartFinish1, std::optional<Path> pathStartFinish2, std::optional<Path> pathFinish1Finish2, std::optional<Path> pathFinish2Finish1, std::ostream& out)
{
    out << "The path between start and finish1:";
    printPath(pathStartFinish1, out);
    out << "The path between start and finish2:";
    printPath(pathStartFinish2, out);
    out << "The path between finish1 and finish2:";
    printPath(pathFinish1Finish2, out);
    out << "The path between finish2 and finish1:";
    printPath(pathFinish2Finish1, out);
}
