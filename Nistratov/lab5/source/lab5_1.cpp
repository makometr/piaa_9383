#include "lab5_1.hpp"


void AhoCorasick::addPattern(std::string str, int pattern_state){
    BorTree* curr_node = root;
    int d = 1;
    for (size_t i = 0; i < str.size(); i++){
        if (!curr_node->links[str[i]]){
            curr_node->links[str[i]] = new BorTree;
        }
        curr_node = curr_node->links[str[i]];
        curr_node->depth = d++;
    }
    curr_node->term = pattern_state;
}

void AhoCorasick::createSuffixLinks(){
    std::queue<BorTree*> q;
    root->suffixLink = root;
    for (auto pair : root->links){
        pair.second->suffixLink = root;
        q.push(pair.second);
    }
    while (!q.empty()){
        auto node = q.front();
        q.pop();
        for (auto pair : node->links){
            while(node->suffixLink != root && !node->suffixLink->links[pair.first]){
                node->suffixLink = node->suffixLink->suffixLink;
            }
            if (node->suffixLink == root && !node->suffixLink->links[pair.first]){
                pair.second->suffixLink = node->suffixLink;
            }
            else{
                node->suffixLink = node->suffixLink->links[pair.first];
                pair.second->suffixLink = node->suffixLink;
            }
            if (pair.second->term > 0){
                pair.second->suffixLink = root;
                pair.second->links.clear();
            }
            q.push(pair.second);
        }
    }
}

Result AhoCorasick::find_ak(){
    BorTree* curr_node = root;
    for (size_t i = 0; i < text.size(); i++){
        while (!curr_node->links[text[i]] && curr_node != root){
            curr_node = curr_node->suffixLink;
        }
        if (curr_node->links[text[i]]){
            curr_node = curr_node->links[text[i]];
        }
        
        BorTree* answer_node = curr_node;
        while (answer_node != root){
            if (answer_node->term > 0){
                result.push_back(std::pair<int, int>(i + 2 - answer_node->depth, answer_node->term));
            }
            answer_node = answer_node->suffixLink;
        }
        
    }
    return result;
}