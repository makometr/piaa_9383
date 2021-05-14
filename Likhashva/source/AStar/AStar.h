#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <queue>



auto Sorting = [](std::pair<char, double> a, std::pair<char, double> b) -> bool { //lambda-выражение для сортировки в приоритетной очереди
    if (a.second == b.second)
        return (a.first < b.first);
    else
        return (a.second > b.second);
};


class FindingPath {   //класс для поиска кратчайшего пути
public:
    FindingPath() {};
    std::vector<char> AlgorithmAStar();  //функция, реализующая алгоритм А*
    void Read();  //функция считывания
    int check = 0;  //проверка на неотрицательность введенной эвр. функции

private:
    std::map<char, std::vector<std::pair<char, double>>> graph;  //хранение графа
    std::map<char, bool> visited;  //посещенные вершины
    char start;
    char end;
    std::map<char, double> heuristic; //эвристические функции
};

