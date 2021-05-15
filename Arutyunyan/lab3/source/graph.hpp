#pragma once

#include <vector>
#include <deque>
#include <functional>
#include <algorithm>


class Graph {
public:
    explicit Graph(size_t vertexes_amount) {
        incident_matrix.resize(vertexes_amount, std::vector<float>(vertexes_amount, -1));
    }

    void SetOffset(int offset_) {
        offset = offset_;
    }

    int GetOffset() const {
        return offset;
    }

    void AddEdge(char u, char v, float weight) {
        incident_matrix[u - offset][v - offset] = weight;
    }

    void ChangeWeight(char u, char v, float weight) {
        incident_matrix[u - offset][v - offset] = weight;
    }

    template <typename Func>
    std::deque<char> GetNeighbours(char u, Func predicate) const
    {
        std::deque<char> neighbours;
        for (char i = (offset == 97 ? 'a' : '1'); i <= (offset == 97 ? 'z' : '9'); ++i) {
            if (incident_matrix[u - offset][i - offset] > 0 && predicate(i))
                neighbours.push_back(i);
        }
        return neighbours;
    }

    std::deque<char> GetNeighbours(char u) const
    {
        std::deque<char> neighbours;
        for (char i = (offset == 97 ? 'a' : '1'); i <= (offset == 97 ? 'z' : '9'); ++i) {
            if (incident_matrix[u - offset][i - offset] > 0)
                neighbours.push_back(i);
        }
        return neighbours;
    }

    float GetEdgeWeight(char u, char v) const {
        return incident_matrix[u - offset][v - offset];
    }

    bool HasEdge(char u, char v) const {
        return incident_matrix[u - offset][v - offset] != -1;
    }

    size_t Size() const { return incident_matrix.size(); }

private:
    std::vector<std::vector<float>> incident_matrix;
    int offset = 97;
};