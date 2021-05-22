#include "Resolver3.h"

std::ostream& operator<<(std::ostream& os, Resolver3 r)
{
	if (r._Result.empty()) return os << "resolver3 has no result!";
	for (auto i : r._Result) os << i;
	return os;
}

void Resolver3::Resolve(Graph& g, char start, char end1, char end2)
{
	// создаем ресолверы
	Resolver2 r1;
	Resolver2 r2;
	Resolver2 r3;

	// ищем пути до 2 концов
	r1.Resolve(g, start, end1);
	r2.Resolve(g, start, end2);

	// ищем путь между 2 концами
	r3.Resolve(g, end1, end2);

	// формируем результат
	int n = 0;
	for (auto i : r1.Result()) {
		if (n++ == 0) continue; // пропуск стартовой вершины
		_Result.push_back(i);
	}
	for (auto i : r2.Result()) _Result.push_back(i);	
	for (auto i : r3.Result()) _Result.push_back(i);
}
