#include "aho_corasick.h"

int main() {
    std::string text; 
    Node* root = new Node;
    root->suffixLink = root;
    input(text, root, std::cin);
    suffixFunc(root);

    std::vector<std::pair<int, int>> ans = ahoCorasik(text, root);
    printAnswer(ans);
    freeMemory(root);
}