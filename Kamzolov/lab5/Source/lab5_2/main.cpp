#include "aho_corasick.h"

int main() {
    std::string text, pattern; 
    char joker;
    int count = 0;
    Node* root = new Node;
    root->suffixLink = root;
    input(text, pattern, joker, std::cin);
    splitString(root, pattern, joker, count);
    suffixFunc(root);
    std::vector<int> ans = ahoCorasik(text, root, count, pattern.size());
    printAnswer(ans);
    freeMemory(root);
}