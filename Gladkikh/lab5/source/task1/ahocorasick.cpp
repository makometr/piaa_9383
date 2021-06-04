#include "ahocorasick.hpp"

AhoCorasick::AhoCorasick() {
    root_node_ = new Node();
    root_node_->parent = root_node_;
    root_node_->suffix_ref = root_node_;
}

void AhoCorasick::add_string(const std::string& patt) {
    
    Node* cur_node = root_node_;

    Node* child_node;

    for(const auto& symbol: patt) {
        
        child_node = cur_node->find_next_node(symbol);

        if(!child_node) {
            child_node = new Node({symbol, cur_node});
            cur_node->next_nodes.push_back(child_node);
        }

        cur_node = child_node;
    }

    cur_node->word_index = words_.size();
    words_.push_back(patt);
}


void AhoCorasick::init() {
    create_refs();
}

void AhoCorasick::create_refs() {
    std::queue<Node*> nodes_queue;
    Node* temp_node;
    Node* found_node;
    Node* node_for_suffix_ref;
    bool suffix_ref_set;

    for(const auto& next_node: root_node_->next_nodes) {
        next_node->suffix_ref = root_node_;
        nodes_queue.push(next_node);
    }

    while (!nodes_queue.empty()) {
        temp_node = nodes_queue.front();
        nodes_queue.pop();

        for (const auto& next_node: temp_node->next_nodes) {
            suffix_ref_set = false;
            node_for_suffix_ref = temp_node;
            while (node_for_suffix_ref != root_node_) {
                node_for_suffix_ref = node_for_suffix_ref->suffix_ref;
                found_node = node_for_suffix_ref->find_next_node(next_node->symbol);
                if(found_node) {
                    if(!suffix_ref_set) {
                        suffix_ref_set = true;
                        next_node->suffix_ref = found_node;
                    }

                    if(found_node->isFinal()) {
                        next_node->final_ref = found_node;
                        break;
                    }
                }
            }

            if(!suffix_ref_set) {
                next_node->suffix_ref = root_node_;
            }

            nodes_queue.push(next_node);
        }
    }
}

std::vector<std::pair<int, int>> AhoCorasick::search(const std::string& temp) {

    std::vector<std::pair<int, int>> ans;

    Node* cur_node = root_node_;
    Node* next_node;

    std::string debug;

    for(int i = 0; (size_t)i < temp.size(); ++i) {
        char text_symbol = temp[i];

        next_node = cur_node->find_next_node(text_symbol);

        while(!next_node) {
            if(cur_node == root_node_) {
                next_node = root_node_;
                break;
            }
            cur_node = cur_node->suffix_ref;
            next_node = cur_node->find_next_node(text_symbol);
        }

        cur_node = next_node;

        while(next_node != root_node_) {
            if(next_node->isFinal()) ans.push_back(std::make_pair(i - words_[next_node->word_index].size() + 2, next_node->word_index + 1));
            next_node = next_node->suffix_ref;
        }
    }

    auto cmp_for_ans = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        if(a.first == b.first) return a.second < b.second;
        return a.first < b.first;
    };

    std::sort(ans.begin(), ans.end(), cmp_for_ans);

    return ans;
}

void AhoCorasick::print() {
    std::cout << "root";
    print_trie(root_node_, 0);
}

void AhoCorasick::print_trie(Node* cur_node, int level) {
    if(!cur_node) return;

    for(int i = 0; i < level; ++i){
        std::cout << '\t';
    }
    std::cout << cur_node->symbol << " " << cur_node << " suff: " << cur_node->suffix_ref << " final: " << cur_node->final_ref << "\n";


    for(const auto& next_node: cur_node->next_nodes) {
        print_trie(next_node, level + 1);
    }
}

void AhoCorasick::clear_memory(Node* cur_node) {
    if(!cur_node) return;

    for(const auto& next_node: cur_node->next_nodes) {
        clear_memory(next_node);
    }

    delete cur_node;
}

AhoCorasick::~AhoCorasick() {
    clear_memory(root_node_);
}

Node* Node::find_next_node(char symbol_to_find) {
    for(const auto& next_node: next_nodes) {
        if (next_node->symbol == symbol_to_find) {
            return next_node;
        }
    }

    return nullptr;
}

bool Node::isFinal() {
    return word_index >= 0;
}