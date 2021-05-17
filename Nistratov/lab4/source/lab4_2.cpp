#include "lab4_2.hpp"

std::vector<int> prefix_function (std::string s){
    size_t n =  s.length();
    std::vector<int> pi(n);
    for (size_t i=1; i<n; ++i) 
    {
        size_t j = pi[i-1];
        while ((j > 0) && (s[i] != s[j])) 
            j = pi[j-1];

        if (s[i] == s[j]) 
            ++j;
        pi[i] = j;
     }
     return pi;
} 

std::vector<int> KMP(std::string& P, std::string& T){
    P += P;
    std::vector<int> answer;
    std::vector<int> pi = prefix_function(T);
    int l = 0;
    for (size_t k = 0; k < P.size(); k++) {
        if (P[k] == T[l]) {
            l++;    
            if (l == T.size()) {
                answer.push_back(k + 1 - T.size());
            }  
        }
        else if (l != 0){
            l = pi[l-1];
            k--;
        }
    }
    return answer;
} 