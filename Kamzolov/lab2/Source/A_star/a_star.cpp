#include "a_star.h"



int heuristic(char start, char finish) {
    return abs(start - finish);
}

std::string vecToString(std::vector<Node*>& vec) {
    std::string ans;
    std::string vertex;
    for (auto& node : vec) {
        vertex = node->vertex;
        ans += "vertex: " + vertex + ", "
            + "neighbours: [";
        for (auto& neighbour : node->neighbours) {
            vertex = neighbour.first->vertex;
            ans += vertex + ", ";
        }
        ans += " ]; \n";
    }
    return ans;
}

int customFind(std::vector<Node*>& graph, char vertex) {
    for (size_t i = 0; i < graph.size(); i++) {
        if (graph[i]->vertex == vertex) return i;
    }
    return -1;
}

void initGraph(std::vector<Node*>& graph, char start, char finish, std::istream& in) {
    char curVertex, neighbourVertex;
    float edgeLength;

    Node* startNode = nullptr;
    Node* endNode = nullptr;

    while (in >> curVertex >> neighbourVertex >> edgeLength) {
        if(!isalpha(curVertex) || !isalpha(neighbourVertex)) {
            continue;
        }
        if(edgeLength < 0) {
            continue;
        }

        int startIndex = customFind(graph, curVertex);
        int endIndex = customFind(graph, neighbourVertex);
        if (startIndex == -1) {
            if (curVertex == start)
                startNode = new Node(curVertex, heuristic(start, finish));
            else
                startNode = new Node(curVertex);
            graph.push_back(startNode);

            startIndex = graph.size() - 1;
        }
        else startNode = graph[startIndex];

        if (endIndex == -1) {
            if (neighbourVertex == start)
                endNode = new Node(neighbourVertex, heuristic(start, finish));
            else
                endNode = new Node(neighbourVertex);
            graph.push_back(endNode);
            //count++;
        }
        else endNode = graph[endIndex];
        graph[startIndex]->neighbours.push_back(std::make_pair(endNode, edgeLength));
    }
}

std::string algo(std::vector<Node*>& graph, char finish) {

    auto nodeComparator = [](
        const Node* lhs,
        const Node* rhs
    ) {
        if (lhs->priority > rhs->priority)
            return true;
        if (lhs->priority == rhs->priority && lhs->vertex < rhs->vertex)
            return true;
        return false;
    };

    std::make_heap(std::begin(graph), std::end(graph), nodeComparator);

    std::string answer;
    while(!graph.empty()) {
        //std::cout << vecToString(graph);
        Node* node = graph.front();
        if (node->vertex == finish)
        {
            while (node->prev) {
                answer += node->vertex;
                node = node->prev;
            }
            answer += node->vertex;
            break;
        }   
        for (auto& neighbour : node->neighbours) {
            float temp = node->priority - heuristic(node->vertex, finish) + neighbour.second;
            if (temp < neighbour.first->priority)
            {
                neighbour.first->priority = temp + heuristic(neighbour.first->vertex, finish);
                neighbour.first->prev = node;
            }
        }
        std::swap(graph[0], graph[graph.size() - 1]);
        graph.pop_back();
        std::make_heap(std::begin(graph), std::end(graph), nodeComparator);
    }
    reverse(answer.begin(), answer.end());
    if(answer.empty())
        answer = "No path.";
    return answer;
}



void freeMemory(std::vector<Node*>& vec) {
    for(auto node : vec) {
        delete node;
    }
}
