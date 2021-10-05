#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

#define TASK 1


struct Node {
    std::unordered_map<char, Node*> nextEdges;        // рёбра, по которым можно перейти
#if TASK == 2
    std::vector<int> substrShift;                     // сдвиги подстрок в шаблоне
#endif
    Node* Parent;                                     // родительская вершина
    Node* suffixLink;
    Node* termSuffixLink;                               // конечная ссылка
    char toParent;                                      // ребро, по которому пришли из родительской вершины
    bool isTerminal;
    std::vector<int> patternNumber;                   // номера шаблонов, в которые входит символ, по которому пришли
    int termPatternNumber;

    Node(Node* parent = nullptr, const char toParent = 0) : Parent(parent), toParent(toParent), suffixLink(nullptr), termSuffixLink(nullptr), isTerminal(false) {
        if (parent == nullptr || toParent == 0) {
            this->Parent = this;
            this->suffixLink = this;
        }
    }

    // поиск следующей вершины при поиске в строке
    Node* GetLink(const char& c) {
        if (this->nextEdges.find(c) != this->nextEdges.end()) {
            return this->nextEdges.at(c);
        }
        if (this->suffixLink == this) {
            return this;
        }
        return this->suffixLink->GetLink(c);
    }

    ~Node() {
        for (auto i : this->nextEdges) {
            delete i.second;
        }
    }
};