#include "API.h"

std::vector<int> prefix_function(std::string s) {
    if (s.empty()) {
        return {-1};
    }
    
    std::vector<int> p(s.size());
    p[0] = 0;
    for (int i = 1; i < s.size(); ++i) {
        int k = p[i - 1];
        while (k > 0 && s[i] != s[k]) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) {
            k++;
        }
        p[i] = k;
    }
    return p;
}

std::vector<int> KMP(std::string P, std::string T) {
    std::vector<int> indices;
    std::vector<int> prefix = prefix_function(P);
    for (int i = 0, j = 0; i < T.size();) {
        if (T[i] != P[j]) {
            if (j == 0) {
                i++;
            }
            j = prefix[j - 1];
        }
        else if (j == P.size() - 1) {
            indices.push_back(i - P.size() + 1);
            j = prefix[j - 1] + 1;
            ++i;
        }
        else {
            ++i;
            ++j;
        }
    }
    return indices;
}