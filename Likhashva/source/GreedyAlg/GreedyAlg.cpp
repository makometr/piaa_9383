#include "GreedyAlg.h"


void FindingPath::Read() {
    cout << "Введите начальную и конечную вершины:\n";
    char start, end;   
    int count = 0;
    cin >> start >> end;
    this->start = start;
    this->end = end;
    cout << "Введите ребра графа и их вес:\n";
    while (cin >> start) {
        if (start == '0')  //символ остановки ввода данных
            break;
        double weight;
        cin >> end >> weight;
        graph[start].push_back({ end,weight });
        visited[start] = false;
        visited[end] = false;
        count++;
    }
    this->number = count;
}



vector<char> FindingPath::GreedyAlgorithm() {
    double min;
    vector<char> result;
    result.reserve(this->number);
    result.push_back(this->start);

    char CurVertex = this->start;

    while (CurVertex != this->end) {
        min = 100;
        char NextVertex;
        bool found = false;

        for (auto& i : this->graph[CurVertex]) {
            if (!visited[i.first] && i.second < min) {
                min = i.second;
                NextVertex = i.first;
                found = true;
            }
        }

        visited[CurVertex] = true;

        if (!found) {
            if (!result.empty()) {
                result.pop_back();
                CurVertex = result.back();
            }
            continue;
        }

        CurVertex = NextVertex;
        result.push_back(CurVertex);
    }

    return result;
}


int main() {
    setlocale(LC_ALL, "Russian");
    FindingPath answer;
    answer.Read();
    vector<char> out = answer.GreedyAlgorithm();
    cout << "\nРезультат работы жадного алгоритма:\n";
    for (auto& i : out) {
        cout << i;
    }
    cout << '\n';
    return 0;
}