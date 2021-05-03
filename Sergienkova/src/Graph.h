#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "Edge.h"

// граф
class Graph
{
	std::map<char, std::vector<Edge> > _Data; // набор ребер на каждый узел
	int m_EdgesCount;
public:

	int EdgesCount() { return m_EdgesCount; }
	void Reset(int edgesCount) { _Data.clear(); m_EdgesCount = edgesCount; }

	std::vector<Edge> operator[](char node); // возвращает сортированный по весам вектор ребер из указанной вершины
	void Set(Edge e);	// задает ребро
	Edge& Get(char from, char to);	// возаращает ссылку на ребро

	std::map<char, std::vector<Edge> >::iterator begin() { return _Data.begin(); }
	std::map<char, std::vector<Edge> >::iterator end() { return _Data.end(); }

	friend std::istream& operator>>(std::istream& is, Graph& g);
	friend std::ostream& operator<<(std::ostream& os, Graph& g);
};

