#include "AStar.h"
#include <queue>
#include <map>

std::ostream& operator<<(std::ostream& os, AStar r) {
	if (r.m_Result.size() == 0) os << "has no result!";
	for (auto i : r.m_Result) os << i.End();
	return os;
}
float AStar::Weight(std::vector<Orgraph::Edge> path)
{
	float w = 0;
	for (auto i : path)
		w += i.W();
	return w;
}
void AStar::Resolve(Orgraph g, char start, char end)
{
	m_Result.clear();
	std::priority_queue<AStar::QueueData, std::vector<AStar::QueueData>,

    std::less<AStar::QueueData> >queue;
	std::map<char, int> cost;
	std::map<char, char> cameFrom;

	// задаем значения
	m_Graph = g;
	m_Start = start;
	m_End = end;

	// пишем начальные данные
	queue.push(AStar::QueueData(m_Start, 0));
	cost[m_Start] = 0; // стоимость перехода в начальную точку 0
	cameFrom[m_Start] = 0; // вначале какбы переход фиктивный

	while (!queue.empty()) {
		// берем элемент с высшим приоритетом
		auto current = queue.top();
		queue.pop();
		if (current.Node == m_End) break;
		// переходим по всем соседним узлам
		for (auto edge : m_Graph[current.Node]) {
			auto newCost = cost[current.Node] + edge.W();
			// ограничитель, если переходить ненужно (по стоимости)
			if (cost.find(edge.End()) != cost.end() && // если стоимость есть 
				newCost >= cost[edge.End()]) // и эта стоимость меньше или равна новой
				continue;
			// совершаем переход
			cost[edge.End()] = newCost;
			cameFrom[edge.End()] = edge.Start();
			// вычисляем приоритет обработки вершины в которую перешли
			auto priority = newCost + Heuristic(edge.End());
			// добавляем эту вершину в очередь обработки с этим приоритетом
			queue.push(AStar::QueueData(edge.End(), priority));
		}
	}

	m_Result.clear();
	auto current = m_End;
	while (cameFrom.find(current) != cameFrom.end() && cameFrom[current]) {
		m_Result.push_front(Orgraph::Edge(cameFrom[current], current, cost[current]));
		current = cameFrom[current];
	}
	if(cameFrom[current]==0)m_Result.push_front(Orgraph::Edge(current, current, 0));
}

