#pragma once

#include <vector>
#include <deque>
#include <functional>
#include <algorithm>

// Вы все верно поняли: я упоролся по шаблонам

template <typename T>
class Graph {
public:
    Graph(size_t vertexes_amount) {
        incident_matrix.resize(vertexes_amount, std::vector<float>(vertexes_amount, -1));
    }

    void AddEdge(T u, T v, float weight) {
        incident_matrix[OffsetValue(u)][OffsetValue(v)] = weight;
    }

    std::deque<T> GetNeighbours(T u, const std::function<bool(T)>& predicate 
                                                        = [](T c) { return true; }) const
    {
        std::deque<T> neighbours;
        auto range = Range(Size());
        for (T i = range.first; i < range.second; ++i) {
            if (incident_matrix[OffsetValue(u)][OffsetValue(i)] != -1 && predicate(OffsetValue(i)))
                neighbours.push_back(OffsetValue(i, false));
        }
        return neighbours;
    }

    float GetEdgeWeight(T u, T v) const {
        return incident_matrix[OffsetValue(u)][OffsetValue(v)];
    }

    bool HasEdge(T u, T v) const {
        return incident_matrix[OffsetValue(u)][OffsetValue(v)] != -1;
    }

    size_t Size() const { return incident_matrix.size(); }

    static T OffsetValue(T value_to_offset, bool reverse = true);
    static std::pair<T, T> Range(size_t graph_size);

private:
    std::vector<std::vector<float>> incident_matrix;
};


template <>
int Graph<int>::OffsetValue(int value_to_offset, bool reverse) {
    return value_to_offset;
}

template <>
char Graph<char>::OffsetValue(char value_to_offset, bool reverse) {
    return value_to_offset + (-1 * reverse) * 97;
}

template <>
std::pair<char, char> Graph<char>::Range(size_t graph_size) {
    return {'a', std::min('z' + 1, graph_size > 26 ? 'z' : static_cast<char>(graph_size + 97) + 1)};
}

template <>
std::pair<int, int> Graph<int>::Range(size_t graph_size) {
    return {0, graph_size};
}