#include "AStar.h"


void FindingPath::Read() {
    std::cout << "Введите начальную и конечную вершины:\n";
    char start, end, elem;
    double heur;
    std::cin >> start >> end;
    this->start = start;
    this->end = end;
    std::cout << "Введите ребра графа и их вес:\n";
    while (std::cin >> start) {
        if (start == '0')  //символ остановки ввода данных
            break;
        double weight;
        std::cin >> end >> weight;
        graph[start].push_back({ end, weight });
        visited[start] = false;
        visited[end] = false;
    }
    std::cout << "Введите эвристические функции для вершин (<вершина> <эврист. функция>):\n";
    while (std::cin >> elem) {
        if (elem == '0')
            break;
        std::cin >> heur;
        if (heur > 0) 
            heuristic[elem] = heur;
        else {
            check = 1;
            break;
        }
    }
}


std::vector<char> FindingPath::AlgorithmAStar() {  //А*
    std::map<char, std::pair<std::vector<char>, double>> ShortPathes;  //текущие кратчайшие пути
    std::vector<char> vertex;
    std::priority_queue<std::pair<char, double>, std::vector<std::pair<char, double>>, decltype(Sorting)> PriorityQueue(Sorting); //очередь в алгоритме

    PriorityQueue.push({ start, 0 });
    vertex.push_back(start);
    ShortPathes[start].first = vertex;

    while (!PriorityQueue.empty()) {  //пока очередь не пуста
        if (PriorityQueue.top().first == end) {  //если найдена конечная вершина
            return ShortPathes[end].first;  //то заканчивается поиск
        }

        auto TmpVertex = PriorityQueue.top();  //достается приоритетная вершина из очереди
        PriorityQueue.pop();

        for (auto& i : graph[TmpVertex.first]) {  //рассматриваются все вершины, которые соединены с текущей вершиной
            double CurLength = ShortPathes[TmpVertex.first].second + i.second;
            if (ShortPathes[i.first].second == 0 || ShortPathes[i.first].second > CurLength) { //если пути нет или найденный путь короче
                std::vector<char> path = ShortPathes[TmpVertex.first].first;  //добавляется в путь родительской вершины текущая вершина с кратчайшим путем
                path.push_back(i.first);
                ShortPathes[i.first] = { path, CurLength };  //обновление пути и расстояния
                //double heuristic = abs(end - i.first);
                //cout << i.first << ' ' << heuristic[i.first] << '\n';
                PriorityQueue.push({ i.first, heuristic[i.first] + ShortPathes[i.first].second }); //записывается в очередь текущая вершина 
            }

        }

    }
    return ShortPathes[end].first;
}


int main() {
    setlocale(LC_ALL, "Russian");
    FindingPath answer;
    answer.Read();
    if (answer.check) {
        std::cout << "\nЭвристическая функция должна быть неотрицательной! Введите данные заново.\n";
        return 0;
    }
    std::vector<char> out = answer.AlgorithmAStar();
    std::cout << "\nРезультат работы алгоритма А*:\n";
    for (auto& i : out) {
        std::cout << i;
    }
    std::cout << '\n';
    return 0;
}