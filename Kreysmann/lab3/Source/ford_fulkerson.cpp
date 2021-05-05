#include "ford_fulkerson.hpp"

void currentResult(Graph flowGraph,Graph graph,Path path,int maxFlow, int pathFlow)
{
    std::cout << "Найденный путь: ";
    for(auto i : path)
    {
        std::cout<<i->name<<' ';
    }
    std::cout<<'\n';

    std::cout<<"Поток пути: "<<pathFlow<<'\n';
    std::cout<<"Текущий максимальный поток:"<<maxFlow<<'\n';
    std::cout<<"Поток через ребра графа:"<<'\n';
    for(auto i:graph)
    {
        for (auto j:i.second)
        {
            int flow = std::max(0,j.second - flowGraph[i.first][j.first]);
            std::cout << i.first->name <<' ' << j.first->name <<' '<< flow <<'\n';
        }
    }
}

Path findPath(Vertex *start, Vertex *finish,Graph& graph)
{
    std::cout<<"\nПросмотренные ребра при поиске нового пути:"<<'\n';

    Path path;
    std::queue<Vertex*> q;
    q.push(start);
    while(!q.empty())
    {
        Vertex *temp = q.front();
        q.pop();
        for(auto i:graph[temp])
        {
            if(!i.first->visited && graph[temp][i.first]>0)
            { 
                q.push(i.first);
                i.first->visited=true;
                i.first->prev=temp;

                std::cout<<"Ребро:("<<temp->name<<","<<i.first->name<<"), пропускная способность : "<<graph[temp][i.first]<<'\n';

                if(i.first->name==finish->name)
                {
                    Vertex* t = i.first;
                    while(t->name!=start->name)
                    {
                        path.push_back(t);
                        t=t->prev;
                    }
                    path.push_back(t);
                    std::reverse(path.begin(),path.end());
                    return path;
                }
            }
        }
    }
    return path;
}

int FordFulkerson(Graph &graph,Graph &originGraph,Vertex*start,Vertex*finish,std::vector<Vertex*> vertexes)
{
    Path path;
    int maxFlow = 0;
    while(!((path=findPath(start,finish,graph)).empty()))
    {
        for(auto i:vertexes)
        {
            i->visited=false;
        }

        int min=-1;
        for(int i = 0 ;i<path.size()-1;i++)
        {
            if(graph[path[i]][path[i+1]]<min  || min==-1)
            {
                min = graph[path[i]][path[i+1]];
            }
        }
        maxFlow+=min;

        for(int i = 0 ;i<path.size()-1;i++)
        {
            graph[path[i]][path[i+1]]-=min;
            graph[path[i+1]][path[i]]+=min;
        }
        
        currentResult(graph,originGraph,path,maxFlow,min);
    }
    return maxFlow;
}

int indexByName(std::vector<Vertex*> vec,char name)
{
    for(int i = 0 ;i<vec.size();i++)
    {
        if(vec[i]->name==name)
        {
            return i;
        }
    }
    return -1;
}

Graph initGraph(std::istream& in, Vertex** start, Vertex** end,std::vector<Vertex*> &vertexes)
{
    Graph graph;
    int weight,size;
    char nameStart, nameEnd;
    in >> size >> nameStart >> nameEnd;
        
    *start = new Vertex(nameStart);
    *end = new Vertex(nameEnd);
    vertexes.push_back(*start);
    vertexes.push_back(*end);

    for (int i = 0 ;i<size;i++)
    {
        char nameVertexOut,nameVertexIn;
        in >> nameVertexOut >> nameVertexIn >> weight;

        int indStart=indexByName(vertexes,nameVertexOut);
        int indFinish=indexByName(vertexes,nameVertexIn);
        
        Vertex *vertexOut = indStart==-1 ? new Vertex(nameVertexOut) : vertexes[indStart];
        Vertex *vertexIn  = indFinish==-1 ? new Vertex(nameVertexIn) : vertexes[indFinish];
        if(indStart==-1)
        {
            vertexes.push_back(vertexOut);
        }
        if(indFinish==-1)
        {
            vertexes.push_back(vertexIn);
        }

        graph[vertexOut][vertexIn]=weight;
    }
    return graph;
}

void printResult(Graph &graph,Graph &flowGraph,int maxFlow,std::ostream& out)
{
    out<<"\nРезультат:\n";
    out<<"Максимальный поток: "<<maxFlow<<'\n';
    out<<"Потоки через ребра графа:\n";
    for(auto i:graph)
    {
        for (auto j:i.second)
        {
            int flow = std::max(0,j.second - flowGraph[i.first][j.first]);
            out << i.first->name <<' ' << j.first->name <<' '<< flow <<'\n';
        }
    }
}