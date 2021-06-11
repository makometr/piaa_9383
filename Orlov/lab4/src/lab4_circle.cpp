#include <iostream>
#include <vector>


std::vector<int> prefixFunction(std::string &str)
{
    int n = str.length();
    std:: vector<int> prefixArray(n, 0);

    for(int i = 1; i < str.length(); i++)
    {
        int j = prefixArray[i - 1];

        while((j > 0) && (str[i] != str[j]))
        {
            j = prefixArray[j - 1];
        }

        if(str[i] == str[j])
        {
            j++;
        }

        prefixArray[i] = j;
    }

    return prefixArray;
}

void KMP_Circle(std::string &P, std::string &T)
{
    std::vector <int> prefixArray;

    int lengthT = T.length();

    T += "@" + P;

    prefixArray = prefixFunction(T);

    for(int i = 0; i < prefixArray.size(); i++)
    {
        if(prefixArray[i] == lengthT)
        {
            std::cout<<i - 2 * lengthT;
            return;
        }
    }

    std::cout<<"-1";

}

int main()
{
    std::string T, P;
    std::cin>>P>>T;

    if(P.length() != T.length())
    {
        std::cout<<"-1";
        return 0;
    }

    P += P;

    KMP_Circle(P, T);

    return 0;
}
