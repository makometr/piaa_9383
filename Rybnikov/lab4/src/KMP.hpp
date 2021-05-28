#ifndef KMP_hpp
#define KMP_hpp

#include <iostream>
#include <string>
#include <vector>

class KMP{
    const std::string m_Text;   // текст
    const std::string m_Str;    // подстрока
     
public:
    std::vector<int> FindPrefix(const std::string &m_Text);                             // поиск префик функции
    std::vector<int> Resolve_1(const std::string &m_Text, const std::string &m_Str);    // первое задание
    std::vector<int> Resolve_2(const std::string &m_Text, const std::string &m_Str);    // второе задание
    
    std::vector<int> PrintResult(std::vector<int> res, const std::string &m_Text, const std::string &m_Str);
};
#endif /* KMP_hpp */
