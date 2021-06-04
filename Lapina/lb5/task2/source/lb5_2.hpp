#include <iostream>
#include <string>
#include <vector>
#include <queue>
 
class State {
public:
    State (char name, State *parent) {
        this->name = name;
        this->parent = parent;
        this->suffixLink = nullptr;
        this->endLink = nullptr;
    }
 
    char getName (){
        return this->name;
    }
 
    std::vector<State *> getChildren (){
        return this->children;
    }
 
    State *getChild (char newName){
        for (auto &node : children) {
            if (node->getName() == newName) {
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
        this->terminals.push_back(numOfString);
    }
 
    std::vector<int> getTerminal () {
        return this->terminals;
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
            while (temp->getTerminal().empty()) {
                if (temp->getName() == ' ') {
                    break;
                }
                temp = temp->getSuffixLink();
            }
            if (!temp->getTerminal().empty()) {
                this->endLink = temp;
            }
        }
    }
 
    State *getSuffixLink () {
        return this->suffixLink;
    }
 
    State *getEndLink () {
        return this->endLink;
    }
 
private:
    char name;
    std::vector<State *> children;
    State *parent;
    State *suffixLink;
    State *endLink;
    std::vector<int> terminals;
 
};
 
class Machine {
public:
    Machine (std::vector<std::pair<std::string, int>> &patterns, int endJokers) {
        this->root = new State(' ', nullptr);
        this->patterns = patterns;
        this->endJokers = endJokers;
        this->addPatterns(patterns);
        this->addSuffixLinks();
    }
 
    ~Machine () {
        root->deleteChildren();
        delete root;
    }
 
    std::vector<int> AhoCorasick (std::string &text) {
        auto curState = root;
        std::vector<int> strNums(text.size(), 0);
        for (int index = 0; index < text.size() - endJokers; index++) {
            auto nextState = curState->getChild(text[index]);
            while (nextState == nullptr) {
                if (curState == this->root) {
                    nextState = curState;
                    break;
                }
                curState = curState->getSuffixLink();
                nextState = curState->getChild(text[index]);
            }
            for (auto &terminal : nextState->getTerminal()) {
                if (index - terminal + 1 >= 0) {
                    strNums[index - terminal + 1]++;
                }
            }
            auto tempState = nextState->getEndLink();
            while (tempState != nullptr) {
                for (auto &terminal : tempState->getTerminal()) {
                    if (index - terminal + 1 >= 0) {
                        strNums[index - terminal + 1]++;
                    }
                }
                tempState = tempState->getEndLink();
            }
            curState = nextState;
        }
        std::vector<int> result;
        for (int index = 0; index < strNums.size(); index++) {
            if (strNums[index] == patterns.size()) {
                result.push_back(index + 1);
            }
        }
        return result;
    }
 
protected:
    void addPatterns (std::vector<std::pair<std::string, int>> &newPatterns) {
        for (auto &str : newPatterns) {
            State *curState = root;
            for (int i = 0; i < str.first.size(); i++) {
                auto nextState = curState->getChild(str.first[i]);
                if (nextState == nullptr) {
                    nextState = new State(str.first[i], curState);
                    curState->addChild(nextState);
                }
                if (i == str.first.size() - 1) {
                    nextState->changeTerminal(str.second);
                } else {
                    curState = nextState;
                }
            }
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
    std::vector<std::pair<std::string, int>> patterns;
    int endJokers;
 
};
