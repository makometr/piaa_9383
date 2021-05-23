#include <vector>
#include <string>
#include <iostream>

std::vector<int> prefix_function (const std::string& s) 
{
    std::cout << "-------------Начало вычисления префикс-функции-------------\n";
    std::vector<int> prefix_array(s.length());
    for (int i = 1; i < s.length(); i++) 
    {
        int j = prefix_array[i-1]; 
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

std::vector<int> kmp(const std::string& pattern, const std::string& text) 
{
    std::vector<int> prefix_array = prefix_function(pattern);
    
    int j = 0;
    std::vector<int> answer;
    std::cout << "-------------Начало вычисления алгоритма Кнут-Моррис-Пратта-------------\n";
    for(int i = 0; i < text.size(); i++) 
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

std::vector<int> cyclic_shift(const std::string& pattern, const std::string& text) 
{
    std::cout << "-------------Начало проверки на циклический сдвиг-------------\nСтрока А: " << text << "\n";
    std::cout << "Строка В, измененная для поиска: " << pattern+pattern << "\n\n";
    std::vector<int> answer = kmp(text, pattern+pattern);
    std::cout << "-------------Конец проверки на циклический сдвиг-------------\n";
    return answer;
}

int main()
{
    std::string pattern;
    std::string text;
    std::cin >> pattern;
    std::cin >> text;
    if (pattern.size() != text.size())
    {
        std::cout << "-1"; 
        return 0;
    }
    if (pattern.size() == 0 || text.size() == 0)
    {
        std::cout << "Одна из строк пуста. Код возврата: -1";  
        return 0;
    }
    std::vector<int> answer = cyclic_shift(pattern, text);
    if (answer.empty())
    {
        std::cout << "Строка В не является циклическим сдвигом строки А. Код возврата: -1";  
        return 0;
    }
    std::cout << "Строка В является циклическим сдвигом строки А. Первый индекс сдвига: " << answer[0];
    return 0;
}
