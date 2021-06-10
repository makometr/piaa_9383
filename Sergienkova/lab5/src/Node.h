#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

#define TASK 2


struct Node {
    std::unordered_map<char, Node*> m_nextEdges;        // рёбра, по которым можно перейти
#if TASK == 2
    std::vector<int> m_shiftSubstr;                     // сдвиги подстрок в шаблоне
#endif
    Node* m_Parent;                                     // родительская вершина
    Node* suffixLink;
    Node* termSuffixLink;                               // конечная ссылка
    char toParent;                                      // ребро, по которому пришли из родительской вершины
    bool isTerminal;
    std::vector<int> m_patternNumber;                   // номера шаблонов, в которые входит символ, по которому пришли
    int termPatternNumber;

    Node(Node* parent = nullptr, const char toParent = 0) : m_Parent(parent), toParent(toParent), suffixLink(nullptr), termSuffixLink(nullptr), isTerminal(false) {
        if (parent == nullptr || toParent == 0) {
            this->m_Parent = this;
            this->suffixLink = this;
        }
    }

    // поиск следующей (для перехода) вершины при поиске в строке
    Node* GetLink(const char& c) {
        if (this->m_nextEdges.find(c) != this->m_nextEdges.end()) {
            return this->m_nextEdges.at(c);
        }
        if (this->suffixLink == this) { 
            return this;
        }
        return this->suffixLink->GetLink(c);
    }

    ~Node() {
        for (auto l : this->m_nextEdges) {
            delete l.second;
        }
    }
};
