#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

//компаратор для сортировки контейнера std::vector<std::pair<int, int>> по возрастанию обоих элементов пары
bool cmp_for_vec_pair(std::pair<int, int> elem1, std::pair<int, int> elem2) 
{
    if (elem1.first < elem2.first) 
    {
        return true;
    }
    else if (elem1.first == elem2.first && elem1.second < elem2.second) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

//структура для хранени и работы с бором, в частности для добавления суффиксной ссылки для текущей вершины
struct Bor 
{
    char edge;
    int final_vertex_number;
    std::vector<Bor*> children;
    Bor* parent;
    Bor* suffix_link;
    Bor* end_suffix_link;

    Bor (char new_edge, Bor* new_parent)
    {
        edge = new_edge;
        final_vertex_number = 0;
        parent = new_parent;
        suffix_link = nullptr;
        end_suffix_link = nullptr;
    }

     void delete_children() 
     {
        for (auto &child : this->children) 
        {
            child->delete_children();
            delete child;
        }
    }
    
    //функция для спуска по бору по ребру к потомку
    Bor* go_to_child_by_edge (char child_edge)
    {
        for (auto &child : children) 
        {
            if (child->edge == child_edge) 
            {
                return child;
            }
        }
        return nullptr;
    }
    
    //функция создания ссылки для одной вершины
    void add_suffix_link ()
    {
        if (edge == '@') //если это корень, то ссылка в себя
        {
            std::cout << "Текущая вершина - корень, ссылается на себя.\n";
            suffix_link = this;
        } 
        else if (parent->edge == '@') //если предок корень, то ссылка в предка, т.е. в корень
        {
            std::cout << "Текущая вершина с ребром " << edge << " потомок корня, ссылается на корень.\n";
            suffix_link = parent;
        } 
        else //если же корень не близко - нужно смотреть
        {
            std::cout << "Текущая вершина с ребром " << edge << " далека от корня, начато построение ссылки. ";
            Bor* current_state = parent->suffix_link; //суффиксная ссылка родителя
            Bor* next_state = current_state->go_to_child_by_edge(edge); //пытаемся от родителя пройти по текущему символу вниз
            while (next_state == nullptr) //если пройти не получилось - нет такого ребра
            {
                if (current_state->edge == '@') //если уперлись в корень
                {
                    next_state = current_state; //то сохраняем для ссылки корень и выходим
                    break;
                }   //если нет
                current_state = current_state->suffix_link; //проходим по ссылке дальше
                next_state = current_state->go_to_child_by_edge(edge); //пытаемся снова спуститься
            }
            suffix_link = next_state;  //сохраняем нашу получившуюся ссылку
            //далее проверим вершину на конечность
            while (next_state->final_vertex_number == 0) //если вершина не конечная для какой-то подстроки
            {
                if (next_state->edge == '@')  //если пришли в корень, то дальше некуда, заканчиваем
                {
                    break;
                }
                next_state = next_state->suffix_link;  //иначе идем по суффиксной ссылке дальше
            }
            if (next_state->final_vertex_number > 0)  //если так получилось, что мы нашли вершину и она конечная
            {
                end_suffix_link = next_state; //запоминаем ее в конечную суффиксную ссылку
            }
            std::cout << "Построение ссылки завершено.\n";
        }
    }
};

//структура для конечного детерминированного автомата
struct DFA 
{
    Bor* root;
    std::vector<std::string> patterns;
    
    DFA (std::vector<std::string>& new_patterns) 
    {
        root = new Bor('@', nullptr);
        patterns = new_patterns;
        bild_bor(new_patterns);
        add_all_suffix_links();
    }

    ~DFA () 
    {
        root->delete_children();
        delete root;
    }
    
    //создание бора путем добавления в него строк-паттернов
    void bild_bor (std::vector<std::string>& new_patterns) 
    {
        std::cout << "----------Начинаем построение бора----------\n";
        int string_number = 1;
        for (auto &current_pattern : new_patterns) 
        {
            Bor* current_state = root;  //текущее состояние в корне
            for (int i = 0; i < current_pattern.size(); i++) 
            {
                Bor* next_state = current_state->go_to_child_by_edge(current_pattern[i]); //пробуем перейти к ребенку
                if (next_state == nullptr) //если вершины при переходе по ребру еще нет
                {
                    next_state = new Bor(current_pattern[i], current_state); //создаем вершину
                    current_state->children.push_back(next_state);  //добавляем ее в число детей
                }
                if (i == current_pattern.size()-1)  //если строка закончилась - то текущая вершина терминальная для данной подстроки
                {
                    next_state->final_vertex_number = string_number; //добавляем ее номер
                    std::cout << "Строка " << current_pattern << " добавлена в бор\n";
                } 
                else 
                {
                    current_state = next_state; //иначе просто переходим дальше, т.к. вершина уже есть
                }
            }
            string_number++;
        }
        std::cout << "----------Построение бора закончено----------\n\n";
    }

    //создаем суффиксные ссылки для каждой вершины
    void add_all_suffix_links () 
    {
        std::cout << "----------Начинаем создание суффиксных ссылок----------\n";
        std::queue<Bor*> queue; //используем очередь, чтобы ходить по вершинам
        Bor* current_state = root;  //начинаем с корня
        queue.push(root);
        while (!queue.empty())  //пока есть по чему ходить
        {
            current_state->add_suffix_link(); //создаем ссылку для текущей вершины
            queue.pop(); //удаляем ее из очереди, т.к. обработали
            for (auto &current_child : current_state->children)  //добавляем всех ее детей в очередь на обработку
            {
                queue.push(current_child);
            }
            current_state = queue.front(); //переходим к следующей в очереди вершине для обработки
        }
        std::cout << "----------Создание суффиксных ссылок закончено----------\n\n";
    }

    //сам алгоритм Ахо-Корасик
    void aho_corasick (std::string& text) 
    {
        std::cout << "----------Начинаем алгоритм Ахо-Корасика----------\n";
        Bor* current_state = root; //начинаем хождение из корня
        std::vector<std::pair<int, int>> result;  //вектор записи результата
        for (int i = 0; i < text.size(); i++) //проходимся по символам текста
        {
            Bor* next_state = current_state->go_to_child_by_edge(text[i]);   //спускаемся из текущей вершине по ребру из текста к потомку
            while (next_state == nullptr) //если такого ребра у нас нет
            {
                if (current_state == root)  //если мы сейчас находимся в корне переходим в него же и прерываем
                {
                    next_state = current_state;
                    break;
                }
                current_state = current_state->suffix_link; //если нет, то переходим по суффиксной ссылке
                next_state = current_state->go_to_child_by_edge(text[i]); //и снова пытаемся спустится
            }
            if (next_state->final_vertex_number > 0) //если мы достигли конечной вершины какого-то слова-запоминаем
            {
                std::cout << "Найдено вхождение образца: " << patterns[next_state->final_vertex_number-1] << '\n';
                result.emplace_back(i-patterns[next_state->final_vertex_number-1].size()+2, next_state->final_vertex_number);
            }
            if (next_state->end_suffix_link != nullptr) //если для следующего состояния есть ссылка на конец
            {
                Bor* tmp_state = next_state->end_suffix_link;
                while (tmp_state != nullptr)  //то пока она указывает на конец - добавляем в результат
                {
                    result.emplace_back(i-patterns[tmp_state->final_vertex_number-1].size()+2, tmp_state->final_vertex_number);
                    tmp_state = tmp_state->end_suffix_link;
                }
            }
            current_state = next_state; //переходим к следующей
        }
        std::cout << "----------Алгоритм Ахо-Корасика закончен----------\n\n";
        std::sort(result.begin(), result.end(), cmp_for_vec_pair); //сортируем согласно заданию
        print_result(result); //печатаем на экран
    }
    
    //функция печати на экран результата
    void print_result (std::vector<std::pair<int, int>>& result)
    {
        std::cout << "----------Результат работы алгоритма----------\n";
        for (auto &answer : result) 
        {
        std::cout << "Позиция в тексте: " << answer.first << " Номер образца: " << answer.second << '\n';
        }
    }
};

int main () 
{
    std::cout << "Введите текст T:\n";
    std::string text;
    std::cin >> text;
    std::cout << "Введите количество подстрок:\n";
    int number_pattenrs;
    std::cin >> number_pattenrs;
    std::cout << "Введите все подстроки:\n\n";
    std::vector<std::string> patterns;
    std::string new_pattern;
    for (int i = 0; i < number_pattenrs; i++) 
    {
        std::cin >> new_pattern;
        patterns.push_back(new_pattern);
    }
    DFA new_DFA(patterns);
    new_DFA.aho_corasick(text);
    return 0;
}