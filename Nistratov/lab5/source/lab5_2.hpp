#include <iostream>
#include <map>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>

struct BorTree;
using Edges = std::map<char, BorTree*>;
using Result = std::vector<int>;

struct BorTree
{
    Edges links;
    BorTree* suffixLink = nullptr;
    std::vector<int> pos_of_split_pattern;
};

class AhoCorasick
{
private:
    BorTree* root;
    std::string text, pattern;
    int split_pattern_ammount = 0;
    Result result;

    std::stack<BorTree*> alloc;
public:
    AhoCorasick(std::string str, std::string ptrn) : root(new BorTree), text(str), pattern(ptrn){};

    ~AhoCorasick() {
        while (!alloc.empty()){
            auto a = alloc.top();
            alloc.pop();
            delete a;
        }
        delete root;
    };

    void addPattern(std::string str, int level);

    void createSuffixLinks();

    void split_by_joker(char joker);

    Result find_ak();
};
