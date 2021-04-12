#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

class Node;

class Neighbour{
public: 
    Neighbour(Node* nodeName, float weight) : nodeName(nodeName), weight(weight) {};
    Node* nodeName;
    float weight;
};

class Node{
public:
    Node(char name) : name(name) {};
    char name;
    float heuristic = __FLT_MAX__, cost = __FLT_MAX__;
    std::vector<Neighbour*> neighbours;
    Node* cameFrom = nullptr;
};

class Graph{
public:
    Graph(char start, char end) : start(start), end(end) {};

    void inputNode(char first, char second, float weight); 
    //void setHeuristic();

    Node* getNodeByName(char name);
    int getIndexByNode(Node* node);
    Node* getMinNode();
    std::vector<Node *> getNodes();

    void printGraph();
    void printNodes();
    void printAnswer();
    std::string getAnswer();

    void AStar();

private:
    char start, end;
    std::vector<Node *> nodes;

    Node *startNode, *endNode;
};