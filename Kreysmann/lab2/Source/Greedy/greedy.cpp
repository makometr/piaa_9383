#include "greedy.hpp"

auto linkComparator = [](Link link1,Link link2)
{
    return link1.second>link2.second;
};

bool checkInput(char nameOut,char nameIn, double weight)
{
    return std::isalpha(nameOut) && isalpha(nameIn) && weight>=0;
}

int findVertexIndexByName(const Graph& graph,char name)
{
    for(int i = 0 ;i <graph.size(); i++)
    {
        if(graph[i]->name==name)
        {
            return i;
        }
    }
    return -1;
}

Graph initGraph(std::istream& in,Vertex** start,Vertex** finish)
{
    Graph graph;
    char nameVertexOut,nameVertexIn;   
    double weight;
    char nameStart,nameFinish;
    while(in>>nameStart>>nameFinish)
    {   
        if(isalpha(nameStart) && isalpha(nameFinish))
        {
            break;
        }
        std::cerr<<"Error input"<<'\n';
    }
    *start = new Vertex(nameStart);
    *finish  = new Vertex(nameFinish);
    graph.push_back(*start);
    graph.push_back(*finish);

    while(in>>nameVertexOut>>nameVertexIn>>weight)
    {
        if(!checkInput(nameVertexOut,nameVertexIn,weight))
        {
            std::cerr<<"Error input!"<<'\n';
            continue;
        }
        Vertex *vertexOut = new Vertex(nameVertexOut);
        Vertex *vertexIn = new Vertex(nameVertexIn);

        int indexOut = findVertexIndexByName(graph,nameVertexOut);
        if(indexOut==-1)
        {
            graph.push_back(vertexOut);
            indexOut = findVertexIndexByName(graph,nameVertexOut);
        }
        
        int indexIn = findVertexIndexByName(graph,nameVertexIn);
        if(indexIn==-1)
        {
            graph.push_back(vertexIn);
            indexIn = findVertexIndexByName(graph,nameVertexIn);
        }
        graph[indexOut]->linksHeap.push_back(Link(graph[indexIn],weight));
        std::push_heap(graph[indexOut]->linksHeap.begin(),graph[indexOut]->linksHeap.end(),linkComparator);
    }
    return graph;
}

std::optional<Path> findPath(Vertex *start,Vertex *finish)
{
    Path path;
    Vertex *current = start;
    path.push_back(current->name);
    while(current->prev!=nullptr || !current->linksHeap.empty())
    {
        if(current==finish)
        {
            break;
        }
        if(!(current->linksHeap.empty()))
        {
            Vertex *next=current->linksHeap[0].first;
            next->prev=current;
            std::pop_heap(current->linksHeap.begin(),current->linksHeap.end(),linkComparator);
            current->linksHeap.pop_back();
            current = next;
            path.push_back(current->name);
            continue;
        }
        else
        {
            Vertex* temp = current;
            current = current->prev;
            temp->prev = nullptr;
            path.pop_back();
        }
    }
    if(current!=finish)
    {
        return std::nullopt;
    }
    return path;
}

void freeMemory(Graph graph)
{
    for(auto i : graph)
    {
        delete i;
    }
}

void printPath(Path path,std::ostream &out)
{
    while(!path.empty())
    {
        out<<path.front();
        path.pop_front();
    }
}
