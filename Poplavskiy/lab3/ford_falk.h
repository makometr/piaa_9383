#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

#define COUNT 26

class Ford_Falkerson {
	int size;								//количество ориентированных ребер
	char source;							//исток
	char stock;								//сток
	char from;								//начальная вершина ребра
	char to;								//конечная вершина ребра
	int cost;								//величина потока ребра
	int delta = 0;							//для сортировки в лексикографическом порядке
	std::vector<std::vector<int>> graph;	//граф
	std::vector<std::vector<int>> flows;	//поток
	std::vector<bool>visited;				//посещенные
	std::vector<int> way;					//путь

public:
	Ford_Falkerson(int digit, char symbol) :size(digit), source(symbol), stock(symbol), from(symbol), to(symbol), cost(digit),
		delta(digit), graph(COUNT, std::vector<int>(COUNT, 0)), flows(COUNT, std::vector<int>(COUNT, 0)),
		visited(COUNT, false), way(COUNT, 0) {}

	void creation_graph() {//создание графа
		std::cin >> size >> source >> stock;
		if (isalpha(source)) {
			delta = 97;//ASCII код а
		}
		else {
			delta = 49;//ASCII код 1
		}
		for (int i = 0; i < size; i++)//считываем ребра графа
		{
			std::cin >> from >> to >> cost;
			graph[from - delta][to - delta] = cost;
		}
	}

	void clear() {//очищает путь
		for (size_t i = 0; i < COUNT; i++) {
			way[i] = 0;
		}
	}

	void DFS(int vertex) {//поиск в глубину
		visited[vertex - delta] = true;
		for (size_t i = 0; i < visited.size(); i++) {
			//перебираем все исходящие из рассматриваемой вершины рёбра
			if (!visited[i] && (graph[vertex - delta][i] - flows[vertex - delta][i] > 0 && graph[vertex - delta][i] != 0 || flows[vertex - delta][i] < 0 && graph[i][vertex - delta] != 0)) {
				//если ребро ведёт в вершину, которая не была рассмотрена ранее, то запускаем алгоритм от этой нерассмотренной вершины
				way[i] = vertex;
				DFS(i + delta);
			}
		}
	}

	bool get_way() {
		DFS(source);//поиск в глубину от истока
		for (size_t i = 0; i < visited.size(); i++) {
			visited[i] = false;//убираем просмотренные вершины
		}
		return (way[stock - delta] != 0);//дошел ли путь до стока
	}

	int alg_ff() {//алгоритм форда фалкерсона
		int max_flow = 0;
		while (get_way()) {
			int tmp = std::numeric_limits<int>::max();
			for (int v = stock - delta; 0 <= way[v] - delta; v = way[v] - delta) {
				tmp = std::min(tmp, graph[way[v] - delta][v] - flows[way[v] - delta][v]);//находим максимальный поток
			}
			for (int v = stock - delta; 0 <= way[v] - delta; v = way[v] - delta) {
				flows[way[v] - delta][v] += tmp;//увеличиваем поток для обратных путей
				flows[v][way[v] - delta] -= tmp;//убавляем поток для текущих путей
			}
			max_flow += tmp;
			clear();//очищаем путь
		}
		return max_flow;
	}

	void print_result() {//выводим рёбра графа с фактическим потоком
		for (int i = 0; i < COUNT; i++) {
			for (int j = 0; j < COUNT; j++) {
				if (flows[i][j] != 0 && flows[i][j] < 0) {
					flows[i][j] = 0;
				}
				if (graph[i][j] > 0) {
					std::cout << (char)(i + delta) << " " << (char)(j + delta) << " " << flows[i][j] << std::endl;
				}
			}
		}
	}
};