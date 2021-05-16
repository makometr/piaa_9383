#pragma once

#include <vector>
#include <string>


inline std::vector<int> PrefixFunction(const std::string& s) {
    std::vector<int> prefix_array(s.size());

    for (int i = 1; i < s.size(); ++i) {
        int j = prefix_array[i-1];
        while (j > 0 && s[i] != s[j])
            j = prefix_array[j-1];

        if (s[i] == s[j])
            ++j;
        prefix_array[i] = j;
    }

    return prefix_array;
}

inline std::vector<int> KnutMorrisPratt(const std::string& source,
                                        const std::string& substring) {
    std::vector<int> start_indexes;

    auto prefix = PrefixFunction(substring + "#" + source);
    for (int i = 0; i < source.size(); ++i) {
        if (prefix[substring.size() + 1 + i] == substring.size())
            start_indexes.push_back(i - substring.size() + 1);
    }

    if (start_indexes.empty())
        start_indexes.push_back(-1);
    return start_indexes;
}

inline int CycleShiftDetect(const std::string& source,
                            const std::string& substring) {
    if (source.size() != substring.size())
        return -1;


    auto prefix = PrefixFunction(source + "#" + substring + substring);
    for (int i = substring.size() + 1; i < source.size() + 2*substring.size() + 1; ++i) {
        if (prefix[i] == substring.size()) {
            return i - 2 * substring.size();
        }
    }

    return -1;
}