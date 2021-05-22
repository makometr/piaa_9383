#include <vector>
#include <string>
#include <iostream>

std::vector<size_t> prefix_function (const std::string& s) 
{
    std::cout << "-------------Начало вычисления префикс-функции-------------\n";
    std::vector<size_t> prefix_array(s.length());
    for (size_t i = 1; i < s.length(); i++) 
    {
        size_t j = prefix_array[i-1]; 
        while ((j > 0) && (s[i] != s[j])) 
        {
            j = prefix_array[j-1];
        }
        if (s[i] == s[j])
        {
            j++;
        }
        std::cout << "Значение префикс-функции для первых " << i+1 << " элементов = " << j << "\n"; 
        prefix_array[i] = j;
     }
     std::cout << "-------------Конец вычисления префикс-функции-------------\n\n";
     return prefix_array;
}

std::vector<size_t> kmp(const std::string& pattern, const std::string& text) 
{
    std::vector<size_t> prefix_array = prefix_function(pattern);
    
    size_t j = 0;
    std::vector<size_t> answer;
    std::cout << "-------------Начало вычисления алгоритма Кнут-Моррис-Пратта-------------\n";
    for(size_t i = 0; i < text.size(); i++) 
    {
        while((j > 0) && (pattern[j] != text[i]))
        {
            std::cout << "Найдено несовпадение символов <" << pattern[j] << "> и <" << text[i] << ">.";
            j = prefix_array[j-1];
            std::cout << " Текущее значение длины цепочки = " << j << "\n";
        }
        if(pattern[j] == text[i])
        {
            j++;
            std::cout << "Найдено совпадение символа <" << text[i] << ">\n";
            std::cout << "Длина совпадающей цепочки символов = " << j << "\n";
        }
        if(j == pattern.size()) 
        {
            answer.push_back(i + 1 - pattern.size());
            std::cout << "Найдено выхождение подстроки с индексом: " << i+1-pattern.size() << "\n";
        }
    }
    std::cout << "-------------Конец вычисления алгоритма Кнут-Моррис-Пратта-------------\n\n";
    return answer;
}

int main()
{
    std::string pattern;
    std::string text;
    std::cin >> pattern;
    std::cin >> text;
    if (pattern.length() > text.length())
    {
        std::cout << "Длина подстроки больше длины строки. Код возврата: -1";
        return 0;
    }
    std::vector<size_t> answer = kmp(pattern, text);
    if(answer.empty())
    {
        std::cout << "Не найдено ни одного вхождения подстроки в строку. Код возврата: -1";
        return 0;
    }  
    std::cout << "--------Полученный результат--------\n";
    for(int i = 0; i < answer.size(); i++) 
    {
        if(i == answer.size() - 1) 
        {
            std::cout << answer[i];
        }
        else 
        {
            std::cout << answer[i] << ",";
        }
    }
    return 0;
}
