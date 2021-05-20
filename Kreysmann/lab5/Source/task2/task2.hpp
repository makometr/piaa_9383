#include <iostream>
#include <map>
#include <algorithm>
#include <queue>
#include <vector>

struct Vertex;
using Links = std::map<char, Vertex*>;
using Result = std::vector<int>;
struct Vertex
{
    Links links;
    Vertex* suffixLink = nullptr;
    std::vector<int> offsets;
};
void addString(Vertex* root, std::string string, int offset);
void addSuffLinks(Vertex* root);
void input(std::istream& in, Vertex* root, std::string& Text, std::string& pattern, char& joker);
Vertex* nextVertex(Vertex* vertex, Vertex* root, char symb);
Result findPos(Vertex* root, std::string Text, int count, int patternSize);
void addInstances(Vertex* root, std::string pattern, char joker, int& count);
