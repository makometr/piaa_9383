#include <iostream>
#include <vector>

int main()
{
    std::string result;
    char start, end;
    int min_l = 10000;
    std::cin >> start >> end;
    std::vector<std::pair<char, std::pair<char, float>>> edges;
    std::pair<char, float> best_edge;
    char edge_s, edge_f;
    float edge_l;
    while (std::cin >> edge_s >> edge_f >> edge_l)
    {
        edges.push_back(std::make_pair(edge_s, std::make_pair(edge_f, edge_l)));
    }
    while (1)
    {
        result += start;
        if (start == end)
            break;
        if (edges.empty())
        {
            std::cout << "No way!";
            return 0;
        }
        for (int i = 0; i < edges.size(); i++)
        {
            if (edges[i].first == start)
                if (edges[i].second.second < min_l)
                {
                    min_l = edges[i].second.second;
                    best_edge = edges[i].second;
                }
                else if (result.length() == 1 && i == edges.size() - 1)
                {
                    std::cout << "No way!";
                    return 0;
                }
        }
        if (min_l == 10000)
        {
            result.erase(result.size() - 1);
            start = result[result.size() - 1];
            result.erase(result.size() - 1);
            continue;
        }
        start = best_edge.first;
        min_l = 10000;
        for (int i = 0; i < edges.size(); i++)
            if (edges[i].second.first == start)
            {
                edges.erase(edges.begin() + i);
                i--;
            }
    }
    std::cout << result;
    return 0;
}