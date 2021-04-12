#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <fstream>
#include <optional>
#include <stack>
#include <cfloat>

struct Vertex;
using Link = std::pair<Vertex*, double>;
using Links = std::vector<Link>;
using Graph = std::vector<Vertex*>;
using Path = std::stack<char>;
using PairPaths = std::pair<std::optional<Path>, std::optional<Path>>;
struct Vertex
{
    Vertex(char name = ' ') :name(name) {}
    char name;
    Links linksHeap;
    Vertex* prev = nullptr;
    double mark = DBL_MAX;
};

int heuristic(char a, char b);
bool checkLinksInput(char nameOut, char nameIn, double weight);
bool checkStartFinishInput(char start, char finish1, char finish2);
int findVertexIndexByName(const Graph& graph, char name);
Graph initGraph(std::istream& in, Vertex** start, Vertex** finish1, Vertex** finish2);
PairPaths findTwoPaths(Graph graph, Vertex* start, Vertex* finish1, Vertex* finish2);
std::optional<Path> findPathWithoutOneVertex(Graph graph, Vertex* start, Vertex* finish, Vertex* noneVertex);
void freeMemory(Graph graph);
void printPath(std::optional<Path> path, std::ostream& out);
void clearMarksAndPrev(Graph& graph);
void printAnswer(std::optional<Path> pathStartFinish1, std::optional<Path> pathStartFinish2, std::optional<Path> pathFinish1Finish2, std::optional<Path> pathFinish2Finish1, std::ostream& out);

