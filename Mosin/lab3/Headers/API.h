#pragma once

#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>

bool input(int& count, char& start, char& end, std::map<char, std::map<char, int>>& graph, std::istream& stream);
static std::map<char, std::map<char, int>> transpose_graph(std::map<char, std::map<char, int>>& graph);
static std::pair<std::vector<char>, int> get_path(std::map<char, std::map<char, int>>& rGraph, char s, char t);
static std::pair<std::vector<char>, int> restore_path(std::map<char, std::pair<char, int>>& graph1, std::map<char, std::pair<char, int>>& graph2, char s, char t, char node);
std::pair<int, std::map<char, std::map<char, int>>> FordFulkerson(std::map<char, std::map<char, int>>& graph, char s, char t);