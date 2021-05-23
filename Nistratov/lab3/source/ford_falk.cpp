#include "ford_falk.h"

bool FFsolver::isVisited(char node){
    for (auto name : visited){
        if (name == node){
            return true;
        }
    }
    return false; 
}

bool FFsolver::findPath(EDGE_MAP& cEdges){
    visited.push_back(start);
    cameFrom.push_back(start);
    char currNode = start;
    for (;;){
        if (currNode == finish){
            return true;
        }
        currNode = findMaxFlow(cEdges[currNode]);
        if (currNode == ' '){
            if (cameFrom.empty()){
                return false;
            }
            cameFrom.pop_back();
            currNode = cameFrom.back();
        }
        else{
            cameFrom.push_back(currNode);
            visited.push_back(currNode);
        }
    }
}

char FFsolver::findMaxFlow(std::map<char, int> node){
    char nodeName = ' ';
    int tempFlow = 0;
    if (node.empty()){
        return nodeName;
    }
    for (auto a : node){
        if (a.second > tempFlow && !isVisited(a.first)){
            nodeName = a.first;
            tempFlow = a.second;
        }
    }
    return nodeName;   
}

std::pair<int, EDGE_MAP> FFsolver::FordFulkerson(){
    EDGE_MAP cEdges = edges;
    EDGE_MAP dEdges = edges;
    int max_flow = 0;
    int tmp = __INT_MAX__;
    while (findPath(cEdges)){
        for (int i = 0; i < cameFrom.size() - 1; i++){
            tmp = std::min(tmp, cEdges[cameFrom[i]][cameFrom[i+1]]);
        }
        max_flow += tmp;
        for (int i = 0; i < cameFrom.size() - 1; i++){
            cEdges[cameFrom[i]][cameFrom[i+1]] -= tmp;
            cEdges[cameFrom[i+1]][cameFrom[i]] += tmp;              
        }
        visited.clear();
        cameFrom.clear();            
    }
    for (auto& kv1 : edges){
        for (auto& kv2 : kv1.second){
            kv2.second -= cEdges[kv1.first][kv2.first];
            if (kv2.second < 0){
                kv2.second = 0;
            }
        }
    }
    return std::make_pair(max_flow, edges);   
}

void FFsolver::print_edges(EDGE_MAP cEdges){
    for (auto& kv1 : cEdges){
        for (auto& kv2 : kv1.second){
            std::cout << kv1.first << " " << kv2.first << " " << kv2.second << std::endl;
        }
    }     
}

void FFsolver::input(){
    int n;
    std::cin >> n >> start >> finish;
    char node1, node2;
    int weight;
    for (int i = 0; i < n; i++){
        std::cin >> node1 >> node2 >> weight;
        edges[node1][node2] = weight;
    }            
}

void FFsolver::setInput(std::stringstream& ss){
    int n;
    ss >> n >> start >> finish;
    char node1, node2;
    int weight;
    for (int i = 0; i < n; i++){
        ss >> node1 >> node2 >> weight;
        edges[node1][node2] = weight;
    }  
}