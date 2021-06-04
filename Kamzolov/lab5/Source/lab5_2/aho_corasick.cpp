#include "aho_corasick.h"


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

void wordToTrie(Node* root, std::string& word, int offset) {
    Node* tempNode = root;
    for(size_t i = 0; i < word.size(); i++) {
        if(tempNode->next.count(word[i]) == 0) 
            tempNode->next[word[i]] = new Node;
        tempNode->next[word[i]]->suffixLink = tempNode;
        tempNode = tempNode->next[word[i]];
        tempNode->symbol = word[i];
    }
    tempNode->offsets.push_back(offset);
}



void input(std::string& text, std::string& pattern, char& joker, std::istream& in) {
    
    in >> text;
    in >> pattern;
    in >> joker;

}



std::vector<int> ahoCorasik(std::string& text, Node* root, int count, int patternSize) {
    std::vector<int> answer;
    std::vector<int> matchCounter(text.size());
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
        
        Node* tempSufNode = tempNode;
        while(tempSufNode != root) {
            for (auto offset : tempSufNode->offsets) {
                if(i - offset >= 0 && i - offset < matchCounter.size()) {
                    matchCounter[i - offset]++;
                }
            }
            tempSufNode = tempSufNode->suffixLink;
        }
    }

    for(size_t i = 0; i < matchCounter.size(); i++) {
        if(matchCounter[i] == count && i + patternSize <= matchCounter.size()) {
            answer.push_back(i + 1);
        }
    }

    return answer;
}


void printAnswer(std::vector<int>& ans) {
    std::sort(ans.begin(), ans.end());
    for(auto& elem : ans) {
        std::cout << elem << '\n';
    }
}


void splitString(Node* root, std::string& pattern, char joker, int& count) {
    std::string tempString;
    int offset = 0;
    for(size_t i = 0; i < pattern.size(); i++) {
        if(pattern[i] == joker) {
            if(!tempString.empty()){
                wordToTrie(root, tempString, offset - 1);
                count++;
            }
            tempString.clear();
        }
        else {
            tempString.push_back(pattern[i]);
        }
        offset++;
    }

    if(!tempString.empty()){
        wordToTrie(root, tempString, offset - 1);
        count++;
    }
}

void freeMemory(Node* root) {
    Node* tempNode = root; 
    for(auto& neighbour : tempNode->next) {
        freeMemory(neighbour.second);
    }
    delete tempNode;
}