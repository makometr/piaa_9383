#include <iostream>
#include <map>
#include <algorithm>
#include <queue>
#include <vector>

struct BorTree;
using Edges = std::map<char, BorTree*>;
using Result = std::vector<std::pair<int, int>>;

struct BorTree
{
    Edges links;
    BorTree* suffixLink = nullptr;
    int term = 0;
    int depth = 0;
};

class AhoCorasick
{
private:
    BorTree* root;
    std::string text;
    Result result;
    
public:
    AhoCorasick(std::string str) : root(new BorTree), text(str) {};

    void addPattern(std::string str, int pattern_state);

    void createSuffixLinks();

    Result find_ak();
};