#include <iostream>
#include <vector>
#include <string>
#include <tuple>

#define INF 1000000

struct Vertex
{
public:
    Vertex* parent;
    char name;
    bool visited;
    int specification, minC;
    std::vector <std::tuple<Vertex*, int, int, bool>> edge;

    Vertex(char nameV, int spec = 1)
    {
        name = nameV;
        specification = spec;
        visited = false;
        parent = nullptr;
        minC = 0;
    }

    void makeEdge(Vertex* v, int cost, bool flag)
    {
        edge.push_back(std::make_tuple(v, cost, cost, flag));
    }
};

Vertex* castomFind(std::vector <Vertex*> graph, char v)
{
    for(int i = 0; i < graph.size(); i++)
    {
        if(graph[i]->name == v)
        {
            return graph[i];
        }
    }
    return nullptr;
}

Vertex* addVertex (std::vector <Vertex*> &graph, char v)
{
    Vertex* ptr = castomFind(graph, v);
    Vertex* ver;
    if(ptr == nullptr)
    {
        ver = new Vertex(v);
        graph.push_back(ver);
        return graph.back();
    }
    return ptr;
}

int getFlag(Vertex* v, int i)
{
    return std::get<3>(v->edge[i]);
}

int getC(Vertex* v, int i)
{
    return std::get<1>(v->edge[i]);
}

int getF(Vertex* v, int i)
{
    return std::get<2>(v->edge[i]);
}

Vertex* getNextVertex(Vertex* v, int i)
{
    return std::get<0>(v->edge[i]);
}

int calcDist(Vertex* v1, Vertex* v2)
{
    return abs(v1->name - v2->name);
}

Vertex* findNextVertex(std::vector <Vertex*> Q, Vertex* u)
{
    int dist = INF, index = -1;

    for(int i = 0; i < Q.size(); i++)
    {
        if(calcDist(u, Q[i]) <= dist)
        {
            if(calcDist(u, Q[i]) == dist)
            {
                if(index == -1)
                {
                    index = i;
                }
                else
                {
                    if(Q[i]->name < Q[index]->name)
                    {
                        index = i;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else
            {
                index = i;
                dist = calcDist(u, Q[i]);
            }
        }
    }
    return Q[index];
}

int findInEdge(Vertex* v, char c)
{
    for(int i = 0; i < v->edge.size(); i++)
    {
        if(getNextVertex(v,i)->name == c)
        {
            return i;
        }
    }
    return -1;
}

int getFactCost(Vertex* v, int i)
{
    int a = getC(v,i) - getF(v,i);
    Vertex* ptr = getNextVertex(v,i);
    if(a > 0)
    {
        return a;
    }
    return 0;
}


void setTrue(std::vector <Vertex*> &graph)
{
    for(auto i : graph)
    {
        i->visited = false;
    }
}

void killParent(std::vector <Vertex*> &graph)
{
    for(auto i : graph)
    {
        i->parent = nullptr;
        i->minC = 0;
    }
}

int comp(const void* v1, const void* v2)
{
    return ((*(Vertex**)v1)->name - (*(Vertex**)v2)->name);
}

int comp2(const void* a, const void* b)
{
    return (std::get<0>(*(std::tuple<Vertex*, int, int, bool>*)a)->name - std::get<0>(*(std::tuple<Vertex*, int, int, bool>*)b)->name);
}

void printGraph(std::vector <Vertex*> graph)
{
    for(auto i : graph)
    {
        if(i->edge.size() != 0)
        {
            std::qsort(&(i->edge[0]), i->edge.size(), sizeof(std::tuple<Vertex*, int, int, bool>), comp2);
            for(int j = 0; j < i->edge.size(); j++)
            {
                if(getFlag(i,j) == true)
                {
                    std::cout<<i->name<<" "<<getNextVertex(i, j)->name<<" "<<getFactCost(i, j)<<"\n";
                }
            }
        }

    }
}

int FFA(Vertex* u, std::vector <Vertex*> &graph)
{
    std::vector <Vertex*> Q;
    int delta = INF;

    while(u->specification != 2)
    {
        u->visited = true;
        u->minC = delta;

        for(int i = 0; i < u->edge.size(); i++)
        {
            if(getNextVertex(u,i)->visited == false && getF(u,i) > 0)
            {
                Q.push_back(getNextVertex(u,i));
            }
        }


        if(Q.size() == 0)
        {
            if(u->specification == 0)
            {
                return 0;
            }
            else
            {
                u = u->parent;
                delta = u->minC;
                continue;
            }
        }

        Vertex* ptr = findNextVertex(Q, u);

        ptr->parent = u;

        int c = getF(u, findInEdge(u, ptr->name));

        if(c < delta)
        {
            delta = c;
        }

        u = ptr;
        Q.clear();
    }

    char c;
    while(u->specification != 0)
    {
        c = u->parent->name;
        std::get<2>(u->edge[findInEdge(u,c)]) += delta;
        c = u->name;
        u = u->parent;
        std::get<2>(u->edge[findInEdge(u,c)]) -= delta;
    }

    return delta;
}

int main()
{
    int n, cost;
    char source, sink, first, second;
    std::vector <Vertex*> graph;
    std::cin>>n;
    std::cin>>source>>sink;
    int index;
    for(int i = 0; i < n; i++)
    {
        std::cin>>first>>second>>cost;

        Vertex* ptr1 = addVertex(graph, first);
        Vertex* ptr2 = addVertex(graph, second);

        if((index = findInEdge(ptr1, ptr2->name)) == -1)
        {
            ptr1->makeEdge(ptr2, cost, true);
        }
        else
        {
            std::get<1>(ptr1->edge[index]) = cost;
            std::get<2>(ptr1->edge[index]) = cost;
            std::get<3>(ptr1->edge[index]) = true;
        }

        if((index = findInEdge(ptr2, ptr1->name)) == -1)
        {
            ptr2->makeEdge(ptr1, 0, false);
        }

    }

    Vertex* ptr = castomFind(graph, source);
    ptr->specification = 0;

    ptr = castomFind(graph, sink);
    ptr->specification = 2;

    Vertex* start = castomFind(graph, source);
    int maxFlow = 0;
    int result;

    while((result = FFA(start,graph)) > 0)
    {
        maxFlow += result;
        setTrue(graph);
        killParent(graph);
    }

    std::cout<<maxFlow<<"\n";


    std::qsort(&graph[0], graph.size(), sizeof(Vertex*), comp);

    printGraph(graph);

    for(int i = 0; i < graph.size(); i++)
    {
        delete graph[i];
    }

    return 0;
}
