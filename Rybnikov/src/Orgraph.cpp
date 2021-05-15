#include "Orgraph.h"
#include <algorithm>

std::istream& operator>>(std::istream& is, Orgraph& g)
{
	Orgraph::Edge e;
	is >> g.m_Start;
	is >> g.m_End;
	do {
		is >> e;
		g.m_Edges.push_back(e);
	} while (e.End() != g.m_End);
	return is;
}
std::ostream& operator<<(std::ostream& os, Orgraph& g) {
	for (auto i = g.m_Edges.begin(); i < g.m_Edges.end(); ++i)
		os << *i << std::endl;
	return os;
}
std::istream& operator>>(std::istream& is, Orgraph::Edge& e) {
	return is >> e.m_Start >> e.m_End >> e.m_W;
}
std::ostream& operator<<(std::ostream& os, Orgraph::Edge& e) {
	return os << e.m_Start << ' ' << e.m_End << ' ' << e.m_W;
}
std::vector<Orgraph::Edge> Orgraph::operator[](char node)	// возвращает все исходящие ребра из указанной вершины, причем все исходящие вершины сортируются
{
	std::vector<Edge> res;
	for (auto i = m_Edges.begin(); i < m_Edges.end(); ++i) {
		if (i->Start() == node) res.push_back(*i);
	}
	std::sort(res.begin(), res.end(), std::less<Edge>());
	return res;
}