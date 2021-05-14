#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <fstream>
#include <optional>
#include <stack>
#include <deque>

struct Vertex;
using Link    = std::pair<Vertex*,double>;
using Links   = std::vector<Link>;
using Graph   = std::vector<Vertex*>;
using Path    = std::deque<char>;


struct Vertex
{
    Vertex(char name= ' '):name(name) {}
    char name;
    Links linksHeap;
    Vertex* prev = nullptr;
};

bool checkInput(char nameOut,char nameIn, double weight);
int findVertexIndexByName(const Graph& graph,char name);
Graph initGraph(std::istream& in,Vertex** start,Vertex** finish);
std::optional<Path> findPath(Vertex *start,Vertex *finish);
void freeMemory(Graph graph);
void printPath(Path path,std::ostream &out);

