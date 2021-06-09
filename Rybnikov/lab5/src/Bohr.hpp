#pragma once

#include "Bohr.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#define RES_2

#ifdef RES_1
#define WORDS_COUNT 5

struct BohrVertex {
    
    int NextVertex[WORDS_COUNT] = {};             // номер вершины в которую происходит переход по символу с этим же номером в алфавите
    int PatternNumber = 0;                      // номер строки образа
    int ParentIndex = 0;
    int SuffixLink = {-1};                      // индекс суфф.ссылки наиб. суффикса
    int MoveSymbol[WORDS_COUNT] = {};           // переход по символам алфавита(индекс)
    char ParentMoveSymbol;                      // индекс символа, по которому идет переход от родителя к текущей вершине
    bool EndOfStr = false;                      // флаг конца подстроки, т.е проверка вершины на исходную строку
    
    BohrVertex(size_t m_ParentNumber, char m_ParentMoveSymbol) : ParentIndex(m_ParentNumber), ParentMoveSymbol(m_ParentMoveSymbol){
        std::fill_n(NextVertex, WORDS_COUNT, -1);
        std::fill_n(MoveSymbol, WORDS_COUNT, -1);
    }
};


class Bohr{
    std::vector<BohrVertex> bohr;
    std::vector<std::string> patterns;
    std::map<char, int> alphabet{ { 'A', 0 }, { 'C', 1 }, { 'G', 2 }, { 'T', 3 }, { 'N', 4 } };
public:
    Bohr();
    ~Bohr() = default;
    void AddInBohr(std::string &str);             
    int GetSuffix(int vertex);
    int Move(int vertex, int symb);      
    void AhoK(const std::string &str);
    void Print(int vertex, int i);          
    
};

#endif

// ##########################################################################################
// ##########################################################################################
// ##########################################################################################

#ifdef RES_2
struct BohrVertex{
    std::map<char, int> NextVertex;
    std::map<char, int> MoveSymbol;
    bool EndOfStr = false;
    int PatternNumber = 0;
    int Suffix = {-1};
    int GoodSuffix = {0};
    int ParentNumber = 0;
    char ParentMoveSymbol;
    BohrVertex(size_t m_ParentNumber, char symb) : ParentNumber(m_ParentNumber), ParentMoveSymbol(symb), EndOfStr(false), Suffix(-1), GoodSuffix(-1) {}
};

class Bohr{
    std::vector<BohrVertex*> bohr;
    std::vector<std::string> patterns;
    char joker{};
    std::string text;
    std::string str;
    
    std::map<char, int> alphabet{ { 'A', 0 }, { 'C', 1 }, { 'G', 2 }, { 'T', 3 }, { 'N', 4 } };
    
public:
    Bohr(){bohr.emplace_back(new BohrVertex(0, '$'));}
    ~Bohr();
    void AddInBohr(const std::string &str);
    int GetSuffix(int vertex);
    int Move(int vertex, char symb);
    void Print(int vertex, int i);
    void AhoK();
    void Init();
};


#endif
