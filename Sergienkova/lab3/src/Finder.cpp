#include "Finder.h"
#include <set>
#include <vector>

bool Finder::Find(Graph& g, char item) // ищет в указанном графе указанное значение
{
	std::cout << "Start finding " << item << "..." << std::endl;
	// создаем набор посещенных вершин
	std::set<char> visited;
	// создаем текущий путь
	std::vector<char> path;

	// запускаем цикл поиска в глубину
	while (true) {
		// берем первую попавшуюся вершину, которую не посещали и помещаем ее в начало пути
		bool findFirst = false;
		for (auto i : g) {
			for (auto e : i.second) {
				// пропускаем все посещенные вершины
				if (visited.find(e.To()) != visited.end()) continue;
				// вставка вершины в начало пути
				path.push_back(e.To());
				visited.insert(e.To());
				std::cout << e.To();
				// если посетили искомую то выводим результат
				if (e.To() == item) {
					std::cout << std::endl;
					return true;
				}
				// завершаем цикл
				findFirst = true;
				break;
			}
			if (findFirst) break;
		}
		// если в путь начинать не от куда то все перебрали
		//if (!findFirst) break;

		// из первой вершины посещаем все возможные
		while (path.size()) {
			// пытаемся посещать вершины, пока это возможно (пропростаем вглубину)
			auto hasVisit = false;
			auto edges = g[path[path.size() - 1]];
			for (auto i = edges.begin(); i != edges.end();) {
				// если вершину посещали то не переходим по ребру (пропускаем ребро)
				if (visited.find(i->To()) != visited.end()) {
					++i;
					continue;
				}
				// посещаем вершину
				path.push_back(i->To());
				visited.insert(i->To());
				std::cout << i->To();
				hasVisit = true;
				// если посетили искомую то выводим результат
				if (i->To() == item) {
					std::cout << std::endl;
					return true;
				}
				// получаем итератор для посещенной вершины
				edges = g[path[path.size() - 1]];
				i = edges.begin();
			}

			// откат назад
			path.pop_back();
			if (hasVisit)std::cout << std::endl;
		}
	}

	// говорим, что ничего не нашли
	return false;
}