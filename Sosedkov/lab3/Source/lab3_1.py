import copy
import sys


def transpose_graph(graph):
    transposed_graph = dict.fromkeys(graph, {})
    for v in graph:
        for u in graph[v]:
            if not transposed_graph[u]:
                transposed_graph[u] = {v: graph[v][u]}
            else:
                transposed_graph[u][v] = graph[v][u]
    transposed_graph = dict(sorted(transposed_graph.items()))
    for i in transposed_graph:
        transposed_graph[i] = dict(sorted(transposed_graph[i].items(), reverse=True))
    return transposed_graph


def build_path(graph_map, graph_map2, vertex):
    min_weight = sys.maxsize
    first_path = vertex
    while graph_map[first_path[0]]:
        min_weight = min(min_weight, graph_map[first_path[0]][list(graph_map[first_path[0]].keys())[0]])
        first_path = list(graph_map[first_path[0]].keys())[0] + first_path

    second_path = vertex
    while graph_map2[second_path[-1]]:
        min_weight = min(min_weight, graph_map2[second_path[0]][list(graph_map2[second_path[0]].keys())[0]])
        second_path = second_path + list(graph_map2[second_path[-1]].keys())[0]

    first_path = first_path[:len(first_path)-1]
    return first_path+second_path, min_weight


def find_path(flow_graph, flow_graph_transposed, start, end):
    visited_start = [start]
    visited_end = [end]

    queue_start = [start]
    queue_end = [end]

    graph_map_start = dict.fromkeys(flow_graph, {})
    graph_map_end = dict.fromkeys(flow_graph, {})

    while len(queue_start) or len(queue_start):
        if len(queue_start):
            current = queue_start.pop()
            for vertex in flow_graph[current]:
                if vertex in visited_end and flow_graph[current][vertex] > 0: 
                    graph_map_start[vertex] = {current : flow_graph[current][vertex]}
                    return build_path(graph_map_start, graph_map_end, vertex)

                if vertex not in visited_start and flow_graph[current][vertex] > 0:
                    visited_start.append(vertex)
                    graph_map_start[vertex] = {current : flow_graph[current][vertex]}
                    queue_start.append(vertex)

        if len(queue_end):
            current = queue_end.pop()
            for vertex in flow_graph_transposed[current]:
                if vertex in visited_start and flow_graph_transposed[current][vertex] > 0:
                    graph_map_end[vertex] = {current : flow_graph_transposed[current][vertex]}
                    return build_path(graph_map_start, graph_map_end, vertex)
            
                if vertex not in visited_end and flow_graph_transposed[current][vertex] > 0:
                    visited_end.append(vertex)
                    graph_map_end[vertex] = {current : flow_graph_transposed[current][vertex]}
                    queue_end.append(vertex)

    return ('', 0)


def max_flow(original_graph, start, end):
    flow_graph = copy.deepcopy(original_graph)
    while True:
        path, min_weight = find_path(flow_graph, transpose_graph(flow_graph), start, end)
        if path:
            for u, v in zip((path)[:-1], (path)[1:]):
                flow_graph[u][v] -= min_weight
                if u not in flow_graph[v]:
                    flow_graph[v][u] = min_weight
                else:
                    flow_graph[v][u] += min_weight
        else:
            break

    return sum([original_graph[start][edge]-flow_graph[start][edge] for edge in flow_graph[start]]), flow_graph
    
    
if __name__ == '__main__':
    graph = {}
    number_of_edges = int(input())
    start = input()
    end = input()
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
        
    flow_value, flow_graph = max_flow(graph, start, end)
    print(flow_value)

    for v1 in graph:
        for v2 in graph[v1]:
            if graph[v1][v2] - flow_graph[v1][v2] > 0:
                print(v1, v2, graph[v1][v2] - flow_graph[v1][v2])
            else:
                print(v1, v2, 0)