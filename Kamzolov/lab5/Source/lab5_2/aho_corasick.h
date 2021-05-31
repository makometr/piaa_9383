#ifndef AHO_KORASICK_H
#define AHO_KORASICK_H

#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <array>

struct Node {
    std::map<char, Node*> next;
    Node* suffixLink = nullptr;
    char symbol = '\0';
    std::vector<int> offsets;
};

void findSuffixLink(Node* node, Node* root, char symbol);
void suffixFunc(Node* root);
void wordToTrie(Node* root, std::string& word, int offset);
void input(std::string& text, std::string& pattern, char& joker, std::istream& in);
std::vector<int> ahoCorasik(std::string& text, Node* root, int count, int patternSize);
void printAnswer(std::vector<int>& ans);
void splitString(Node* root, std::string& pattern, char joker, int& count);

#endif
