import copy
import sys


def find_path(flow_graph, current, end, path='', visited=None, min_weight=sys.maxsize):
    if visited is None:
        visited = []
    if current == end:
        return (path, min_weight)
    visited.append(current)
    for vertex in flow_graph[current]:
        if vertex not in visited and flow_graph[current][vertex] > 0:
            new_path, new_min_weight = find_path(flow_graph, vertex, end, path+vertex, visited,
                                                 min(flow_graph[current][vertex], min_weight))
            if new_path:
                return (new_path, new_min_weight)
    return ('', min_weight)


def max_flow(graph, start, end):
    flow_graph = copy.deepcopy(graph)
    path, min_weight = find_path(flow_graph, start, end)
    while path:
        for u, v in zip((start+path)[:-1], (start+path)[1:]):
            flow_graph[u][v] -= min_weight
            if u not in flow_graph[v]:
                flow_graph[v][u] = min_weight
            else:
                flow_graph[v][u] += min_weight
        path, min_weight = find_path(flow_graph, start, end)
    return sum([graph[start][edge]-flow_graph[start][edge] for edge in flow_graph[start]]), flow_graph


def reed_graph(number_of_edges):
    graph = {}
    for i in range(number_of_edges):
        v1, v2, weight = input().split()
        if v1 in graph:
            graph[v1][v2] = int(weight)
        else:
            graph[v1] = {v2: int(weight)}
        if v2 not in graph:
            graph[v2] = {}

    graph = dict(sorted(graph.items()))
    for i in graph:
        graph[i] = dict(sorted(graph[i].items()))
    return graph


if __name__ == '__main__':
    number_of_edges = int(input())
    start = input()
    end = input()
    graph = reed_graph(number_of_edges)

    flow_value, flow_graph = max_flow(graph, start, end)
    print(flow_value)

    for v1 in graph:
        for v2 in graph[v1]:
            if graph[v1][v2] - flow_graph[v1][v2] > 0:
                print(v1, v2, graph[v1][v2] - flow_graph[v1][v2])
            else:
                print(v1, v2, 0)