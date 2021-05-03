#include "FF.h"

std::ostream& operator<<(std::ostream& os, FF& r)
{
	os << r.m_MaxStream << std::endl;
	return os << r.m_Res;
}
void FF::Init(Orgraph& g, char in, char out)
{
	// принимаем данные
	m_Graph = g;
	m_In = in;
	m_Out = out;
	// создаем копию графа с нулевыми ребрами
	m_Res.SetEdgesCount(g.EdgesCount());
	for (auto i : g) m_Res.Set(Orgraph::Edge(i.Start(), i.End(), 0));

	// поиск макс потоков по всей сети (по всему графу)
	Visit(Orgraph::Edge(0, in, 0));

	// поиск макс потока (те сумма весов входных ребер в выходной узел)
	m_MaxStream = 0;
	for (auto i : m_Res) {
		if (i.End() != out) continue;
		m_MaxStream += i.W();
	}
}


void FF::Visit(Orgraph::Edge e)
{
	if (m_Visited.find(e.End()) != m_Visited.end()) return;
	m_Visited.insert(e.End());
	m_Path.push_back(e);

	// если дошли до конечной вершины
	if (e.End() == m_Out) MyPath();
	else {
		// перебор всех исходящих вершин
		for (auto e : m_Graph[e.End()])
			Visit(e);		
	}

	m_Visited.erase(e.End());
	m_Path.pop_back();
}
void FF::MyPath() // производит анализ одного найденого пути
{
	// берем мин пропускную способность на текущем пути
	auto minW = GetMinW();
	// добавляем эту мин пропускную способность на все ребра результирующего графа, по которому идет путь
	for (auto e : m_Path) {
		// пропуск стартового перехода из пустоты
		if (e.Start() == 0) continue;
		// добавляем вес
		auto edge = m_Res.Get(e.Start(), e.End());
		edge.SetW(edge.W() + minW);
		m_Res.Set(edge);
	}
}
unsigned int FF::GetMinW()	// находит мин пропускную способность из текущего пути
{
	unsigned int min = 0;
	bool hasMin = false;
	for (auto e : m_Path) {
		// пропуск стартового перехода из пустоты
		if (e.Start() == 0) continue;
		// поиск
		if (!hasMin || e.W() < min) {
			min = e.W();
			hasMin = true;
		}
	}
	return min;
}
