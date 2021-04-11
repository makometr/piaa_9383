#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;


struct Sorting { //функция сортировки для приоритетной очереди
    bool operator() (pair<char, double> a, pair<char, double> b) {
        //если стоимость двух вершин равна, то возвращается меньшая из них в алфавитном порядке, если стоимость разная, то большая из них
        if (a.second == b.second)
            return (a.first < b.first);
        else
            return (a.second > b.second);
    }
};



class FindingPath {   //класс для поиска кратчайшего пути
public:
    FindingPath() {};
    vector<char> AlgorithmAStar();  //функция, реализующая алгоритм А*
    void Read();  //функция считывания
    int check = 0;  //проверка на неотрицательность введенной эвр. функции

private:
    map<char, vector<pair<char, double>>> graph;  //хранение графа
    map<char, bool> visited;  //посещенные вершины
    char start;
    char end;
    map<char, double> heuristic; //эвристические функции
};

