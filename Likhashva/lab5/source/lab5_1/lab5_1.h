#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>


class Bor {
public:
	Bor* parent;   // родительская вершина 
	Bor* SufLink; // суффиксная ссылка
	Bor* EndLink;  // конечная ссылка
	char ToParent;	// ребро, по которому попали из родительской вершины
	bool IsTerminal;  // терминальая вершина или нет (конец шаблона)
	std::map<char, Bor*> next;  //ребра по которым можно переходить
	std::vector<int> NumPattern;  // номера шаблонов, в которые входит символ, по которому пришли
	int TermNumPattern;

	Bor(Bor* parent = nullptr, char ToPrnt = 0) : parent(parent), ToParent(ToPrnt), SufLink(nullptr), EndLink(nullptr), IsTerminal(false) {
		if (parent == nullptr || ToPrnt == 0) { // создание корня
			this->parent = this;
			this->SufLink = this;
		}
	}

	~Bor() {
		for (auto i : this->next) {
			delete i.second;
		}
	}

	Bor* GetLink(const char& symbol) {
		if (this->next.find(symbol) != this->next.end()) { // если есть путь по заданному символу из текущей вершины
			return this->next.at(symbol);
		}
		if (this->SufLink == this) { // если в корне и путь не найден
			return this;
		}
		return this->SufLink->GetLink(symbol); // не в корне и путь не найден
	}
};


Bor* CreateBor(const std::vector<std::pair<std::string, int>>& patterns);
void Automaton(Bor* bor);
std::pair<int, int> LongestChain(Bor* bor, Bor* root, int& depth);
void AhoCorasick(const std::string& t, const std::vector<std::pair<std::string, int>>& patterns, std::vector<std::pair<int, int>>& result);