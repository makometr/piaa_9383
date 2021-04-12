#include "greedy.h"


int findMinPath(std::vector<Graph>& graph, char start, int min_weight, std::vector<char> corr_path) {
    Graph min;
    for (int i = 0; i < graph.size(); i++) {
        if ((graph[i].start == start) && (graph[i].correct)){
            min = graph[i];
            min_weight = i;
            break;
        }
    }

    if (min.weight == -1){ 
        graph[min_weight].correct = false; 
        return -1;
    }

    for (int i = 0; i < graph.size(); i++) {
        if ((graph[i].weight < min.weight) && (graph[i].start == start) && (graph[i].correct)) {
            min = graph[i];
            min_weight = i;
        }
    }
    if (std::find(corr_path.begin(), corr_path.end(), graph[min_weight].end) != corr_path.end()) {
        graph[min_weight].correct = false;
        return -1;
    }
    return min_weight;
}

void Greedy(std::vector<Graph>& graph, char start, char end, std::vector<char>& corr_path)
{
    char current = start;
    int min_weight = 0;
    while (1) {
        corr_path.push_back(current);
        min_weight = findMinPath(graph, current, min_weight, corr_path);
        if (min_weight == -1) {
            min_weight = 0;
            current = start;
            corr_path.clear();
        }
        else {
            current = graph[min_weight].end;
        }

        if (graph[min_weight].end == end) break;
    }
    corr_path.push_back(end);
}

std::string getAnswer(std::vector<char> path){
    std::string answer;
    for (auto& a : path){
        answer += a;
    }
    return answer;
}