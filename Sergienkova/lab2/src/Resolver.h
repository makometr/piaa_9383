#pragma once
#include <iostream>
#include <vector>
#include "Graph.h"

// производит решение задачи
class Resolver
{
	std::vector<Edge> _Result;	// результат
	bool Go(Edge edge, Graph& g, std::vector<Edge>& path, char end);		// посещает указанную вершину
	double Weight(std::vector<Edge>& path);	// вес указанного пути 
public:
	void Resolve(Graph& g, char a, char b);

	friend std::ostream& operator<<(std::ostream& os, Resolver r);
};

