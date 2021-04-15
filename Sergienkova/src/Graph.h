#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "Edge.h"

// граф
class Graph
{
	std::map<char, std::vector<Edge> > _Data; // набор ребер на каждый узел
	char _Start;
	char _End;
public:

	char Start();
	char End();

	std::vector<Edge> operator[](char node); // возвращает сортированный по весам вектор ребер из указанной вершины

	friend std::istream& operator>>(std::istream& is, Graph& g);
	friend std::ostream& operator<<(std::ostream& os, Graph& g);
};

