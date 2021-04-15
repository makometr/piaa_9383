#include "Resolver2.h"
#include <list>

bool operator<(QueueData d1, QueueData d2) {
	return d1.Weight < d2.Weight;
}
bool operator>(QueueData d1, QueueData d2) {
	return d1.Weight > d2.Weight;
}

std::ostream& operator<<(std::ostream& os, Resolver2 r)
{
	auto res = r.Result();
	if (res.empty()) return os << "A* has no result!";
	for (auto i : res) os << i;
	return os;
}
void Resolver2::Resolve(Graph& g, char a, char b)
{
	// принимаем данные
	_Start = a;
	_End = b;
	// запуск расчетов
	_Queue.push(QueueData(_Start, 0));
	_CameFrom[_Start] = 0;
	_Cost[_Start] = 0;

	// цикл обхода
	while (!_Queue.empty()) {
		// берем наилучший вариант
		auto current = _Queue.top();
		_Queue.pop();
		// если этот вариант уже вконце то расчеты закончены
		if (current.Point == _End) break;
		// переходим из наилучшего варианта во все возможные новые смежные вершины
		for (auto e : g[current.Point]) {
			// расчет стоимости перехода в новую вершину
			auto newCost = _Cost[current.Point] + e.Weight(); 
			// если новая вершина содержится в списке переходов
			// и новая стоимость перехода больше или равна уже имеющейся стоимости
			// то пропускаем новый переход
			if (_Cost.count(e.To()) > 0 && _Cost[e.To()] >= newCost) continue;
			// производим переход в вершину
			_Cost[e.To()] = newCost; // пишем стоимость перехода
			_CameFrom[e.To()] = current.Point; // пишем откуда пришли
			// добавляем в приоритетную очередь новую вершину с приоритетом,
			// учитывающим эвристическую функцию
			_Queue.push(QueueData(e.To(), newCost + Heuristic(e.To())));
		}
	}

	/*_CameFrom[_End] = '4';
	_CameFrom['4'] = '3';
	_CameFrom['3'] = '2';
	_CameFrom['2'] = '1';
	_CameFrom['1'] = 0;*/
}

std::vector<char> Resolver2::Result() // вектор результата
{
	std::vector<char> vector;
	// ограничитель
	if (_CameFrom.count(_End) == 0) 
		return vector;

	// формируем список
	std::list<char> list;
	auto cur = _End;
	while (cur != 0) {
		list.push_front(cur);
		cur = _CameFrom[cur];
	}

	// конвертируем в вектор
	for (auto i : list) vector.push_back(i);

	// вывод результата
	return vector;
}