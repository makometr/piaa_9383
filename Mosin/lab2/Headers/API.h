#pragma once

#include "iostream"
#include "string"
#include "map"
#include "unordered_map"
#include "algorithm"
#include "vector"
#include "queue"

bool input(std::map<char, std::vector<std::pair<char, float>>>& graph, char& start, char& end, std::istream& stream);
bool possible(std::map<char, std::vector<std::pair<char, float>>>& graph, std::string& current, char from, char link, char end);

namespace Greed {
    std::string way(std::map<char, std::vector<std::pair<char, float>>>& graph, char start, char end);
}

namespace Star {
    std::string way(std::map<char, std::vector<std::pair<char, float>>>& graph, char start, char end);
    int heuristic(char a, char b);
}