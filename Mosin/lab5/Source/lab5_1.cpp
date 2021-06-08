#include "lab5_1.h"

void add(Trie* root, std::string& string, int order) {
    Trie* node = root;
    int depth = 1;
    for (auto symbol : string) {
        if (!node->children[symbol]) {
            node->children[symbol] = new Trie();
        }
        node = node->children[symbol];
        node->depth = depth++;
    }
    node->order = order;
}

void build(Trie* root) {
    root->suffix_link = root;

    std::queue<Trie*> queue;
    for (auto vertex : root->children) {
        vertex.second->suffix_link = root;
        queue.push(vertex.second);
    }

    while (!queue.empty()) {
        Trie* node = queue.front();
        queue.pop();

        for (auto vertex : node->children) {
            char name = vertex.first;
            Trie* child = vertex.second;
            Trie* suffix_link = node->suffix_link;
            while (suffix_link != root && !suffix_link->children[name]) {
                suffix_link = suffix_link->suffix_link;
            }

            if (suffix_link == root && !suffix_link->children[name]) {
                child->suffix_link = suffix_link;
            }
            else {
                suffix_link = suffix_link->children[name];
                child->suffix_link = suffix_link;
            }

            queue.push(vertex.second);
        }
    }
}

std::vector<std::pair<int, int>> Aho_Corasick(Trie* root, std::string& text) {
    std::vector<std::pair<int, int>> result;

    Trie* node = root;
    for (int i = 0; i < text.size(); ++i) {
        while (!node->children[text[i]] && node != root) {
            node = node->suffix_link;
        }

        if (node->children[text[i]]) {
            node = node->children[text[i]];
        }

        Trie* temp = node;
        while (temp != root) {
            if (temp->order != 0) {
                result.push_back(std::pair<int, int>(i + 2 - temp->depth, temp->order));
            }
            
            temp = temp->suffix_link;
        }
    }

    return result;
}