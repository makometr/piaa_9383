#pragma once
#include <iostream>

// ребро графа
class Edge
{
	char _From;
	char _To;
	double _Weight;
public:

	Edge();
	Edge(char from, char to, double weight);

	char From();		// откуда
	char To();			// куда
	double Weight();	// с каким весом

	friend std::istream& operator>>(std::istream& is, Edge& e);
	friend std::ostream& operator<<(std::ostream& os, Edge& e);
	friend bool operator<(const Edge& a, const Edge& b);
	friend bool operator>(const Edge& a, const Edge& b);
};
