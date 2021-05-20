#include "task2.hpp"

int main()
{
    Vertex* root = new Vertex;
    std::string Text, pattern;
    char joker;
    int count = 0;
    input(std::cin, root, Text, pattern, joker);
    addInstances(root, pattern, joker, count);
    addSuffLinks(root);
    Result result = findPos(root, Text, count, pattern.size());
    for (auto i : result)
    {
        std::cout << i << '\n';
    }
    return 0;
}