#pragma once
#include <queue>
#include <vector>
#include <map>
#include "Graph.h"

// данные для приоритетной очереди
struct QueueData {
	char Point;
	int Weight;

	QueueData(char point, int weight) {
		this->Point = point;
		this->Weight = weight;
	}

	friend bool operator<(QueueData d1, QueueData d2);
	friend bool operator>(QueueData d1, QueueData d2);
};
// решает вторую задачу
class Resolver2
{
	std::priority_queue<QueueData, std::vector<QueueData>, std::less<QueueData> > _Queue; // очередь посещения вершин
	std::map<char, char> _CameFrom; // откуда пришли в каждую вершину
	std::map<char, int> _Cost;		// все известные стоимости вершин
	char _Start;	// откуда
	char _End;	// куда
	int Heuristic(char point) { return abs(_End - point); } // эвристическая функция
public:
	void Resolve(Graph& g, char a, char b);
	std::vector<char> Result(); // вектор результата

	friend std::ostream& operator<<(std::ostream& os, Resolver2 r);
};

