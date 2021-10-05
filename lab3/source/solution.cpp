#include "solution.h"

void read_graph(Graph& G)
{
    char out, in;
    float weight;
    while (std::cin >> out >> in >> weight)
    {
        Edge g(in, weight);
        if (G.count(out) == 0)
        {
            std::vector<Edge> d = { g };
            G[out] = d;
        }
        else
        {
            G[out].push_back(g);
            std::sort(G[out].begin(), G[out].end(), [](Edge& p1, Edge& p2) { return (p1.next() < p2.next()); });
        }
    }


}

int Ford_Fulkerson(Graph& G, char start, char finish)
{
    int max_flow = 0;
    bool check_ = check(G, start);
    char cur = start;
    std::string path;
    path.push_back(cur);
    while (check_)
    {
        path = search_path(G, cur, finish, path);
        if (path.empty())
            break;
        int min = search_min_weight(path, G);
        max_flow = max_flow + min;
        decrease_weight(G, path, min);
        create_reversed_edges(G, path, min);
        if (path.size() > 1)
        {
            path.pop_back();
            cur = path.back();
            check_ = check(G, start);
        }
        if (path.size() == 1)
            continue;
        std::string new_path;
        char out = path[0];
        char in = path[1];
        new_path.push_back(out);
        int break_cycle = 0;
        for (int i = 0; i != path.size() - 1; i++)
        {
            for (int j = 0; j != G[out].size(); j++)
            {
                if (G[out][j].next() == in)
                {
                    if (G[out][j].weight() > 0)
                    {
                        new_path.push_back(G[out][j].next());
                        out = G[out][j].next();
                        in = path[i + 2];
                        cur = in;
                        break;
                    }
                    else
                    {
                        cur = new_path[new_path.size() - 1];
                        break_cycle = 1;
                        break;
                    }
                }
            }
            if (break_cycle)
                break;
        }

        for (int i = new_path.size(); i != path.size(); i++)
        {
            out = path[i];
            in = path[i + 1];
            for (int y = 0; y != G[out].size(); y++)
            {
                if (G[out][y].next() == in)
                {
                    G[out][y].isVisited = 0;
                }
            }
        }
        path = new_path;
        if (path.size() >= 1)
        {
            check_ = check(G, start);
        }
        else
        {
            check_ = 0;
            break;
        }
    }
    return max_flow;
}

bool check(Graph G, char start)
{
    for (int i = 0; i != G[start].size(); i++)
    {
        if (G[start][i].weight() > 0)
        {
            return 1;
        }
    }
    return 0;
}

std::string search_path(Graph& G, char cur, char finish, std::string path)
{
    while (cur != finish)
    {
        char now = cur;
        for (int i = 0; i != G[cur].size(); i++)
        {

            int continue_cycle = 0;
            for (int j = 0; j != path.size(); j++)
            {
                if (G[cur][i].next() == path[j])
                {
                    continue_cycle = 1;
                }
            }
            if (continue_cycle)
            {
                continue;
            }

            if ((!G[G[cur][i].next()].empty() && G[cur][i].isVisited == 0 && G[cur][i].weight() > 0) || (G[cur][i].next() == finish && G[cur][i].weight() > 0))
            {
                G[cur][i].isVisited = 1;
                cur = G[cur][i].next();
                path.push_back(cur);
                break;
            }
            else
            {
                G[cur][i].isVisited = 1;
                if (i == (G[cur].size() - 1)) {
                    path.pop_back();
                    cur = path.back();
                    break;
                }
            }
        }
        if (cur == now)
        {
            if (path.size() < 2)
            {
                return path;
            }
            else
            {
                path.pop_back();
                cur = path.back();
            }
        }
    }
    return path;
}

int search_min_weight(std::string path, Graph G)
{
    int min = 10000;
    for (int i = 0; i != path.size() - 1; i++)
    {
        char out = path[i];
        char in = path[i + 1];
        for (int j = 0; j != G[out].size(); j++)
        {
            if (G[out][j].next() == in)
            {
                if (min > G[out][j].weight())
                    min = G[out][j].weight();
            }
        }
    }
    return min;
}

void decrease_weight(Graph& G, std::string path, int min)
{
    for (int i = 0; i != path.size() - 1; i++)
    {
        char out = path[i];
        char in = path[i + 1];

        Edge g(in, min);
        for (int j = 0; j != G[out].size(); j++)
        {
            if (G[out][j].next() == in)
                G[out][j].dec(min);
        }

    }

}

void create_reversed_edges(Graph& G, std::string path, int min)
{
    std::reverse(path.begin(), path.end());
    for (int i = 0; i != path.size() - 1; i++)
    {
        char out = path[i];
        char in = path[i + 1];

        Edge g(in, min);
        if (G.count(out) == 0)
        {
            std::vector<Edge> d = { g };
            G[out] = d;
        }
        else
        {
            int is_find = 0;
            for (int j = 0; j != G[out].size(); j++)
            {
                if (G[out][j].next() == in)
                {
                    G[out][j].inc(min);
                    is_find = 1;
                }
            }

            if (is_find == 0)
            {
                G[out].push_back(g);
                std::sort(G[out].begin(), G[out].end(), [](Edge& p1, Edge& p2) { return (p1.next() < p2.next()); });
            }

        }
    }

}

std::vector <Answer> get_edges(Graph G, Graph G2)
{
    std::vector <Answer> answer;
    for (auto i = G2.begin(); i != G2.end(); i++)
    {
        int l = 0;
        int l2 = 0;

        for (auto j = i->second.begin(); j != i->second.end(); j++)
        {
            char out = i->first;
            char in = j->next();
            int l2 = j->weight();
            int l = 0;
            for (int k = 0; k != G[out].size(); k++)
            {
                if (G[out][k].next() == in)
                    l = l2 - G[out][k].weight();
            }
            if (l < 0)
                l = 0;
            Answer g(out, in, l);
            answer.push_back(g);
        }
    }
    std::sort(answer.begin(), answer.end(), [](Answer& p1, Answer& p2) {
        if (p1.out < p2.out)
        {
            return true;
        }
        if (p1.out == p2.out)
        {
            return (p1.in < p2.in);
        }
        return false;
    });
    return answer;
}
