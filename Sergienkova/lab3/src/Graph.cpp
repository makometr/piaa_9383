#include "Graph.h"
#include <algorithm>

std::istream& operator>>(std::istream& is, Graph& g) {
	// ввод всех ребер, засовывая их в нужные вектора
	Edge e;
	for(int i=0;i<g.m_EdgesCount;++i){
		is >> e;
		g._Data[e.From()].push_back(e);
	}

	// сортировка всех векторов
	for (auto i : g._Data) {
		std::sort(i.second.begin(), i.second.end());
		g._Data[i.first] = i.second;
	}

	// вывод результатов
	return is;
}
std::ostream& operator<<(std::ostream& os, Graph& g) {
	for (auto i : g._Data)
		for (auto j : i.second)
			os << j << std::endl;
	return os;	
}
std::vector<Edge> Graph::operator[](char node){ // возвращает сортированный по весам вектор ребер из указанной вершины
	return _Data[node];
}
void Graph::Set(Edge e)	// задает ребро
{
	// берем список исходящих ребер
	auto list = _Data[e.From()];
	// пытаемся заменить ребро (если ребро существует)
	for (int i = 0; i < list.size(); ++i) {
		// пропускаем ненужные ребра
		if (list[i].From() != e.From() || list[i].To() != e.To()) continue;
		// перезапись ребра
		list[i] = e;
		// завершаем алгоритм
		return;
	}
	// вставка ребра вконец (если ребра еще нет)
	list.push_back(e);
	_Data[e.From()] = list;
}
Edge& Graph::Get(char from, char to)	// возаращает ссылку на ребро
{
	auto& list = _Data[from];
	for (int i = 0; i < list.size(); ++i) {
		if (list[i].To() == to) return list[i];
	}
	throw "could not found edge";
}