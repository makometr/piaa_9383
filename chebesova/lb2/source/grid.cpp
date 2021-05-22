#include <iostream>
#include <vector>
#include <climits>

int main()
{
    int length_min = INT_MAX;
    char start, end;
    std::cin >> start >> end;
    std::vector<std::pair<char, std::pair<char, float>>> graph;
    std::pair<char, float> best_way;
    char from, to;
    float graph_length;
    std::string answer;
    
    while (std::cin >> from >> to >> graph_length)
    {
        graph.push_back(std::make_pair(from, std::make_pair(to, graph_length)));
    }
    std::cout << "Граф считан корректно\n";
    std::cout << "------------Начало работы жадного алгоритма------------\n";
    while (1)
    {
        answer += start;
        std::cout << "Была добавлена вершина: " << start << "\n";
        
        if (start == end)
        {
            break;
        }
        
        for (int i = 0; i < graph.size(); i++)
        {
            if ((graph[i].first == start) && (graph[i].second.second < length_min))
            {
                length_min = graph[i].second.second;
                best_way = graph[i].second;
            }
        }
        
        if (length_min == INT_MAX)
        {
            answer.erase(answer.size()-1);
            start = answer[answer.size()-1];
            answer.erase(answer.size()-1);
            continue;
        }
        
        start = best_way.first;
        length_min = INT_MAX;
        
        for (int i = 0; i < graph.size(); i++)
        {
            if (graph[i].second.first == start)
            {
                graph.erase(graph.begin()+i);
                i--;
            }
        }
    }
    std::cout << "Результат работы алгоритма:\n";
    std::cout << answer << '\n';
    return 0;
}