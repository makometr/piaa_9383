#pragma once

#include <vector>
#include <string>

#include "stringwrapper.hpp"


inline std::vector<int> PrefixFunction(const StringWrapper& s) {
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

    auto prefix = PrefixFunction({MiniWrapper{substring.data(), substring.size()},
                                  MiniWrapper{"#", 1},
                                  MiniWrapper{source.data(), source.size()}});
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

    auto prefix = PrefixFunction({MiniWrapper{source.data(), source.size()},
                                  MiniWrapper{"#", 1},
                                  MiniWrapper{substring.data(), substring.size()},
                                  MiniWrapper{substring.data(), substring.size()}});

    for (int i = substring.size() + 1; i < source.size() + 2*substring.size() + 1; ++i) {
        if (prefix[i] == substring.size()) {
            return i - 2 * substring.size();
        }
    }

    return -1;
}