#pragma once
#include "Resolver2.h"
#include <vector>

// решает 3 задачу
class Resolver3
{
	std::vector<char> _Result;
public:
	void Resolve(Graph& g, char start, char end1, char end2);

	friend std::ostream& operator<<(std::ostream& os, Resolver3 r);
};
