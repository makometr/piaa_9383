#pragma once

#include <iostream>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
//#include <cmath>


class Finding {
private:
    char start;         // исток 
    char end;  //сток
	std::map<char, std::map<char, double>> edges;        // ребра с остаточной пропускной способностью
	std::map<char, std::map<char, double>> capacity;     // ребра с текущим потоком
	std::set<char> visited;  // посещенные вершины
	std::vector<char> path;  //путь

public:
    Finding() {};
    void Read();
    void PrintEdges(const std::map<char, double>& e, const char& vert);
    void PrintFront(const std::queue<char>& f);
    void PrintCapacity();
    bool IsNewFront(const std::queue<char>& nf, char v);
    void FindPath();
    double AlgorithmFF();
};

