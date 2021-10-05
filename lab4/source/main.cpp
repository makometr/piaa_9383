#include <iostream>
#include <vector>
#include <string>

#define RES
//#define RES2

std::vector<int> prefix(const std::string& text) {
    int n = text.length();
    std::vector<int> pi(text.length(), 0);

    for (size_t i = 1; i < n; ++i) {
        size_t j = pi[i - 1];
        while (j > 0 && text[i] != text[j]) {
            j = pi[j - 1];
        }
        if (text[i] == text[j]) {
            pi[i] = j + 1;
        }
        else {
            pi[i] = j;
        }
    }
    return pi;
}


std::vector<int> KMP(const std::string& text, const std::string& str) {
    std::vector<int> result;
    std::vector<int> pi = prefix(str);
    size_t strInd = 0;
    for (size_t textInd = 0; textInd < text.size(); textInd++) {
        if (text[textInd] == str[strInd]) {
            strInd++;
            if (strInd == str.size()) {
                result.push_back(textInd - str.size() + 1);
            }
            continue;
        }
        if (strInd == 0) continue;
        strInd = pi[strInd - 1];
        textInd--;
    }
    if (result.empty())
        result.push_back(-1);
    return result;
}

std::vector<int> KMP_2(const std::string& text, const std::string& str) {
    const int LenText = text.length();
    const int LenStr = str.length();
    if (LenText != LenStr) {
        std::vector<int> result = { -1 };
        return result;
    }
    std::vector<int> result = KMP(str + str, text);
    return result;
}

int main() {
    std::vector<int> result;
    std::string str;
    std::string text;
    std::cin >> str;
    std::cin >> text;
#ifdef RES
    result = KMP(text, str);
    for (auto i = 0; i < result.size(); i++) {
        std::cout << result[i];
        if (i + 1 != result.size())
            std::cout << ",";
    }
#endif
#ifdef RES2
    result = KMP_2(text, str);
    std::cout << result[0];
#endif
    std::cout << std::endl;
    return 0;
}