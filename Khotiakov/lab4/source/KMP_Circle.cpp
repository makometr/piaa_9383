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

void KMP_Circle(std::string &P, std::string &T)
{
    if (P.empty() || T.empty())
    {
        std::cout << "-1";
        return;
    }
    int length_P = P.length();
    P += '|' + T;
    std::vector<int> PrefixArray = PrefixFunction(P);
    for (int i = 0; i < P.length(); i++)
    {
        if (PrefixArray[i] == length_P)
        {
            std::cout << std::to_string(i - 2 * length_P);
            return;
        }
    }
    std::cout << "-1";
}

int main()
{
    std::string P, T;
    std::cin >> P;
    std::cin >> T;
    if (P.length() != T.length())
    {
        std::cout << "-1";
        return 0;
    }
    P += P;
    KMP_Circle(T, P);
    return 0;
}