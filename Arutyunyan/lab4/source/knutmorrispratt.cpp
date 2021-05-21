#include <iostream>
#include <vector>
#include <string>

#include "stringwrapper.hpp"
#include "knutmorrispratt.h"


constexpr bool DEBUG = false;


std::vector<int> PrefixFunction(const ConcatenatedStringsWrapper& s) {
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

std::vector<int> KnutMorrisPratt(const ConcatenatedStringsWrapper& source,
                                        const ConcatenatedStringsWrapper& substring) {
    std::vector<int> start_indexes;

    auto prefix = PrefixFunction(substring + StringWrapper{"#", 1} + source);

    if (DEBUG) {
        std::cout << "Префиксный массив:" << std::endl;
        for (int v : prefix) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < source.size(); ++i) {
        if (prefix[substring.size() + 1 + i] == substring.size())
            start_indexes.push_back(i - substring.size() + 1);
    }

    if (start_indexes.empty())
        start_indexes.push_back(-1);
    return start_indexes;
}

int CycleShiftDetect(const std::string& source,
                            const std::string& substring) {
    return source.size() == substring.size()
            ? KnutMorrisPratt(ConcatenatedStringsWrapper(substring) + substring, source)[0]
            : -1;
}
