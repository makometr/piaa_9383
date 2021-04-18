#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class Graph {
public:
    char start, end;
    float weight;
    bool correct;
    Graph() : start('\0'), end('\0'), weight(-1), correct(true) {};
    Graph(char from, char to, double weight) : start(from), end(to), weight(weight), correct(true) {}
};

int findMinPath(std::vector<Graph>& graph, char start, int min_weight, std::vector<char> corr_path);
void Greedy(std::vector<Graph>& graph, char start, char end, std::vector<char>& corr_path);
std::string getAnswer(std::vector<char> path);