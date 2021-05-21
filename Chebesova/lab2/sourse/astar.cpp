#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <algorithm>

bool cmp_dist_for_queue (const std::tuple<char, char, float> &first, const std::tuple<char, char, float> &second)
{
    if (std::get<2>(first) < std::get<2>(second))
    {
        return false;
    }
    return true;
}

int h (char vertex, char finish) 
{
    return abs(finish - vertex);
}; 

struct Vertex 
{   
    char name;
    float len;
    Vertex(char name, float len)
    {
        this->name = name;
        this->len = len;
    }
};
 
using Graph = std::map<char, std::vector<Vertex>>;

int main()
{
    char start, finish;
    std::cin >> start >> finish;
    char from, to;
    float len;
    Graph graph;
    while (std::cin >> from >> to >> len)
    {
        Vertex new_vertex(to, len);
        graph[from].push_back(new_vertex);
    }
    std::cout << "----------------Начало работы алгоритма А*----------------\n";
    char current_vertex = start;
    float path = 0;
    std::vector<std::tuple<char, char, float>> viewed; 
    std::vector<std::tuple<char, char, float>> queue;
    while (current_vertex != finish)
    {
        for(auto vertex = graph[current_vertex].begin(); vertex != graph[current_vertex].end(); vertex++)
        {
            queue.push_back(std::make_tuple(current_vertex, vertex->name, path + vertex->len + h(vertex->name, finish)));
        }
        std::sort(queue.begin(), queue.end(), cmp_dist_for_queue);
        char from;
        while(!queue.empty())
        {
            from = std::get<0>(queue.back());
            current_vertex = std::get<1>(queue.back());
            path = std::get<2>(queue.back())-h(current_vertex, finish);
            queue.pop_back();
            bool is_shorter = false;
            for(auto vertex = viewed.begin(); vertex != viewed.end(); vertex++)
            {
                if (std::get<1>(*vertex) == current_vertex)
                {
                    if(std::get<2>(*vertex) <= path)
                    {
                        is_shorter = true;
                        break;
                    }
                    else
                    {
                        viewed.erase(vertex);
                        break;
                    }
                }
            }
            if (is_shorter)
            {
                continue;
            }
            else
            {
                break;
            }
        }
        std::cout << "Просмотрен новый путь:\n";
        std::cout << from << " -> " << current_vertex << " с сумарной длиной " << path << "\n";
        viewed.push_back(std::make_tuple(from, current_vertex, path));
    }
    std::string answer;
    answer+=finish;
    current_vertex = finish;
    while(current_vertex != start)
    {
        for (auto vertex = viewed.begin(); vertex != viewed.end(); vertex++)
        {
            if(std::get<1>(*vertex) == current_vertex)
            {
                current_vertex = std::get<0>(*vertex);
                break;
            }
        }
        answer+=current_vertex;
    }
    std::cout << "Результат работы алгоритма:\n";
    std::reverse(answer.begin(), answer.end());
    std::cout << answer << '\n';
    return 0;
}
