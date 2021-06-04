#include "lab5_2.hpp"

void AhoCorasick::addPattern(std::string str, int pattern_state){
    BorTree* curr_node = root;
    for (size_t i = 0; i < str.size(); i++){
        if (!curr_node->links[str[i]]){
            curr_node->links[str[i]] = new BorTree;
            alloc.push(curr_node->links[str[i]]);
        }
        curr_node = curr_node->links[str[i]];
    }
    curr_node->pos_of_split_pattern.push_back(pattern_state);
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
            q.push(pair.second);
        }
    }
}

void AhoCorasick::split_by_joker(char joker){
    std::string split_str;
    for (int i = 0; i < pattern.size(); i++){
        if (pattern[i] == joker){
            if (!split_str.empty()){
                addPattern(split_str, i - 1);
                split_pattern_ammount++;
            }
            split_str.clear();
        }
        else{
            split_str.push_back(pattern[i]);
        }
    }
    if (!split_str.empty()){
        addPattern(split_str, pattern.size() - 2);
        split_pattern_ammount++;
    }
}

Result AhoCorasick::find_ak(){
    BorTree* curr_node = root;
    int numberMatches[text.size()];
    for (int i = 0; i < text.size(); i++){
        numberMatches[i] = 0;
    }    
    for (size_t i = 0; i < text.size(); i++){
        while (!curr_node->links[text[i]] && curr_node != root){
            curr_node = curr_node->suffixLink;
        }
        if (curr_node->links[text[i]]){
            curr_node = curr_node->links[text[i]];
        }
        
        BorTree* answer_node = curr_node;
        while (answer_node != root){
            if (!answer_node->pos_of_split_pattern.empty()){
                for (auto pos : answer_node->pos_of_split_pattern){
                    if(i - pos >= 0){
                        numberMatches[i - pos]++;
                    }
                }
            }
            answer_node = answer_node->suffixLink;
        }
    }
    for (int i = 0; i < text.size(); i++){
        if (numberMatches[i] == split_pattern_ammount && i + pattern.size() <= text.size() ){
            result.push_back(i + 1);
        }
    }   
    return result;
}