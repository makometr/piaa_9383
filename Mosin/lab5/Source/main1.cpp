#include "lab5_1.h"

int main(int argc, char *argv[]) {
    std::string text;
    std::cin >> text;

    int count;
    std::cin >> count;
    
    Trie* root = new Trie;
    std::string string;
    for (int i = 0; i < count; ++i) {
        std::cin >> string;
        add(root, string, i+1);
    }
    build(root);

    std::vector<std::pair<int, int>> result = Aho_Corasick(root, text);
    std::sort(result.begin(), result.end(), [](std::pair<int, int>& a, std::pair<int, int>& b) -> bool {return a.first == b.first ? a.second < b.second : a.first < b.first;});
    for (auto it : result) {
        std::cout << it.first << " " << it.second << std::endl;
    }

    delete root;
    return 0;
}