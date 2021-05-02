#include "lab3.h"


void Finding::Read() {   //считывание данных
    int n;
    std::cout << "Введите количество ориентированных ребер графа:\n";
    std::cin >> n;
    std::cout << "Введите исток и сток:\n";
    std::cin >> start >> end;
    char first, second;
    double weight;
    std::cout << "Введите ребра графа и их пропускную способность:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> first >> second >> weight;
        edges[first][second] = weight;
    }
}


void Finding::PrintEdges(const std::map<char, double>& e, const char& ver) { //вывод ребер, исходящих из одной вершины
    for (auto& el : e)
        std::cout << ver << '-' << el.first << ": " << el.second << '\n';
}


void Finding::PrintFront(const std::queue<char>& front) {  //вывод фронта
    std::queue<char> tmp = front;
    std::vector<char> arr;
    while (!tmp.empty()) {
        arr.push_back(tmp.front());
        tmp.pop();
    }
    for (auto& el : arr) 
        std::cout << el;
    std::cout << '\n';
}


void Finding::PrintCapacity(){  //вывод графов и их пропускной способности
    for (auto& a : capacity)
        for (auto& b : a.second)
            std::cout << a.first << ' ' << b.first << ' ' << b.second << '\n';
}


bool Finding::IsNewFront(const std::queue<char>& f, char v){ //проверка на новый фронт
    auto tmp = f;
    while (!tmp.empty()) {
        char cur = tmp.front();
        tmp.pop();
            if (cur == v)
                return true;
    }
    return false;
}


void Finding::FindPath() { //функция поиска пути в ширину
    char current = start;    // текущая вершина
    bool IsFound = false;   //конец поиска
    std::queue<char> frontier, NewFrontier; // непросмотренные вершины с пропускной способностью
    std::map<char, char> from;  // значение, откуда взята вершина (вершина, предыдущая вершина на пути)

    path.clear();
    visited.clear();

    std::cout << "\nПоиск пути:\n";
    visited.emplace(start);

    while (!IsFound) {  //пока путь не найден
        std::vector<std::pair<char, double>> CurPathes; //ребра текущей вершины
        std::cout << "\nТекущая вершина: " << current << '\n';
        if (edges.find(current) != edges.end()) { //получение ребер
            auto found = edges.find(current)->second;
            for (auto& el : found)
                CurPathes.push_back(std::make_pair(el.first, el.second));
            PrintEdges(found, current);
        }
        else {
            CurPathes = std::vector<std::pair<char, double>>();
            std::cout << "Нет ребер.\n";
        }

        auto iter_visited = visited.end();
        int n = (int)CurPathes.size();
        for (auto& vert : CurPathes) { //добавление всех непосещенных соседей к фронту
            std::cout << "Проверка пути: " << current << '-' << vert.first << '\n';
            //проверка, если не было посещено или если пропускная способность больше 0
            if ((vert.second > 0) && (visited.find(vert.first) == visited.end()) && 
                (!IsNewFront(NewFrontier, vert.first) || vert.second > edges[from[vert.first]][vert.first])) {
                std::cout << "Не было посещено ранее, пропускная способность больше 0 ==> добавление во фронт\n";
                if (!IsNewFront(NewFrontier, vert.first)) // добавление во фронт
                    NewFrontier.push(vert.first);
                from[vert.first] = current;
            }
            else
                std::cout << "Было посещено ранее или же вместимость равна 0.\n";
        }
        if (!IsFound) {
            if (frontier.empty() && !(NewFrontier.empty())) { //переход к следующему фронту, если старый закончился; он становится посещенным
                auto tmp = NewFrontier;
                while (!tmp.empty()) {
                    char v = tmp.front();
                    if (v == end) {//проверка, если путь найден
                        std::cout << "Путь найден. Текущая вершина конечная.\n";
                        IsFound = true;
                        break;
                    }
                    tmp.pop();
                    visited.emplace(v);
                }
                frontier = NewFrontier;
                while (!NewFrontier.empty())
                    NewFrontier.pop();
            }
            else if (frontier.empty() && NewFrontier.empty()) {
                std::cout << "Путей больше нет.\n";
                break;
            }
            std::cout << "Фронт:\n"; //получаем следующую вершину из фронта
            PrintFront(frontier);
            current = frontier.front();
            frontier.pop();
        }
    }
    if (IsFound) { //получение пути
        char get = end;
        while (get != start) {
            path.push_back(get);
            get = from[get];
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());

        std::cout << "Путь: ";
        for (auto& v : path)
            std::cout << v;
        std::cout << '\n';
    }
}


double Finding::AlgorithmFF() {  //алгоритм Форда-Фалкерсона
    std::cout << "\nАлгоритм Форда-Фалкерсона:\n";
    double flow = 0;  //максимальный поток

    for (auto& v1 : edges)  //пропускная способность обнуляется
        for (auto& v2 : v1.second)
            capacity[v1.first][v2.first] = 0;

    while (FindPath(), !path.empty()) { //если путь существует
        char first = start;
        char second;
        std::cout << "Пропускная способность пути:\n  "; //подсчет минимальной пропускной способности пути
        double MinCapacity = 1000;
        for (int i = 1; i < path.size(); i++) {
            second = path[i];
            double CurCapacity = edges[first][second];
            if (CurCapacity < MinCapacity)
                MinCapacity = CurCapacity;
            std::cout << first << "-(" << CurCapacity << ")-" << second << ' ';
            first = second;
        }
        std::cout << "\nМинимальная пропускная способность: " << MinCapacity << '\n';
        first = start;  //обновление графа
        for (int i = 1; i < path.size(); i++) {
            second = path[i];
            edges[first][second] -= MinCapacity;
            edges[second][first] += MinCapacity;
            first = second;
        }
        flow += MinCapacity; //обновление текущего максимального потока
        first = start; //обновление пропускной способности
        for (int i = 1; i < path.size(); i++) {
            second = path[i];
            if (capacity.find(first) != capacity.end() && capacity[first].find(second) != capacity[first].end())
                capacity[first][second] += MinCapacity;
            else
                capacity[second][first] -= MinCapacity;
            first = second;
        }
    }

    return flow;
}


int main() {
    setlocale(LC_ALL, "Russian");
    Finding f;
    f = Finding();
    f.Read();
    double res = f.AlgorithmFF();
    std::cout << "\n\n_Результат работы_:\n";
    std::cout << res << '\n';  //максимальный поток
    f.PrintCapacity();
    return 0;
}