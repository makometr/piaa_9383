#include "Orgraph.h"
#include <algorithm>

std::istream& operator>>(std::istream& is, Orgraph& g)
{
	Orgraph::Edge e;
	g.m_Edges.clear();
	for(int i=0;i< g.m_EdgesCount;++i){
		is >> e;
		g.m_Edges.push_back(e);
	} 
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
std::vector<Orgraph::Edge> Orgraph::operator[](char node)
{
	std::vector<Edge> res;
	for (auto i = m_Edges.begin(); i < m_Edges.end(); ++i) {
		if (i->Start() == node) res.push_back(*i);
	}
	std::sort(res.begin(), res.end(), std::less<Edge>());
	return res;
}

void Orgraph::Set(Edge e) {
	// попытка записать заного ребро
	for (int i = 0; i < m_Edges.size(); ++i) {
		if (m_Edges[i].Start() == e.Start() && m_Edges[i].End() == e.End()) {
			m_Edges[i] = e;
			return;
		}
	}
	// вставка вконец
	m_Edges.push_back(e);
}
void Orgraph::SetEdgesCount(int count) {
	m_Edges.clear();
	m_EdgesCount = count;
}
Orgraph::Edge& Orgraph::Get(char start, char end) {
	for (int i = 0; i < m_Edges.size(); ++i) {
		if (m_Edges[i].Start() == start && m_Edges[i].End() == end)
			return m_Edges[i];
	}

	throw "error";
}
