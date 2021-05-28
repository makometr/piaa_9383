#include "KMP.h"

void readStrings(std::string& str1, std::string& str2, std::istream& in) {
    in >> str1 >> str2;
}


std::vector<int> prefixFunc(std::string& text) {
    std::vector<int> prefix(text.size());
    int j = 0;
    for(size_t i = 1; i < text.size(); i++) {
        if(text[j] == text[i]) {
            prefix[i] = j + 1;
            j++;
            continue; 
        }
        if(j == 0) {
            prefix[i] = 0;
            continue;
        }
        j = prefix[j - 1];
        i--;
    }

    return prefix;
}

std::vector<int> KMP(std::string& pattern, std::string& text) {
    std::vector<int> answer;
    std::vector<int> prefix = prefixFunc(pattern);
    int l = 0;
    for (size_t k = 0; k < text.size(); k++) {
        if(text[k] == pattern[l]) {
            l++;
            if(l == (int)pattern.size()) {
                answer.push_back(k + 1 - pattern.size());
            }   
            continue;
        }
        if(l == 0) continue;
        l = prefix[l-1];
        k--;
    }
    return answer;
}