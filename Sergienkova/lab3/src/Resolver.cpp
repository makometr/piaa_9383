#include "Resolver.h"

std::ostream& operator<<(std::ostream& os, Resolver& r)
{
	os << r._MaxStream << std::endl;
	return os << r._Result;
}

void Resolver::Resolve(Graph& g, char in, char out)
{
	// принимаем данные
	_Graph = g;
	_In = in;
	_Out = out;

	// создаем копию исходного графа, но с 0 весами
	_Result.Reset(_Graph.EdgesCount());
	for (auto listI : _Graph) {
		for (auto edge : listI.second) {
			_Result.Set(Edge(edge.From(), edge.To(), 0));
		}
	}

	// сканируем все пути
	_Path.clear();
	Go(in);

	// поиск макс потока из истока в сток (сумма весов входящих ребер в сток из результата)
	_MaxStream = 0;
	for (auto listI : _Result) {
		for (auto edge : listI.second) {
			// пропуск ненужных ребер
			if (edge.To() != _Out) continue;
			// суммируем вес
			_MaxStream += edge.Weight();
		}
	}
}

void Resolver::Go(char point)
{
	// ограничитель
	if (Contains(_Path, point)) return;

	// добавляем элемент в путь
	_Path.push_back(point);

	// если дошли до конца
	if (point == _Out) {
		CheckPath();
	}
	else {
		for (auto e : _Graph[point]) Go(e.To());		
	}

	// удаляем элемент из пути
	_Path.pop_back();
}

bool Resolver::Contains(std::vector<char>& path, char point)
{
	for (auto i : path)
		if (i == point) return true;
	return false;
}
void Resolver::CheckPath()	// проверяет найденый путь (по алгоритму)
{
	// поиск мин пропускной способности на пути
	unsigned int minW = 0;
	for (int i = 1; i < _Path.size(); ++i) {
		auto& e = _Graph.Get(_Path[i - 1], _Path[i]);
		if (minW == 0 || e.Weight() < minW) minW = e.Weight();
	}

	// прибавляем этот мин ко всему на результирующем графе
	for (int i = 1; i < _Path.size(); ++i) {
		auto& e = _Result.Get(_Path[i - 1], _Path[i]);
		e.SetWeight(e.Weight() + minW);		
	}
}