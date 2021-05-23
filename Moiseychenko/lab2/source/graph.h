#pragma once

#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>


struct Node
{
    std::vector<std::pair<Node*, float>> neighbours;
    char value;
    float priority;
    Node* prev = nullptr;
    Node(char value, float priority = std::numeric_limits<float>::max()) : value(value), priority(priority) {}
};

void readGraph(std::vector<Node*>& graph, char start, char finish, std::istream& in);
int heuristic_func(char start, char finish);
int findIndex(std::vector<Node*>& graph, char value);
std::string Astar(std::vector<Node*>& graph, char finish);
std::string greedy(std::vector<Node*>& graph, char finish);
std::string vecToString(std::vector<Node*>& vec);
void freeMemory(std::vector<Node*>& vec);
