#include "API.h"

bool input(std::map<char, std::vector<std::pair<char, float>>>& graph, char& start, char& end, std::istream& stream) {
    stream >> start >> end;
    if (start < 'a' || start > 'z' || end < 'a' || end > 'z') {
        return false;
    }

    float weight = 0;
    for (char node1 = '\0', node2 = '\0'; stream >> node1 >> node2;) {
        if (!(stream >> weight) || node1 < 'a' || node1 > 'z' || node2 < 'a' || node2 > 'z') {
            return false;
        }
        graph[node1].push_back(std::make_pair(node2, weight));
    }

    if (!graph.count(start)) {
        return false;
    }

    std::string temp;
    return possible(graph, temp, start, start, end);
}

bool possible(std::map<char, std::vector<std::pair<char, float>>>& graph, std::string& current, char from, char link, char end) {
    if (link == end) {
        return true;
    }

    for (auto it = graph[link].begin(); it != graph[link].end(); ++it) {
        if (it->first == end) {
            return true;
        }
        else if (graph.count(it->first) && it->first != from && std::find(current.begin(), current.end(), link) == std::end(current)) {
            return possible(graph, current, link, it->first, end);
        }
    }
    return false;
}

std::string Greed::way(std::map<char, std::vector<std::pair<char, float>>>& graph, char start, char end) {
    std::string result;
    result += start;

    while (start != end) {
        for (auto it = graph[start].begin(); it != graph[start].end(); ++it) {
            if (possible(graph, result, start, it->first, end)) {
                start = it->first;
                break;
            }
        }
        result += start;
    }

    return result;
}

std::string Star::way(std::map<char, std::vector<std::pair<char, float>>>& graph, char start, char end) {
    std::unordered_map<char, char> came_from;
    std::unordered_map<char, float> cost_so_far;

    std::priority_queue<std::pair<char, double>, std::vector<std::pair<char, double>>, std::greater<std::pair<char, double>>> frontier;
    frontier.emplace(0, start);

    came_from[start] = start;
    cost_so_far[start] = 0;

    char current;
    while (!frontier.empty()) {
        current = frontier.top().second;
        frontier.pop();

        if (current == end) {
            break;
        }

        for (auto &next : graph[current]) {
            float new_cost = cost_so_far[current] + next.second;
            if (!cost_so_far.count(next.first) || new_cost < cost_so_far[next.first]) {
                cost_so_far[next.first] = new_cost;
                float priority = new_cost + heuristic(next.first, end);
                frontier.emplace(priority, next.first);
                came_from[next.first] = current;
            }
        }
    }

    std::vector<char> result;
    current = end;
    result.push_back(current);

    while (current != start) {
        current = came_from[current];
        result.push_back(current);
    }
    std::reverse(result.begin(), result.end());

    std::string path;
    for (int i = 0; i < result.size(); ++i) {
        path += result[i];
    }

    return path;
}

int Star::heuristic(char a, char b) {
    return std::abs(a - b);
}