#include "task1.hpp"
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
/*
     std::cout<<"Префикс-функция:"<<'\n';
    for(auto i:str)
    {
        std::cout<<i<<' ';
    }
    std::cout<<'\n';
    for(auto i:pi)
    {
        std::cout<<i<<' ';
    }
    std::cout<<'\n';
*/
    return pi;
}

Result KMP(std::string P, std::string T)
{
    std::string P_T = P + " " + T;
    Result result;
    std::vector<int> pi = prefix(P_T);

    for (int k = P.length() + 1; k < P_T.size(); k++)
    {
        if (pi[k] == P.length())
        {
            result.push_back(k -2* P.length());
        }
    }
    return result;
}

void output(Result result, std::ostream& out)
{
    if(result.size()==0)
    {
        out<<-1;
        return;
    }
    for (int i = 0; i < result.size()-1; i++)
    {
        out<< result[i] << ',';
    }
    out << result[result.size() - 1];
}
