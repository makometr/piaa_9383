#include "FordFulkerson.h"

bool flowComparator(std::pair<char, Edge> first, std::pair<char, Edge> second) {
    return first.second.capacity > second.second.capacity;
}

bool charComparator(std::pair<char, Edge> first, std::pair<char, Edge> second) {
    return first.first < second.first;
}

void readGraph(
    std::map<char, std::vector<std::pair<char, Edge>>>& graph,
    int& size,
    char& start,
    char& finish,
    std::istream& in
) {
    in >> size;
    in >> start >> finish;
    char tempFrom, tempTo;
    int tempFlow;
    for(int i = 0; i < size; i++) {
        in >> tempFrom >> tempTo >> tempFlow;
        if(tempFlow < 0) {
            graph = {};
            return;
        }
        graph[tempFrom].push_back({tempTo, {tempFlow, 0, true}});
        graph[tempTo].push_back({tempFrom, {0, tempFlow, false}});
    }
}



int FordFulkerson::search(char curVertex){
    if (curVertex == finish) return true;
    visited[curVertex] = true;
    std::sort(graph[curVertex].begin(), graph[curVertex].end(), flowComparator);
    for(auto& neighbour : graph[curVertex]) {
        if(!visited[neighbour.first] && neighbour.second.capacity > 0) {
            parent[neighbour.first] = curVertex;
            if(search(neighbour.first)){
                neighbour.second.used = true;
                for(auto& rNeighbour : graph[neighbour.first]) {
                    if(rNeighbour.first != curVertex) continue;
                    if(rNeighbour.second.flow != neighbour.second.capacity) continue;
                    if(rNeighbour.second.capacity != neighbour.second.flow) continue;
                    rNeighbour.second.used = true;
                }
                return true;
            }
        }
    }
    return false;
}

void FordFulkerson::fordFulkersonAlgo(){
    while(search(start)) {
        int tempFlow = INT_MAX;
        for(char v = finish; v != start; v = parent[v]) {
            char u = parent[v];
            for(size_t i = 0; i < graph[u].size(); i++) {
                if(graph[u][i].first == v) {
                    if(!graph[u][i].second.used) continue;
                    tempFlow = std::min(tempFlow, graph[u][i].second.capacity);
                }
            }
        }

        for (char v = finish; v != start; v = parent[v]) {
            char u = parent[v];
            for(size_t i = 0; i < graph[u].size(); i++) {
                if(graph[u][i].first == v && graph[u][i].second.used) {
                    graph[u][i].second.capacity -= tempFlow;
                    graph[u][i].second.flow += tempFlow;
                    graph[u][i].second.used = false;
                }

            }
            for(size_t i = 0; i < graph[v].size(); i++) {
                if(graph[v][i].first == u && graph[u][i].second.used) {
                    graph[v][i].second.capacity += tempFlow;
                    graph[v][i].second.flow -= tempFlow;
                    graph[v][i].second.used = false;
                }
            }
        }
        visited = {};
        parent = {};
        maxFlow += tempFlow;
    }
}

void FordFulkerson::printAnswer() {
    std::cout << maxFlow;
    std::cout << '\n';
    for (auto& from : graph) {
        if(from.second.size() > 0) {
            std::sort(graph[from.first].begin(), graph[from.first].end(), charComparator);
            for (auto& to : from.second) {
                if(to.second.onStart)
                    std::cout << from.first << ' ' <<to.first << ' ' << to.second.flow << '\n';
            }
        }
    }
}
