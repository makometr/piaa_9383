#include "aho_corasick.h"

bool comparator(std::pair<int, int> first, std::pair<int, int> second) {
    if (first.first != second.first) {
        return first.first < second.first;
    } else {
        return first.second < second.second;
    }
}



void findSuffixLink(Node* node, Node* root, char symbol) {
    if(node->suffixLink == root) {
        return;
    }
    Node* tempSuffix = node->suffixLink->suffixLink;
    bool isChanged = false;
    while(true) {
        for(auto& vertex: tempSuffix->next) {
            if(vertex.second->symbol == symbol) {
                if(!isChanged) {
                    node->suffixLink = vertex.second;
                    isChanged = true;
                }
                if(vertex.second->isTerminal) {
                    node->endLink = vertex.second;
                    return;
                }
                                
            }
        }
        if(tempSuffix == root) 
            break;
        tempSuffix = tempSuffix->suffixLink;
    }
    if(!isChanged) {
        node->suffixLink = root;
    }
}


void suffixFunc(Node* root) {
    std::queue<Node*> tempQueue;
    Node* curNode = root;

    for(auto& node : curNode->next) {
        tempQueue.push(node.second);
    }
 
    while(!tempQueue.empty()) {
        curNode = tempQueue.front();
        tempQueue.pop();
        findSuffixLink(curNode, root, curNode->symbol);
        for (auto &node : curNode->next) {
            tempQueue.push(node.second);
        }
    }
}

void wordToTrie(Node* root, std::string& word, int number) {
    
    Node* tempNode = root;
    for(int i = 0; i < word.size(); i++) {
        if(tempNode->next.count(word[i]) == 0) 
            tempNode->next[word[i]] = new Node;
        tempNode->next[word[i]]->suffixLink = tempNode;
        tempNode = tempNode->next[word[i]];
        tempNode->symbol = word[i];
        if(i == word.size() - 1) {
            tempNode->isTerminal = true;
            tempNode->wordSize = word.size();
            tempNode->stringNumbers.push_back(number);
        }
    }
}



void input(std::string& text, Node* root, std::istream& in) {
    
    in >> text;

    int n;
    in >> n;

    std::string tempString;
    for(int i = 0; i < n; i++) {
        in >> tempString;
        wordToTrie(root, tempString, i + 1);
    }

}



std::vector<std::pair<int, int>> ahoCorasik(std::string& text, Node* root) {
    std::vector<std::pair<int, int>> answer;
    Node* tempNode = root;
    for(size_t i = 0; i < text.size(); i++) {
        if(tempNode->next.count(text[i]) == 0) {
            while(tempNode != root && tempNode->next.count(text[i]) == 0) {
                tempNode = tempNode->suffixLink;
                if(tempNode->next.count(text[i]) != 0) {
                    tempNode = tempNode->next[text[i]];
                    break;        
                }
            }   
            if (tempNode == root) continue;
        }
        else {
            tempNode = tempNode->next[text[i]];
        }
            
        
        if(tempNode->isTerminal == true) {
           for(int j = 0; j < tempNode->stringNumbers.size(); j++)
                answer.push_back(std::make_pair(i - tempNode->wordSize + 2, tempNode->stringNumbers[j]));
        }  

        Node* tempEndNode = tempNode->endLink;
        while(tempEndNode) {
            for(int j = 0; j < tempEndNode->stringNumbers.size(); j++)
                answer.push_back(std::make_pair(i - tempEndNode->wordSize + 2, tempEndNode->stringNumbers[j]));
            tempEndNode = tempEndNode->endLink;
        }
    }
    return answer;
}


void printAnswer(std::vector<std::pair<int, int>>& ans) {
    
    std::sort(ans.begin(), ans.end(), comparator);

    for(auto& pair : ans) {
        std::cout << pair.first << ' ' << pair.second << '\n';
    }
}