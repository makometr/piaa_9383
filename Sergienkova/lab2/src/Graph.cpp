#include "Graph.h"
#include <algorithm>

std::istream& operator>>(std::istream& is, Graph& g) {
	// ввод начала и конца
	is >> g._Start >> g._End;

	// ввод всех ребер, засовывая их в нужные вектора
	Edge e;
	do {
		is >> e;
		g._Data[e.From()].push_back(e);
	} while (e.To() != g._End);

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
char Graph::Start() {
	return _Start;
}
char Graph::End() {
	return _End;
}
std::vector<Edge> Graph::operator[](char node){ // возвращает сортированный по весам вектор ребер из указанной вершины
	return _Data[node];
}