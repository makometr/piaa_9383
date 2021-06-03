#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

bool cmp_for_vec_pair(std::pair<int, int> elem1, std::pair<int, int> elem2) 
{
    if (elem1.first < elem2.first) 
    {
        return true;
    }
    else if (elem1.first == elem2.first && elem1.second < elem2.second) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

struct Bor 
{
    char edge;
    std::vector<int> final_vertex_number;
    std::vector<Bor*> children;
    Bor* parent;
    Bor* suffix_link;
    Bor* end_suffix_link;

    Bor (char new_edge, Bor* new_parent)
    {
        edge = new_edge;
        parent = new_parent;
        suffix_link = nullptr;
        end_suffix_link = nullptr;
    }
    
    Bor* go_to_child_by_edge (char child_edge)
    {
        for (auto &child : children) 
        {
            if (child->edge == child_edge) 
            {
                return child;
            }
        }
        return nullptr;
    }
    
    void add_suffix_link ()
    {
        if (edge == '@') 
        {
            suffix_link = this;
        } 
        else if (parent->edge == '@') 
        {
            suffix_link = parent;
        } 
        else 
        {
            Bor* current_state = parent->suffix_link;
            Bor* next_state = current_state->go_to_child_by_edge(edge);
            while (next_state == nullptr) 
            {
                if (current_state->edge == '@') 
                {
                    next_state = current_state;
                    break;
                }
                current_state = current_state->suffix_link;
                next_state = current_state->go_to_child_by_edge(edge);
            }
            suffix_link = next_state;
            Bor* tmp_state = next_state;
            while (tmp_state->final_vertex_number.empty()) 
            {
                if (tmp_state->edge == '@') 
                {
                    break;
                }
                tmp_state = tmp_state->suffix_link;
            }
            if (!tmp_state->final_vertex_number.empty()) 
            {
                end_suffix_link = tmp_state;
            }
        }
    }
};
    
struct DFA 
{
    Bor* root;
    std::vector<std::pair<std::string, int>> patterns;
    int last_jokers;
    
    DFA (std::vector<std::pair<std::string, int>>& new_patterns, int new_last_jokers) 
    {
        root = new Bor('@', nullptr);
        last_jokers = new_last_jokers;
        patterns = new_patterns;
        add_patterns(new_patterns);
        add_all_suffix_links();
    }
    
    void add_patterns (std::vector<std::pair<std::string, int>>& new_patterns) 
    {
        for (auto &current_pattern : new_patterns) 
        {
            Bor* current_state = root;
            for (int i = 0; i < current_pattern.first.size(); i++) 
            {
                Bor* next_state = current_state->go_to_child_by_edge(current_pattern.first[i]);
                if (next_state == nullptr) 
                {
                    next_state = new Bor(current_pattern.first[i], current_state);
                    current_state->children.push_back(next_state);
                }
                if (i == current_pattern.first.size()-1) 
                {
                    next_state->final_vertex_number.push_back(current_pattern.second);
                } 
                else 
                {
                    current_state = next_state;
                }
            }
        }
    }

    void add_all_suffix_links () 
    {
        std::queue<Bor*> queue;
        Bor* current_state = root;
        queue.push(root);
        while (!queue.empty()) 
        {
            current_state->add_suffix_link();
            queue.pop();
            for (auto &current_child : current_state->children) 
            {
                queue.push(current_child);
            }
            current_state = queue.front();
        }
    }

    void aho_corasick (std::string& text) 
    {
        Bor* current_state = root;
        std::vector<int> length_patterns_current(text.size(), 0);
        for (int i = 0; i < text.size()-last_jokers; i++) 
        {
            Bor* next_state = current_state->go_to_child_by_edge(text[i]);
            while (next_state == nullptr) 
            {
                if (current_state == root) 
                {
                    next_state = current_state;
                    break;
                }
                current_state = current_state->suffix_link;
                next_state = current_state->go_to_child_by_edge(text[i]);
            }
            for (auto &current_terminal : next_state->final_vertex_number) 
            {
                if (i-current_terminal+1 >= 0) 
                {
                    length_patterns_current[i-current_terminal+1]++;
                }
            }
            Bor* tmp_state = next_state->end_suffix_link;
            while (tmp_state != nullptr) 
            {
                for (auto &current_terminal : tmp_state->final_vertex_number) 
                {
                    if (i-current_terminal+1 >= 0) 
                    {
                        length_patterns_current[i-current_terminal+1]++;
                    }
                }
                tmp_state = tmp_state->end_suffix_link;
            }
            current_state = next_state;
        }
        std::vector<int> result;
        for (int i = 0; i < length_patterns_current.size(); i++) 
        {
            if (length_patterns_current[i] == patterns.size()) 
            {
                result.push_back(i+1);
            }
        }
        print_result(result);
    }
    
    void print_result(std::vector<int>& result)
    {
        std::cout << "Результат работы алгоритма: \n";
        sort(result.begin(), result.end());
        for (auto &answer : result) 
        {
            std::cout << answer << '\n';
        }
    }
};

int main () 
{
    std::cout << "Введите текст T:\n";
    std::string text;
    std::cin >> text;
    std::cout << "Введите шаблон:\n";
    std::string pattern;
    std::cin >> pattern;
    char joker;
    std::cout << "Введите символ джокера:\n";
    std::cin >> joker;
    std::vector<std::pair<std::string, int>> all_patterns;
    std::string pattern_separation;
    int last_jokers;
    for (int i = 0; i < pattern.size(); i++) 
    {
        if (pattern[i] != joker) 
        {
            pattern_separation += pattern[i];
            last_jokers = 0;
        } 
        else 
        {
            if (!pattern_separation.empty())
            {
                all_patterns.emplace_back(pattern_separation, i);
            }
            pattern_separation = "";
            last_jokers++;
        }
    }
    if (!pattern_separation.empty()) 
    {
        all_patterns.emplace_back(pattern_separation, pattern.size());
    }
    std::cout << "Строка успешно раздерена по разделителю джокер. Полученные подстроки: \n";
    for (int i = 0; i < all_patterns.size(); i++) 
    {
        std::cout << all_patterns[i].first << ' ';
    }
    std::cout << '\n';
    DFA new_dfa(all_patterns, last_jokers);
    new_dfa.aho_corasick(text);
    return 0;
}