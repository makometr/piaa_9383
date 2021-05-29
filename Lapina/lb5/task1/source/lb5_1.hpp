#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
 
class State {
public:
    State (char name, State *parent) : name(name), parent(parent) {
        this->suffixLink = nullptr;
        this->endLink = nullptr;
        this->terminal = 0;
    }
 
    char getName (){
        return this->name;
    }
 
    std::vector<State *> getChildren (){
        return this->children;
    }
 
    State *getChild (char newChild){
        for (auto &node : children) {
            if (node->getName() == newChild) {
                return node;
            }
        }
        return nullptr;
    }
 
    void addChild (State *descendent) {
        this->children.push_back(descendent);
    }
 
    void deleteChildren () {
        for (auto &node : this->children) {
            node->deleteChildren();
            delete node;
        }
    }
 
    void changeTerminal (int numOfString) {
        this->terminal = numOfString;
    }
 
    int getTerminal (){
        return this->terminal;
    }
 
    void addSuffixLink () {
        if (this->getName() == ' ') {
            this->suffixLink = this;
        } else if (this->parent->getName() == ' ') {
            this->suffixLink = this->parent;
        } else {
            auto curState = this->parent->suffixLink;
            auto nextState = curState->getChild(this->getName());
            while (nextState == nullptr) {
                if (curState->getName() == ' ') {
                    nextState = curState;
                    break;
                }
                curState = curState->suffixLink;
                nextState = curState->getChild(this->getName());
            }
            this->suffixLink = nextState;
            auto temp = nextState;
            while (temp->getTerminal() == 0) {
                if (temp->getName() == ' ') {
                    break;
                }
                temp = temp->getSuffixLink();
            }
            if (temp->getTerminal() > 0) {
                this->endLink = temp;
            }
        }
    }
 
    State *getSuffixLink (){
        return this->suffixLink;
    }
 
    State *getEndLink (){
        return this->endLink;
    }
 
private:
    char name;
    std::vector<State *> children;
    State *parent;
    State *suffixLink;
    State *endLink;
    int terminal;
 
};
 
class Machine {
public:
    explicit Machine (std::vector<std::string> &patterns) {
        this->root = new State(' ', nullptr);
        this->patterns = patterns;
        this->addPatterns(patterns);
        this->addSuffixLinks();
    }
 
    ~Machine () {
        root->deleteChildren();
        delete root;
    }
 
    std::vector<std::pair<int, int>> AhoCorasick (std::string &text) {
        auto curState = root;
        std::vector<std::pair<int, int>> result;
        for (int index = 0; index < text.size(); index++) {
            auto nextState = curState->getChild(text[index]);
            while (nextState == nullptr) {
                if (curState == this->root) {
                    nextState = curState;
                    break;
                }
                curState = curState->getSuffixLink();
                nextState = curState->getChild(text[index]);
            }
            if (nextState->getTerminal() > 0) {
                int strIndex = index - this->patterns[nextState->getTerminal() - 1].size() + 2;
                result.emplace_back(strIndex, nextState->getTerminal());
            }
            if (nextState->getEndLink() != nullptr) {
                auto temp = nextState->getEndLink();
                while (temp != nullptr) {
                    result.emplace_back(index - this->patterns[temp->getTerminal() - 1].size() + 2, temp->getTerminal());
                    temp = temp->getEndLink();
                }
            }
            curState = nextState;
        }
        std::sort(result.begin(), result.end(), [](std::pair<int, int> entry1, std::pair<int, int> entry2){
            if (entry1.first != entry2.first) {
                return entry1.first < entry2.first;
            } else {
                return entry1.second < entry2.second;
            }
        });
        return result;
    }
 
protected:
    void addPatterns (std::vector<std::string> &newPatterns) {
        int numOfString = 1;
        for (auto &str : newPatterns) {
            State *curState = root;
            for (int i = 0; i < str.size(); i++) {
                auto nextState = curState->getChild(str[i]);
                if (nextState == nullptr) {
                    nextState = new State(str[i], curState);
                    curState->addChild(nextState);
                }
                if (i == str.size() - 1) {
                    nextState->changeTerminal(numOfString);
                } else {
                    curState = nextState;
                }
            }
            numOfString++;
        }
    }
 
    void addSuffixLinks () {
        std::queue<State *> queue;
        State *curState = root;
        queue.push(root);
        while (!queue.empty()) {
            curState->addSuffixLink();
            queue.pop();
            for (auto &node : curState->getChildren()) {
                queue.push(node);
            }
            curState = queue.front();
        }
    }
 
private:
    State *root;
    std::vector<std::string> patterns;
 
};
 
