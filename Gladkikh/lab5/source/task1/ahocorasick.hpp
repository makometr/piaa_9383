#pragma once

#include <iostream>

#include <vector>
#include <string>
#include <queue>
#include <algorithm>

struct Node{
    char symbol;
    int word_index = -1;

    Node* parent;
    Node* suffix_ref;
    Node* final_ref;

    std::vector<Node*> next_nodes;

    Node() {}
    Node(char newSymbol, Node* parent_node) : symbol(newSymbol), parent(parent_node) {}

    Node* find_next_node(char symbol);

    bool isFinal();
};

class AhoCorasick{

public:

    AhoCorasick();
    ~AhoCorasick();
    void add_string(const std::string& patt);

    std::vector<std::pair<int, int>> search(const std::string& temp);

    void init();

    void print();


private:

    Node* root_node_;
    std::vector<std::string> words_;
    
    void create_refs();
    void print_trie(Node* cur_node, int level);
    void clear_memory(Node* cur_node);

};