#ifndef AHO_KORASICK_H
#define AHO_KORASICK_H

#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>


struct Node {
    std::map<char, Node*> next;
    Node* suffixLink = nullptr;
    Node* endLink = nullptr;
    bool isTerminal = false;
    char symbol = '\0';
    int stringNumber = -1;
    std::vector<int> stringNumbers;
    int wordSize = 0;
};

bool comparator(std::pair<int, int> first, std::pair<int, int> second);
void findSuffixLink(Node* node, Node* root, char symbol);
void suffixFunc(Node* root);
void wordToTrie(Node* root, std::string& word, int number);
void input(std::string& text, Node* root, std::istream& in);
std::vector<std::pair<int, int>> ahoCorasik(std::string& text, Node* root);
void printAnswer(std::vector<std::pair<int, int>>& ans);

#endif