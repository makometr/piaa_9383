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

void KMP(std::string &P, std::string &T)
{
    std::string result = "";

    std::vector <int> prefixArray;

    int lengthP = P.length();

    P += "@" + T;

    prefixArray = prefixFunction(P);

    for(int i = 0; i < prefixArray.size(); i++)
    {
        if(prefixArray[i] == lengthP)
        {
            result += std::to_string(i - 2 * lengthP) + ",";
        }
    }

    if(result.length() == 0)
    {
        std::cout<<"-1";
    }
    else
    {
        result.pop_back();
        std::cout<<result;
    }
}

int main()
{
    std::string T, P, s;
    std::cin>>P>>T;

    KMP(P, T);

    return 0;
}
