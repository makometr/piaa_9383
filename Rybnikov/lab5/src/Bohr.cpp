#include "Bohr.hpp"

#define RES_2

#ifdef RES_1
Bohr::Bohr(){
    bohr.emplace_back(0,0);
}
// ------------------------------------------------
void Bohr::AddInBohr(std::string &str){
    int n = 0;
    for(auto &i : str){
        int symb;
        if(alphabet.find(i) != alphabet.end())
            symb = alphabet[i];
        else
            symb = 5;
        
        if(bohr[n].NextVertex[symb] == -1){
            bohr.emplace_back(n, symb);
            bohr[n].NextVertex[symb] = bohr.size() - 1;
        }
        n = bohr[n].NextVertex[symb];
    }
    bohr[n].EndOfStr = true;
    patterns.emplace_back((str));
    bohr[n].PatternNumber = static_cast<int>(patterns.size()) - 1;
    }

// ------------------------------------------------
int Bohr::GetSuffix(int vertex){
    if(bohr[vertex].SuffixLink == -1){
        if(vertex == 0 || bohr[vertex].ParentIndex == 0){
            bohr[vertex].SuffixLink = 0;
        }
        else{
            bohr[vertex].SuffixLink = Move(GetSuffix(bohr[vertex].ParentIndex), bohr[vertex].ParentMoveSymbol);
        }
    }
    return bohr[vertex].SuffixLink;
}
// ------------------------------------------------

int Bohr::Move(int vertex, int symb){
    if(bohr[vertex].MoveSymbol[symb] == -1){
        if(bohr[vertex].NextVertex[symb] != -1){
            bohr[vertex].MoveSymbol[symb] = bohr[vertex].NextVertex[symb];
        }
        else{
            if(vertex == 0){
                bohr[vertex].MoveSymbol[symb] = 0;
            }
            else{
                bohr[vertex].MoveSymbol[symb] = Move(GetSuffix(vertex), symb);
            }
        }
    }
    return bohr[vertex].MoveSymbol[symb];
}
// ------------------------------------------------

void Bohr::AhoK(const std::string &str){
    int u = 0;
    for(int i = 0; i < str.length(); i++){
        int symb;
        
        if(alphabet.find(str[i]) != alphabet.end()) symb = alphabet[str[i]];
        else symb = 5;
        
        u = Move(u, symb);
        Print(u, i + 1);
    }
}
// ------------------------------------------------
void Bohr::Print(int vertex, int i){
    for(int u = vertex; u != 0; u = GetSuffix(u)){
        if(bohr[u].EndOfStr)
            std::cout << i - patterns[bohr[u].PatternNumber].length() + 1 << " " << bohr[u].PatternNumber + 1 << std::endl;
    }
}
    Bohr::~Bohr(){
        bohr.clear();
        bohr.shrink_to_fit();
    }
// ------------------------------------------------
#endif

#ifdef RES_2
#include "Bohr.hpp"

void Bohr::AddInBohr(const std::string &str){
    int n = 0;
    for(auto &i : str){
        if(bohr[n]->NextVertex.find(i) == bohr[n]->NextVertex.end()){
            bohr.emplace_back(new BohrVertex(n, i));
            bohr[n]->NextVertex[i] = bohr.size() - 1;
        }
        n = bohr[n]->NextVertex[i];
    }
    bohr[n]->EndOfStr = true;
    patterns.emplace_back(str);
    bohr[n]->PatternNumber = static_cast<int>(patterns.size()) - 1;
}

    void Bohr::Init(){
        std::cin >> text;
        std::cin >> str;
        std::cin >> joker;
        AddInBohr(str);
        AhoK();
    }
    
int Bohr::GetSuffix(int vertex){
    if(bohr[vertex]->Suffix == - 1){
        if(vertex == 0 || bohr[vertex]->ParentNumber == 0) bohr[vertex]->Suffix = 0;
        else bohr[vertex]->Suffix = Move(GetSuffix(bohr[vertex]->ParentNumber), bohr[vertex]->ParentMoveSymbol);
    }
    return bohr[vertex]->Suffix;
}

int Bohr::Move(int vertex, char symb){
    if(bohr[vertex]->MoveSymbol.find(symb) == bohr[vertex]->MoveSymbol.end()){
        if(bohr[vertex]->NextVertex.find(symb) != bohr[vertex]->NextVertex.end()){
            bohr[vertex]->MoveSymbol[symb] = bohr[vertex]->NextVertex[symb];
        }
        else if(bohr[vertex]->NextVertex.find(joker) != bohr[vertex]->NextVertex.end()){
            bohr[vertex]->MoveSymbol[symb] = bohr[vertex]->NextVertex[joker];
        }
        else if (vertex == 0){
            bohr[vertex]->MoveSymbol[symb] = 0;
        }
        else{
            bohr[vertex]->MoveSymbol[symb] = Move(GetSuffix(vertex), symb);
        }
    }
    return bohr[vertex]->MoveSymbol[symb];
}

void Bohr::Print(int vertex, int i){
    for(int j = vertex; j != 0; j = GetSuffix(j)){
        if(bohr[j]->EndOfStr)
            std::cout << i + 2 - patterns[bohr[j]->PatternNumber].length() << std::endl;
    }
}

void Bohr::AhoK(){
    int j = 0;
    for(int i = 0; i < text.length(); i++){
        j = Move(j, text[i]);
        Print(j, i);
    }
}

    Bohr::~Bohr(){
        bohr.clear();
        bohr.shrink_to_fit();
    }

#endif
