#include "lab5_2.h"

void add(Trie* root, std::string& string, int position) {
    Trie* node = root;
    for (auto symbol : string) {
        if (!node->children[symbol]) {
            node->children[symbol] = new Trie();
        }
        node = node->children[symbol];
    }
    node->wild_card_position.push_back(position);
}

int split(Trie* root, std::string& pattern, char wild_card) {
    int count = 0;
    int index = 0;
    std::string temp;
    for (auto symbol : pattern) {
        if (symbol == wild_card) {
            if (!temp.empty()) {
                add(root, temp, index - 1);
                count++;
            }
            temp.clear();
        }
        else {
            temp.push_back(symbol);
        }
        index++;
    }

    if (!temp.empty()) {
        add(root, temp, index - 1);
        count++;
    }

    return count;
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

std::vector<int> Aho_Corasick(Trie* root, std::string& text, int count, int size) {
    std::vector<int> result;

    Trie* node = root;
    int number_of_matches[text.size()];
    std::memset(number_of_matches, 0, sizeof(number_of_matches));

    for (int i = 0; i < text.size(); ++i) {
        while (!node->children[text[i]] && node != root) {
            node = node->suffix_link;
        }

        if (node->children[text[i]]) {
            node = node->children[text[i]];
        }

        Trie* temp = node;
        while (temp != root) {
            for (auto position : temp->wild_card_position) {
                if (i - position >= 0) {
                    number_of_matches[i - position]++;
                }
            }
            temp = temp->suffix_link;
        }
    }

    for (int i = 0; i < text.size(); ++i) {
        if (number_of_matches[i] == count && i + size <= text.size()) {
            result.push_back(i + 1);
        }
    }

    return result;
}