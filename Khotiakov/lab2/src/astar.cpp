#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>

int calcH(const int &cur, const int &end)
{
    return abs(cur - end);
}

struct Vertex
{
    int prev;
    int name;
    float f, g;
    int h;
    Vertex(int name, float g, int end) : name(name), g(g)
    {
        h = calcH(name, end);
        f = g + h;
    }
};

bool operator<=(const Vertex &a, const Vertex &b)
{
    return a.f <= b.f;
}
bool operator>=(const Vertex &a, const Vertex &b)
{
    return a.f >= b.f;
}
bool operator==(const Vertex &a, const Vertex &b)
{
    return a.name == b.name;
}

void readData(std::vector<std::pair<int, std::pair<int, float>>> &edges)
{
    int edge_s, edge_f;
    float edge_l;
    while (std::cin >> edge_s >> edge_f >> edge_l)
    {
        edges.push_back(std::make_pair(edge_s, std::make_pair(edge_f, edge_l)));
    }
}

bool inClose(const std::vector<int> &close, int name)
{
    for (int i = 0; i < close.size(); i++)
        if (name == close[i])
            return true;
    return false;
}

void addToQueue(std::priority_queue<Vertex, std::vector<Vertex>, std::greater_equal<Vertex>> &open, std::vector<std::pair<int, std::pair<int, float>>> &edges, std::vector<int> &close, Vertex &cur, int &end, std::vector<Vertex> &Vertex_arr)
{
    for (int i = 0; i < edges.size(); i++)
    {
        if (cur.name == edges[i].first)
            if (inClose(close, edges[i].second.first))
                continue;
            else
            {
                Vertex x(edges[i].second.first, edges[i].second.second + cur.g, end);
                x.prev = Vertex_arr.size() - 1;
                open.push(x);
            }
    }
}

void restorePath(Vertex end, std::vector<Vertex> &Vertex_arr)
{
    Vertex cur = end;
    std::vector<int> res;
    while (1)
    {
        if (cur.prev == -1)
        {
            res.push_back(cur.name);
            break;
        }
        res.push_back(cur.name);
        cur = Vertex_arr[cur.prev];
    }
    for (int i = res.size() - 1; i >= 0; i--)
        std::cout << res[i] << ' ';
}

void findWay(std::vector<std::pair<int, std::pair<int, float>>> &edges, int &start, int &end)
{
    std::vector<int> close;
    std::priority_queue<Vertex, std::vector<Vertex>, std::greater_equal<Vertex>> open;
    std::vector<Vertex> Vertex_arr;
    Vertex cur(start, 0, 0);
    cur.prev = -1;
    open.push(cur);
    while (cur.name != end && !open.empty())
    {
        cur = open.top();
        if (inClose(close, cur.name))
        {
            open.pop();
            continue;
        }
        Vertex_arr.push_back(cur);
        open.pop();
        addToQueue(open, edges, close, cur, end, Vertex_arr);
    }
    if (open.empty())
    {
        std::cout << "No way!";
        return;
    }
    restorePath(cur, Vertex_arr);
}

int main()
{
    int start, end;
    std::cin >> start >> end;

    std::vector<std::pair<int, std::pair<int, float>>> edges;
    readData(edges);
    findWay(edges, start, end);

    return 0;
}