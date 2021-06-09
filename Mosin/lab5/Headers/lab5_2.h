#pragma once

#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <map>

struct Trie {
    ~Trie() {
        for (auto it : children) {
            delete it.second;
        }
    }
    std::map<char, Trie*> children;
    Trie* suffix_link = nullptr;
    std::vector<int> wild_card_position;
};

void add(Trie* root, std::string& string, int position);
int split(Trie* root, std::string& pattern, char wild_card);
void build(Trie* root);
std::vector<int> Aho_Corasick(Trie* root, std::string& text, int count, int size);