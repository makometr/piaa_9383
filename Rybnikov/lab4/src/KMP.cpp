#include "KMP.hpp"

std::vector<int> KMP::FindPrefix(const std::string &str){
    if(str.empty()){
        throw "Prefix error";
    }
    
    std::vector<int> pi;
    pi.resize(str.length());
    
    for(auto i = 1; i < str.length(); ++i){
        auto j = pi[i-1];
        
        while(j > 0 && str[i] != str[j]) j = pi[j - 1];
        
        if(str[i] == str[j])
            pi[i] = j + 1;
        else
            pi[i] = j;
    }
    return pi;
}

std::vector<int> KMP::Resolve_1(const std::string &m_Text, const std::string &m_Str){
    // ограничитель
    if(m_Text.empty() || m_Str.empty()){
        throw "Reslove_1 error";
    }
    
    std::vector<int> res;
    std::vector<int> pi = KMP::FindPrefix(m_Str + '#' + m_Text);
    
    const int sizeStr = m_Str.length();     // размер подстроки
    const int sizeText = m_Text.length();   // размер всего текста
    
    for(int i = 0; i < sizeText; ++i){
        if(pi[sizeStr + 1 + i] == sizeStr)
            res.__emplace_back(i - sizeStr + 1);
    }
    
    if(res.empty())
        res.__emplace_back(-1);
    
    return res;
}

std::vector<int> KMP::Resolve_2(const std::string &m_Text, const std::string &m_Str){
    // ограничители
    if(m_Text.empty() || m_Str.empty()) throw "Resolve_2 error";
    if(m_Text.length() != m_Str.length()){
        std::vector<int> res = {-1};
        return res;
    }
    
    std::vector<int> pi = KMP::FindPrefix(m_Text + '#' + m_Str + m_Str);
    const int sizeStr = m_Str.length();     // размер подстркои
    const int sizeText = m_Text.length();   // размер текста
    std::vector<int> res;
    
    for(int i = 0; i < 2*sizeText; ++i){
        if(pi[sizeStr + 1 + i] == sizeStr){
            res.__emplace_back(i - sizeStr + 1);
            break;
        }
    }
    // проверка на пустое решение
    if(res.empty()) res.__emplace_back(-1);
    return res;
}

std::vector<int> KMP::PrintResult(std::vector<int> res, const std::string &m_Text, const std::string &m_Str){
    for(auto i = 0; i < res.size(); ++i){
        std::cout << res[i];
        if(i != res.size() - 1)
            std::cout << ',';
    }
    std::cout << std::endl;
    return res;
    
}


