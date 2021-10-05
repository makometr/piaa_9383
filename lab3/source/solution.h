#pragma once
#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <algorithm>

class Edge {
public:
    Edge(char next, float weight) {
        this->next_ = next;
        this->weight_ = weight;
        this->isVisited = 0;
    }

    char next()const {
        return this->next_;
    }

    float weight()const {
        return this->weight_;
    }
    void inc(int min) {
        this->weight_ = this->weight_ + min;
    }

    void dec(int min) {
        this->weight_ = this->weight_ - min;
    }

private:
    char next_;
    float weight_;
public:
    int isVisited;
};

using Graph = std::map<char, std::vector<Edge>>;

class Answer {
public:
    Answer(char out_, char in_, int weight_) {
        this->out = out_;
        this->in = in_;
        this->weight = weight_;
    }

public:
    char out;
    char in;
    int weight;
};

void read_graph(Graph& G);
int Ford_Fulkerson(Graph& G, char start, char finish);
bool check(Graph G, char start);
std::string search_path(Graph& G, char cur, char finish, std::string path);
int search_min_weight(std::string path, Graph G);
void decrease_weight(Graph& G, std::string path, int min);
void create_reversed_edges(Graph& G, std::string path, int min);
std::vector <Answer> get_edges(Graph G, Graph G2);
