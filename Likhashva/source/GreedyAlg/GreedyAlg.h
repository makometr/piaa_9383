#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;


class FindingPath {
public:
    FindingPath() {};
    vector<char> GreedyAlgorithm();
    void Read();

private:
    map<char, vector<pair<char, double>>> graph;
    map<char, bool> visited;
    char start;
    char end;
    int number;
};

