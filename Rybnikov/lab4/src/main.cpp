#include <iostream>
#include <vector>
#include "KMP.hpp"

std::vector<int> SetResolve(KMP resolve, unsigned int digit, std::string str, std::string text, std::vector<int> res){
    switch (digit) {
        case 0:     // выбор первого задания
            res = resolve.Resolve_1(text, str);
            break;
        case 1:     // выбор второго задания
            res = resolve.Resolve_2(text, str);
            break;
        default:
            break;
    }
    return res;
}

int main(int argc, const char * argv[]) {
    std::string m_Str;   // подстрока
    std::string m_Text;  // текст
    std::vector<int> res;   // результат
    std::cout << "Enter substring and text: " << std::endl;
    std::cin >> m_Str;
    std::cin >> m_Text;
    
    // для выбора решения
    unsigned int function;
    std::cout << "Choise resolve [0;1]: " << std::endl;
    std::cin >> function;
    // проверяем корректность выбора решения
    while(function > 1){
        std::cout << "Bad resolve, try again..." << std::endl;
        std::cin >> function;
    }
    // создаём решение
    KMP resolve;
    // выбираем решение
    res = SetResolve(resolve, function, m_Str, m_Text, res);
    // печатаем на экран
    resolve.PrintResult(res, m_Text, m_Str);
    
    return 0;
}
