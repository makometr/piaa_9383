#include "task1.hpp"

int main()
{
    Vertex* root = new Vertex;
    std::string Text;
    input(std::cin, root, Text);
    addSuffLinks(root);
    Result result = findPos(root, Text);
    std::sort(result.begin(), result.end(), [](auto i, auto j)
        {
            if (i.first != j.first)
            {
                return i.first < j.first;
            }
            return i.second < j.second;
        });
    for (auto i : result)
    {
        std::cout << i.first << ' ' << i.second << '\n';
    }
    std::cout << '\n';

    return 0;
}