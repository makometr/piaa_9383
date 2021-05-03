#pragma once
#include <iostream>

// ребро графа
class Edge
{
	char _From;
	char _To;
	unsigned int _Weight;
public:

	Edge();
	Edge(char from, char to, unsigned int weight);

	char From();		// откуда
	char To();			// куда
	unsigned int Weight();	// с каким весом
	void SetWeight(int weight) { _Weight = weight; }

	friend std::istream& operator>>(std::istream& is, Edge& e);
	friend std::ostream& operator<<(std::ostream& os, Edge& e);
	friend bool operator<(const Edge& a, const Edge& b);
	friend bool operator>(const Edge& a, const Edge& b);
};
