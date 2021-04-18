#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>

struct Edge;

struct Vertex{
    char name;
    std::vector<Edge> edges_arr;
    Vertex* prev;
    bool isVisited = false;
    float priority = __FLT_MAX__;
};

struct Edge{
    Vertex* end_vertex;
    float weight;
};

class Graph{
public:

    Graph(char start_vertex, char end_vertex);
    ~Graph();

    std::string find_path_a_star();
    std::string find_path_greedy();

    bool read_edges(std::istream& in);

    std::string print_vector_to_string();

    float heuristics(const char& start, const char& finish);

private:
    char start_vertex_symbol_, end_vertex_symbol_;

    std::vector<Vertex*> vertices_arr_;
    std::vector<Vertex*> utility_vector_;

    Vertex* start_vertex_;
    Vertex* end_vertex_;

    std::string path_;


    Vertex* get_vertex_from_vector(char target_vertex_name);
    
};