#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

struct Trie {
    std::map<char, Trie*> children;
    Trie* suffix_link = nullptr;
    int order = 0;
    int depth = 0;
};

void add(Trie* root, std::string& string, int order);
void build(Trie* root);
std::vector<std::pair<int, int>> Aho_Corasick(Trie* root, std::string& text);