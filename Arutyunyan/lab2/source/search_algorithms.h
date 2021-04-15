#pragma once

#include <vector>
#include "graph.hpp"

template <typename T>
std::vector<T> GreedyAlgorithm(const Graph<T>& graph, T start, T end);

template <typename T>
std::vector<T> AStarAlgorithm(const Graph<T>& graph, T start, T end);

#include "greedy.hpp"
#include "astar.hpp"