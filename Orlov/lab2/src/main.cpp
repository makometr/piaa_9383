#include <iostream>
#include <vector>
#include  <algorithm>
#include <string>

#define INF 1000000

struct Vertex
{
public:
    char name;
    Vertex* parent = nullptr;
    bool used;
    float f, h, g, goalDistance, minCost;
    std::vector <std::pair<Vertex*, float>> edge;

    Vertex(char nameV)
    {
        name = nameV;
        f = 0;
        h = 0;
        g = 0;
        goalDistance = 0;
        minCost = 0;
        used = false;
    }

    void makeEdge(Vertex* v, float cost)
    {
        edge.push_back(std::make_pair(v,cost));
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

int heuristic(char first, char second)
{
    return abs(first - second);
}

bool findInQ(std::vector <Vertex*> Q, Vertex v)
{
    for(int i = 0; i < Q.size(); i++)
    {
        if(Q[i]->name == v.name)
        {
            return true;
        }
    }
    return false;
}

std::vector <char> greedy(std::vector <Vertex*> &graph, char start, char finish)
{
    std::vector <char> greedyWay;
    greedyWay.push_back(start);

    Vertex* ptr = castomFind(graph, start);
    Vertex* newPtr = nullptr;
    int minWay = INF;

    while(ptr->name != finish || greedyWay.empty())
    {
        for(auto e : ptr->edge)
        {
            if(e.second < minWay && e.first->used == false)
            {
                minWay = e.second;
                newPtr = e.first;
            }
        }
        if(minWay == INF)
        {
            ptr->used = true;
            greedyWay.pop_back();
            ptr = castomFind(graph, greedyWay.back());
            continue;
        }
        greedyWay.push_back(newPtr->name);
        ptr = newPtr;
        ptr->used = true;
        minWay = INF;

    }
    return greedyWay;
}

bool aStar(std::vector <Vertex*> &graph, char start, char finish)
{
    //a star
    std::vector <Vertex*> Q;
    Q.push_back(castomFind(graph, start));
    Q[0]->g = 0.0;
    Q[0]->f = Q[0]->g + Q[0]->h;
    int index, minF = INF, tentativeScore;
    while(!Q.empty())
    {
        for(int i = 0; i < Q.size(); i++)
        {
            if(Q[i]->f <= minF)
            {
                index = i;
                minF = Q[i]->f;
            }
        }
        minF = INF;

        if(Q[index]->name == finish)
        {
            //---------------
            Vertex* ptr = castomFind(graph, finish);
            Vertex* startPtr = castomFind(graph, start);
            while(ptr != startPtr)
            {
                ptr->parent->goalDistance = ptr->goalDistance + ptr->parent->minCost;
                ptr = ptr->parent;
            }
            //---------------
            return true;
        }

        Q[index]->used = true;
        for(int i = 0; i < Q[index]->edge.size(); i++)
        {
            tentativeScore = Q[index]->g + Q[index]->edge[i].second;
            if(Q[index]->edge[i].first->used == true && tentativeScore >= Q[index]->edge[i].first->g)
            {
                continue;
            }
            if(Q[index]->edge[i].first->used == false || tentativeScore < Q[index]->edge[i].first->g)
            {
                Q[index]->edge[i].first->parent = Q[index];
                //----------
                Q[index]->minCost = Q[index]->edge[i].second;
                //----------
                Q[index]->edge[i].first->g = tentativeScore;
                Q[index]->edge[i].first->f = Q[index]->edge[i].first->g + Q[index]->edge[i].first->h;
                if(findInQ(Q, *Q[index]->edge[i].first) == false)
                {
                    Q.push_back(Q[index]->edge[i].first);
                }
            }
        }
        Q.erase(Q.begin() + index);
    }
    //a star

    for(auto i : graph)
    {
        i->used = false;
    }

    return false;
}

void checkHeuristic(std::vector <Vertex*> graph, char start, char finish)
{
    //valid

    for(auto i : graph)
    {
        aStar(graph, i->name, finish);
    }

    bool flag = true;

    for(auto ptr : graph)
    {
        if(ptr->goalDistance == 0 && ptr->name != finish)
        {
            ptr->goalDistance = INF;
        }
        if(ptr->goalDistance < ptr->h)
        {
            flag = false;
            break;
        }
    }

    if(flag == true)
    {
        std::cout<<"\nHeuristic is valid!\n";
    }
    else
    {
        std::cout<<"\nHeuristic is not valid!\n";
    }


    //monotone

    if(castomFind(graph, finish)->h == 0)
    {
        for(auto v1 : graph)
        {
            for(int i = 0; i < v1->edge.size(); i++)
            {
                if(v1->h - v1->edge[i].first->h > v1->edge[i].second)
                {
                    std::cout<<"\nHeuristic is not monotonic!\n";
                    goto exit;
                }
            }
        }
        std::cout<<"\nHeuristic is monotonic!\n";
    }
    else
    {
        std::cout<<"\nHeuristic is not monotonic!\n";
    }
exit:
    ;

}


int main()
{
    char startV, finishV, firstV, secondV;
    float cost;
    std::vector <Vertex*> graph;

    std::cin>>startV>>finishV;

    while(std::cin>>firstV)
    {
        std::cin>>secondV>>cost;

        Vertex* ptr1 = addVertex(graph, firstV);
        Vertex* ptr2 = addVertex(graph, secondV);

        ptr1->makeEdge(ptr2, cost);
    }

    for(int i = 0; i < graph.size(); i++)
    {
        graph[i]->h = heuristic(graph[i]->name, finishV);
    }


    std::cout<<"A star way:\n";

    bool pathAStar = aStar(graph, startV, finishV);

    if(pathAStar == true)
    {
        Vertex* ptr = castomFind(graph, finishV);
        std::string way;

        Vertex* startPtr = castomFind(graph, startV);

        while(ptr != startPtr)
        {
            way+=ptr->name;
            ptr = ptr->parent;
        }
        way+=ptr->name;

        reverse(way.begin(), way.end());
        std::cout<<way<<"\n\n";
    }
    else
    {
        std::cout<<"No path.\n\n";
    }

    for(auto i : graph)
    {
        i->used = false;
    }

    std::cout<<"Greedy way:\n";

    std::vector <char> greedyWay = greedy(graph, startV, finishV);

    if(!greedyWay.empty())
    {
        for(auto i : greedyWay)
        {
            std::cout<<i;
        }
        std::cout<<"\n";
    }
    else
    {
        std::cout<<"No path.\n";
    }

    for(auto i : graph)
    {
        i->used = false;
    }

    checkHeuristic(graph, startV, finishV);

    for(int i = 0; i < graph.size(); i++)
    {
        delete graph[i];
    }

    return 0;
}
