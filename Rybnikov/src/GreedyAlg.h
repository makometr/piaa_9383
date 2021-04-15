#pragma once
#include <vector>
#include "Orgraph.h"

class GreedyAlg
{
	std::vector<Orgraph::Edge> m_Result;
	std::vector<Orgraph::Edge> m_Current;
	Orgraph m_Graph;
	char m_Start;
	char m_End;
	void Scan(Orgraph::Edge edge);
	float Weight(std::vector<Orgraph::Edge> path);
public:

	void Resolve(Orgraph g, char start, char end);

	friend std::ostream& operator<<(std::ostream& os, GreedyAlg r);
};

