#include "lab4_1.hpp"

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
    std::vector<int> answer;
    std::vector<int> pi = prefix_function(P);
    int l = 0;
    for (size_t k = 0; k < T.size(); k++) {
        if (T[k] == P[l]) {
            l++;    
            if (l == P.size()) {
                answer.push_back(k + 1 - P.size());
            }  
        }
        else if (l != 0){
            l = pi[l-1];
            k--;
        }
    }
    return answer;
}