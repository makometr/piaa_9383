#pragma once

#include "Node.h"

// создание бора
Node* CreateBohr(const std::vector<std::pair<std::string, int>> &patterns) {
    Node* bohr = new Node;
    for (auto& pt : patterns) {
        int ptnNum = find(patterns.begin(), patterns.end(), pt) - patterns.begin();
        Node* cur = bohr;
        for (auto& c : pt.first) {
            if (cur->m_nextEdges.find(c) == cur->m_nextEdges.end()) {
                cur->m_nextEdges.insert({ c, new Node(cur, c) });
            }
            cur = cur->m_nextEdges[c]; // переходим по данному ребру
            cur->m_patternNumber.push_back(ptnNum);
        }
        // для конечной вершины
        cur->termPatternNumber = ptnNum;
        cur->isTerminal = true;
#if TASK == 2
        cur->m_shiftSubstr.push_back(pt.second);
#endif
    }
    return bohr;
}

// нахождение суффиксных и конечных ссылок
void FindSuffixLinks(Node* bohr) {
    std::queue<Node*> front({ bohr });    // вершины одного уровня в боре
    while (!front.empty()) {
        Node* current = front.front();
        front.pop();
        Node* currentLink = current->m_Parent->suffixLink;
        const char& key = current->toParent;
        bool foundLink = true;
        
        while (currentLink->m_nextEdges.find(key) == currentLink->m_nextEdges.end()) {
            if (currentLink == bohr) {
                current->suffixLink = bohr;
                foundLink = false;
                break;
            }
            currentLink = currentLink->suffixLink;
        }
        if (foundLink) {
            currentLink = currentLink->m_nextEdges.at(key);
            if (current->m_Parent == bohr) {
                current->suffixLink = bohr;
            }
            else {
                current->suffixLink = currentLink;
                Node* curTlink = current->suffixLink;
                while (curTlink != bohr) {
                    if (curTlink->isTerminal) {
                        current->termSuffixLink = curTlink;
                        break;
                    }
                    curTlink = curTlink->suffixLink;
                }
            }
        }
        
        if (!current->m_nextEdges.empty()) {
            for (auto& nxt : current->m_nextEdges) {
                front.push(nxt.second);
            }
        }
    }
}

// вычисление длин наибольших цепочек из суффиксных и конечных ссылок
std::pair<int, int> LenAllLinks(Node* bohr, Node* root, int& depth) {
    std::pair<int, int> longest = { 0, 0 };
    Node* current = bohr;
    while (current->suffixLink != root) {
        longest.first++;
        current = current->suffixLink;
    }
    longest.first++;
    current = bohr;
    while (current->termSuffixLink != nullptr) {
        longest.second++;
        current = current->termSuffixLink;
    }
    for (auto& n : bohr->m_nextEdges) {
        std::pair<int, int> nextLon = LenAllLinks(n.second, root, ++depth);
        if (nextLon.first > longest.first) {
            longest.first = nextLon.first;
        }
        if (nextLon.second > longest.second) {
            longest.second = nextLon.second;
        }
    }
    depth--;
    return longest;
}


void MyAlgorithm(const std::string &t, const std::vector<std::pair<std::string, int>> &patterns, std::vector<std::pair<int, int>> &res, int ptnLength = 0) {
    Node* bohr = CreateBohr(patterns);
    FindSuffixLinks(bohr);
    int depth = 0;
    std::pair<int, int> longest = LenAllLinks(bohr, bohr, depth);
    Node* current = bohr;
    res.clear();
#if TASK == 2
    std::vector<int> tInd(t.length(), 0);
#endif

    for (int i = 0; i < t.length(); i++) {
        current = current->GetLink(t.at(i));    // получили ссылку для перехода
        Node* terminalLink = current->termSuffixLink;
        while (terminalLink != nullptr) {    // если у этой вершины есть конечная ссылка, записываем, что нашли соответствующий ей шаблон
#if TASK == 1
            res.push_back({ i - patterns.at(terminalLink->termPatternNumber).first.length() + 2, terminalLink->termPatternNumber + 1 });
#elif TASK == 2
            for (auto& sh : terminalLink->m_shiftSubstr) {
                int idx = i - patterns.at(terminalLink->termPatternNumber).first.length() - sh + 1;
                if (!(idx < 0)) {
                    tInd.at(idx)++;
                }
            }
#endif
            terminalLink = terminalLink->termSuffixLink;
        }
        if (current->isTerminal) {    // если терминальная - шаблон найден
#if TASK == 1
            res.push_back({ i - patterns.at(current->termPatternNumber).first.length() + 2, current->termPatternNumber + 1 });
#elif TASK == 2
            for (auto& sh : current->m_shiftSubstr) {
                int idx = i - patterns.at(current->termPatternNumber).first.length() - sh + 1;
                if (!(idx < 0)) {
                    tInd.at(idx)++;
                }
            }
#endif
        }
    }

#if TASK == 2
    for (int i = 0; i < tInd.size(); i++) {
        if (tInd[i] == patterns.size() && i + ptnLength <= t.length()) {
            res.push_back({ i + 1, 0 });
        }
    }
#endif

    delete bohr;
}


#if TASK == 2

// разбиение шаблона с джокером на безджокерные подшаблоны
// p -- шаблон с маской, j -- символ разделитель, patterns -- список шаблонов
void preparePatterns(const std::string &p, const char &j, std::vector<std::pair<std::string, int>> &patterns) {
    int prev = 0;
    size_t temp;
    do {
        temp = p.find(j, prev);
        if (temp != prev && prev != p.length()) {
            patterns.push_back({ p.substr(prev, temp - prev), prev });
        }
        prev = temp + 1;
    } while (temp != std::string::npos);
}
#endif
