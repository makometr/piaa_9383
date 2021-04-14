#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <queue>



class FindingPath {
public:
    FindingPath() {};
    std::vector<char> GreedyAlgorithm();
    void Read();

private:
    std::map<char, std::vector<std::pair<char, double>>> graph;
    std::map<char, bool> visited;
    char start;
    char end;
    int number;
};

