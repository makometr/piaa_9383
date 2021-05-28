#include "task2.hpp"

void input(std::string& str1, std::string& str2, std::istream& in)
{
    in >> str1 >> str2;
}

std::vector<int> prefix(std::string &str)
{
    std::vector<int> pi(str.length());
    pi[0]=0;
    int i = 1, j = 0;
    while (i < str.length())
    {
        if (str[i] == str[j])
        {
            pi[i] = j + 1;
            i++;
            j++;
        }
        else if (j == 0)
        {
            pi[i] = 0;
            i++;
        }
        else
        {
            j = pi[j - 1];
        }
    }

     /*std::cout<<"Префикс-функция:"<<'\n';
    for(auto i:str)
    {
        std::cout<<i<<' ';
    }
    std::cout<<'\n';
    for(auto i:pi)
    {
        std::cout<<i<<' ';
    }
    std::cout<<'\n';*/

    return pi;
}

int KMP(std::string& A, std::string& B)
{
    int result = -1;
    if(A.size()!=B.size())
    {
        return result;
    }
     B += " "+A + A;
    std::vector<int> pi = prefix(B);

    for (int k = A.length() + 1; k < B.length(); k++)
    {
        if (pi[k] == A.length())
        {
            result = k -2 * A.length();
            break;
        }
    }
    return result;
}