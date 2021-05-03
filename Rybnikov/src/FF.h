#pragma once
#include "Orgraph.h"
#include <set>
#include <vector>

class FF
{
	int m_MaxStream;
	Orgraph m_Graph;
	Orgraph m_Res;
	std::set<char> m_Visited;
	std::vector<Orgraph::Edge> m_Path;	// текущий путь

	char m_In;
	char m_Out;

	void Visit(Orgraph::Edge e);
	void MyPath();		// производит анализ одного найденого пути
	unsigned int GetMinW();	
public: 
	void Init(Orgraph& g, char in, char out);

	friend std::ostream& operator<<(std::ostream& os, FF& r);
};

