#include <iostream>
#include <map>
#include <algorithm>
#include <queue>
#include <vector>

struct Vertex;
using Links = std::map<char, Vertex*>;
using Result = std::vector<std::pair<int, int>>;
struct Vertex
{
    Links links;
    Vertex* suffixLink = nullptr;
    int terminal = 0;
    int level = 0;
};

void addString(Vertex* root, std::string string, int number);
void addSuffLinks(Vertex* root);
void input(std::istream& in, Vertex* root, std::string& Text);
Vertex* nextVertex(Vertex*vertex,Vertex*root,char symb);
Result findPos(Vertex* root, std::string Text);
