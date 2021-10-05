#pragma once

#include "node.h"

Node* CreateBor(const std::vector<std::pair<std::string, int>>& patterns) {
    Node* bor = new Node;
    for (auto& i : patterns) {
        int patternNum = find(patterns.begin(), patterns.end(), i) - patterns.begin();
        Node* current = bor;
        for (auto& c : i.first) {
            if (current->nextEdges.find(c) == current->nextEdges.end()) {
                current->nextEdges.insert({ c, new Node(current, c) });
            }
            current = current->nextEdges[c];
            current->patternNumber.push_back(patternNum);
        }
        current->termPatternNumber = patternNum;
        current->isTerminal = true;
#if TASK == 2
        current->substrShift.push_back(i.second);
#endif
    }
    return bor;
}

void FindSuffixLinks(Node* bor) {
    std::queue<Node*> front({ bor });
    while (!front.empty()) {
        Node* current = front.front();
        front.pop();
        Node* currentLink = current->Parent->suffixLink;
        const char& key = current->toParent;
        bool foundLink = true;

        while (currentLink->nextEdges.find(key) == currentLink->nextEdges.end()) {
            if (currentLink == bor) {
                current->suffixLink = bor;
                foundLink = false;
                break;
            }
            currentLink = currentLink->suffixLink;
        }
        if (foundLink) {
            currentLink = currentLink->nextEdges.at(key);
            if (current->Parent == bor) {
                current->suffixLink = bor;
            }
            else {
                current->suffixLink = currentLink;
                Node* curTlink = current->suffixLink;
                while (curTlink != bor) {
                    if (curTlink->isTerminal) {
                        current->termSuffixLink = curTlink;
                        break;
                    }
                    curTlink = curTlink->suffixLink;
                }
            }
        }

        if (!current->nextEdges.empty()) {
            for (auto& nxt : current->nextEdges) {
                front.push(nxt.second);
            }
        }
    }
}

std::pair<int, int> LenAllLinks(Node* bor, Node* root, int& depth) {
    std::pair<int, int> longest = { 0, 0 };
    Node* current = bor;
    while (current->suffixLink != root) {
        longest.first++;
        current = current->suffixLink;
    }
    longest.first++;
    current = bor;
    while (current->termSuffixLink != nullptr) {
        longest.second++;
        current = current->termSuffixLink;
    }
    for (auto& n : bor->nextEdges) {
        std::pair<int, int> nextLong = LenAllLinks(n.second, root, ++depth);
        if (nextLong.first > longest.first) {
            longest.first = nextLong.first;
        }
        if (nextLong.second > longest.second) {
            longest.second = nextLong.second;
        }
    }
    depth--;
    return longest;
}


void solution(const std::string& t, const std::vector<std::pair<std::string, int>>& patterns, std::vector<std::pair<int, int>>& res, int ptnLength = 0) {
    Node* bor = CreateBor(patterns);
    FindSuffixLinks(bor);
    int depth = 0;
    std::pair<int, int> longest = LenAllLinks(bor, bor, depth);
    Node* current = bor;
    res.clear();
#if TASK == 2
    std::vector<int> tInd(t.length(), 0);
#endif

    for (int i = 0; i < t.length(); i++) {
        current = current->GetLink(t.at(i));
        Node* terminalLink = current->termSuffixLink;
        while (terminalLink != nullptr) {
#if TASK == 1
            res.push_back({ i - patterns.at(terminalLink->termPatternNumber).first.length() + 2, terminalLink->termPatternNumber + 1 });
#elif TASK == 2
            for (auto& sh : terminalLink->substrShift) {
                int idx = i - patterns.at(terminalLink->termPatternNumber).first.length() - sh + 1;
                if (!(idx < 0)) {
                    tInd.at(idx)++;
                }
            }
#endif
            terminalLink = terminalLink->termSuffixLink;
        }
        if (current->isTerminal) {
#if TASK == 1
            res.push_back({ i - patterns.at(current->termPatternNumber).first.length() + 2, current->termPatternNumber + 1 });
#elif TASK == 2
            for (auto& sh : current->substrShift) {
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

    delete bor;
}


#if TASK == 2

// p -- шаблон с маской, j -- символ разделитель, patterns -- список шаблонов
void preparePatterns(const std::string& p, const char& j, std::vector<std::pair<std::string, int>>& patterns) {
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