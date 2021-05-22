#include "Resolver.h"

void Resolver::Resolve(Graph& g, char a, char b) {
	// очистка предыдущего результата
	_Result.clear();

	// создаем нулевой путь
	std::vector<Edge> path;

	// посещаем первую вершину
	Go(Edge(0, a, 0), g, path, b);
}

std::ostream& operator<<(std::ostream& os, Resolver r) {
	if (r._Result.size() == 0) os << "Has no result";
	for (auto i : r._Result) os << i.To();
	return os;
}
bool Resolver::Go(Edge edge, Graph& g, std::vector<Edge>& path, char end)		// посещает указанную вершину
{
	// если вес текущего пути больше чем лучший найденый то не посещаем вершину
	if (_Result.size() > 0 && Weight(path) > Weight(_Result)) return false;

	// добавляем ребро в путь
	path.push_back(edge);

	// если дошли до конца, то проверяем получившийся путь
	if (edge.To() == end) {
		if (_Result.size() == 0 || Weight(path) < Weight(_Result))
			_Result = path;
	}
	else { // в противном случае посещаем все остальные вершины
		// посещаем все вершины из этого пути
		for (auto i : g[edge.To()])
			if (!Go(i, g, path, end)) break;
	}

	// удаляем ребро из пути
	path.pop_back();

	// сообщает что посетили успешно
	return true;
}
double Resolver::Weight(std::vector<Edge>& path) {	// вес указанного пути 
	double weight = 0;
	for (auto i : path) weight += i.Weight();
	return weight;
}

