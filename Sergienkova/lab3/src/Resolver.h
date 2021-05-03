#pragma once
#include <iostream>
#include "Graph.h"

class Resolver
{
	Graph _Graph;	// исходный граф
	Graph _Result;	// результирующий граф
	char _In;		// исток
	char _Out;		// сток
	int _MaxStream;	// максимальный поток из истока в сток
	std::vector<char> _Path; // текущий путь

	void Go(char point);	// переходит в указанную вершину при сканировании вершин
	bool Contains(std::vector<char>& path, char point);
	void CheckPath();	// проверяет найденый путь (по алгоритму)
public:
	void Resolve(Graph &g, char in, char out);

	friend std::ostream& operator<<(std::ostream& os, Resolver& r);
};

