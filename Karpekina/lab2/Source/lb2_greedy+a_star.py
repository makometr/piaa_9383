import networkx as nx
from pylab import show as graph_show

from operator import itemgetter
from math import inf
import sys


class Graph:
    def __init__(self):
        self.graph = {}

    def append_edge(self, vertex_out, vertex_in, weight):
        if vertex_out not in self.graph:
            self.graph[vertex_out] = {}
        self.graph[vertex_out][vertex_in] = weight

    def greedy(self, start_vertex, end_vertex):
        processed_vertex = []
        while True:
            el = start_vertex
            answer = []
            while el in self.graph and any(self.graph[el]):
                answer.append(el)
                min_size = inf
                next_vertex = None
                for vertex in self.graph[el]:
                    if self.graph[el][vertex] < min_size and vertex not in processed_vertex:
                        if vertex in self.graph or vertex == end_vertex:
                            next_vertex = vertex
                            min_size = self.graph[el][vertex]
                el = next_vertex
                processed_vertex.append(el)
                if el == end_vertex:
                    answer.append(el)
                if answer[-1] == end_vertex:
                    return answer

    def a_star(self, start_vertex, end_vertex):
        answer = {}
        vertex_queue = [(start_vertex, 0)]
        vertex_queue.sort(key=itemgetter(1), reverse=True)
        vec = [start_vertex]
        answer[start_vertex] = (vec, 0)
        while not vertex_queue == []:
            if vertex_queue[-1][0] == end_vertex:
                return answer[end_vertex][0]
            top_queue = vertex_queue[-1]
            vertex_queue.pop()
            if top_queue[0] in self.graph:
                for i in list(self.graph[top_queue[0]].keys()):
                    cur_size = self.graph[top_queue[0]][i] + answer[top_queue[0]][1]
                    if i not in answer or answer[i][1] > cur_size:
                        cur_path = []
                        for j in answer[top_queue[0]][0]:
                            cur_path.append(j)
                        cur_path.append(i)
                        answer[i] = (cur_path, cur_size)
                        vertex_queue.append((i, abs(ord(end_vertex) - ord(i)) + answer[i][1]))
                        vertex_queue.sort(key=itemgetter(1), reverse=True)
        return answer[end_vertex][0]

    def draw(self):
        g = nx.DiGraph()

        for i in self.graph:
            for j in self.graph[i]:
                g.add_edges_from([(i, j)], weight=self.graph[i][j])

        edge_labels = dict([((u, v,), d['weight'])
                            for u, v, d in g.edges(data=True)])
        pos = nx.spring_layout(g, scale=100, k=100)
        nx.draw_networkx_edge_labels(g, pos, edge_labels=edge_labels)
        nx.draw(g, pos, node_size=200, with_labels=True, node_color='g', edge_color='m')
        graph_show()


def read_list():
    for line in sys.stdin:
        line = line.rstrip()
        if line:
            yield line
        else:
            break


def fill_graph(empty_graph):
    input_list = list(read_list())
    for el in range(len(input_list)):
        input_list[el] = input_list[el].split(" ")
        if el > 0:
            empty_graph.append_edge(input_list[el][0], input_list[el][1], float(input_list[el][2]))

    start_node = input_list[0][0]
    end_node = input_list[0][1]
    return start_node, end_node


if __name__ == '__main__':

    graph = Graph()
    filled_graph = fill_graph(graph)
    path_greedy = graph.greedy(filled_graph[0], filled_graph[1])
    path_a_star = graph.a_star(filled_graph[0], filled_graph[1])

    print("\nGreedy: ", end='')
    for p in path_greedy:
        print(p, end='')

    print("\nA*: ", end='')
    for p in path_a_star:
        print(p, end='')

    graph.draw()
