#include "GreedyAlg.h"

void GreedyAlg::Resolve(Orgraph g, char start, char end)
{
	m_Result.clear();
	m_Current.clear();

	m_Graph = g;
	m_Start = start;
	m_End = end;

	Scan(Orgraph::Edge(start, start, 0));
}
std::ostream& operator<<(std::ostream& os, GreedyAlg r) {
	if (r.m_Result.size() == 0) os << "has no result!";
	for (auto i : r.m_Result) os << i.End();
	return os;
}

void GreedyAlg::Scan(Orgraph::Edge edge) {

	for (auto i : m_Current)
		if (i.End() == edge.End()) 
			return;

	m_Current.push_back(edge);

	// если дошли до конца то проверка текущего пути
	if (m_Current[m_Current.size() - 1].End() == m_End) {
		// если текущий путь короче чем результат то его запоминаем
		if (m_Result.size() == 0 || Weight(m_Current) < Weight(m_Result))
			m_Result = m_Current;
		m_Current.pop_back();
		return;
	}
	// если длина пути стала больше чем лучший результат то ничего не делаем
	if (m_Result.size() > 0 && Weight(m_Current) >= Weight(m_Result)) {
		m_Current.pop_back();
		return;
	}

	for (auto i : m_Graph[edge.End()]) 
		Scan(i);	

	m_Current.pop_back();
}
float GreedyAlg::Weight(std::vector<Orgraph::Edge> path)
{
	float w = 0;
	for (auto i : path)
		w += i.W();
	return w;
}
