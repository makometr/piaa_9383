#include <iostream>
#include <vector>
#include <string>
std::vector<int> PrefixFunction(std::string &KMP_string)
{
    int length = KMP_string.length();
    std::vector<int> PrefixArray(length);
    for (int i = 1; i < length; i++)
    {
        int k = PrefixArray[i - 1];
        while (k > 0 && KMP_string[i] != KMP_string[k])
            k = PrefixArray[k - 1];
        if (KMP_string[i] == KMP_string[k])
            ++k;
        PrefixArray[i] = k;
    }
    return PrefixArray;
}

void KMP(std::string &P, std::string &T)
{
    std::string KMP_string = P + '|' + T;
    std::string result = "";
    std::vector<int> PrefixArray = PrefixFunction(KMP_string);
    int length_P = P.length();
    for (int i = 0; i < KMP_string.length(); i++)
    {
        if (PrefixArray[i] == length_P)
            result += std::to_string(i - 2 * length_P) + ",";
    }
    if (result.empty())
    {
        std::cout << "-1";
        return;
    }
    result.pop_back(); //убираем последюю запятую
    std::cout << result;
}

int main()
{
    std::string P, T;
    std::cin >> P;
    std::cin >> T;
    KMP(P, T);
    return 0;
}