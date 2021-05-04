#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>

struct Edge{
    int flow = 0;
    int usedFlow = 0;
    int index = 0;
    bool isInit = false;
    bool isVisited = false;
};

using Neighbour = std::pair<char, Edge>;

inline bool neighbour_cmp(Neighbour a, Neighbour b);

class Graph{
public:

    Graph(char source_node_symbol, char sink_node_symbol, int edges_amount);
    ~Graph();

    bool read_edges(std::istream& in);

    std::string to_string();

    std::string print_res_graph();

    int ford_fulkerson();

    std::vector<char> test_find_path(char start_symbol, char end_symbol);

private:
    char source_symbol_;
    char sink_symbol_;
    int edges_amount_;

    std::map<char, std::vector<Neighbour>> graph_map_;
    std::map<char, char> prev_node_map_;

    int find_flow_path(char start_symbol, char end_symbol, std::map<char, bool> is_visited_map, int result);
    std::vector<char> get_flow_path();

};

#endif