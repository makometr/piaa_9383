#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

bool mycmp(std::pair<char, std::pair<char, int>> a, std::pair<char, std::pair<char, int>> b)
{
    return a.second.second < b.second.second;
}

void readData(std::map<char, std::map<char, std::pair<int, bool>>> &Graph, char &v0, char &vn)
{
    int N;
    std::cin >> N;
    std::cin >> v0 >> vn;
    char source, distination;
    int weight;
    for (int i = 0; i < N; i++)
    {
        std::cin >> source >> distination >> weight;
        Graph[source][distination].first = weight;
        Graph[source][distination].second = true;
        if (!Graph[distination][source].first)
        {
            Graph[distination][source].first = 0;
            Graph[distination][source].second = false;
        }
    }
}

bool BFS(std::map<char, std::map<char, std::pair<int, bool>>> &Graph, std::map<char, char> &close, char &v0, char &vn)
{
    std::vector<std::pair<char, std::pair<char, int>>> open;
    std::pair<char, int> cur_item;
    //Для первой вершины(исток)
    for (auto it = Graph[v0].begin(); it != Graph[v0].end(); ++it)
    {
        if (it->second.first != 0)
            open.push_back(std::make_pair(v0, std::make_pair(it->first, it->second.first)));
    }
    close[v0] = '.'; //специально для истока - предыдущий к нему.

    //запускаем обход вершин
    while (1)
    {
        sort(open.begin(), open.end(), mycmp);                       //сортируем открытый список по длине ребер
        std::vector<std::pair<char, std::pair<char, int>>> tmp_open; // first - откуда пришли, second.first - сама вершина, second.second - расстояние до неё от предыдущей
        while (!open.empty())
        {
            cur_item = open.back().second;                 //достаем наиболее приоритетную вершину
            if (close.find(cur_item.first) != close.end()) //в случае если вершина была повторно внесена в открытый список(как ребенок), то пропускаем её
            {
                open.pop_back();
                continue;
            }
            if (cur_item.first == vn) //если эта вершина - конечная, то возвращаем её
            {
                close[vn] = open.back().first;
                return true;
            }
            close[cur_item.first] = open.back().first;                                             //добавляем вершину в закрытый список
            open.pop_back();                                                                       //убираем вершину из открытого списка
            for (auto it = Graph[cur_item.first].begin(); it != Graph[cur_item.first].end(); it++) //проходимся по всем детям этой вершины
            {
                if (it->second.first != 0)                    //если расстояние до ребенка = 0, то пропускаем её(дороги нет)
                    if (close.find(it->first) == close.end()) //если вершины нет в закрытом списке, то добавляем её к открытым
                    {
                        tmp_open.push_back(std::make_pair(cur_item.first, std::make_pair(it->first, it->second.first)));
                    }
            }
        }
        open = tmp_open; //обновляем список открытых
        if (open.empty())
        {
            return false; //если ни одного пути не было найдено
        }
        tmp_open.clear(); //отчищаем временный список
    }
}

int findMinFlox(std::map<char, std::map<char, std::pair<int, bool>>> &Graph, std::map<char, char> &close, char &vn)
{
    int minValue = Graph[close[vn]][vn].first;
    char cur_vertex = vn;
    int tmp_value;
    while (close[cur_vertex] != '.')
    {
        tmp_value = Graph[close[cur_vertex]][cur_vertex].first;
        cur_vertex = close[cur_vertex];
        if (tmp_value < minValue)
            minValue = tmp_value;
    }
    return minValue;
}

int restorePath(std::map<char, std::map<char, std::pair<int, bool>>> &Graph, std::map<char, char> &close, char &vn)
{
    char cur_vertex = vn;
    int minValue = findMinFlox(Graph, close, vn);
    while (close[cur_vertex] != '.')
    {
        Graph[close[cur_vertex]][cur_vertex].first -= minValue;
        Graph[cur_vertex][close[cur_vertex]].first += minValue;
        cur_vertex = close[cur_vertex];
    }
    return minValue;
}

int ff(std::map<char, std::map<char, std::pair<int, bool>>> &Graph, char &v0, char &vn)
{
    std::map<char, char> close;
    int maxFlow = 0;
    while (1)
    {
        if (BFS(Graph, close, v0, vn))
            maxFlow += restorePath(Graph, close, vn);
        else
            return maxFlow;
        close.clear();
    }
    return maxFlow;
}

int main()
{
    char v0, vn;
    std::map<char, std::map<char, std::pair<int, bool>>> Graph;
    readData(Graph, v0, vn);
    std::map<char, std::map<char, std::pair<int, bool>>> Graph_tmp = Graph;
    int max = ff(Graph_tmp, v0, vn);
    // Graph_print
    std::cout << max << '\n';
    auto jt = Graph_tmp.begin();
    for (auto it = Graph.begin(); it != Graph.end(); ++it, ++jt)
    {
        auto j = jt->second.begin();
        for (auto i = it->second.begin(); i != it->second.end(); ++j, ++i)
        {
            if (i->second.second)
                if (i->second.first - j->second.first >= 0)
                    std::cout << it->first << ' ' << i->first << ' ' << (i->second.first - j->second.first) << '\n';
                else
                    std::cout << it->first << ' ' << i->first << ' ' << 0 << '\n';
        }
    }
}