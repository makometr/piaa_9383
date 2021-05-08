from sys import stdin
from collections import namedtuple
pair = namedtuple('pair', ['first', 'second'])

class Queue:
    def __init__(self):
        self.__data = []

    def __compare(self, a, b):
        if a.second == b.second:
            return a.first < b.first
        else:
            return a.second > b.second

    def top(self):
        return self.__data[-1]

    def push(self, el):
        self.__data.append(el)
        self.__sort()

    def __sort(self):
        for i in range(len(self.__data) - 1):
            for j in range(len(self.__data) - i - 1):
                if not self.__compare(self.__data[j], self.__data[j + 1]):
                    self.__data[j], self.__data[j + 1] = self.__data[j + 1], self.__data[j]

    def pop(self):
        self.__data.pop()

    def empty(self):
        return len(self.__data) == 0


class Graph:
    def __init__(self):
        self.graph = {}

    def add_edge(self, head, leave, value):
        if head not in self.graph:
            self.graph[head] = {}
        self.graph[head][leave] = value

    def print_graph(self):
        print(self.graph)

    def a_star(self, start, end):
        shortPath = {}
        queue = Queue()
        queue.push(pair(start, 0))
        vector = [start]
        shortPath[start] = (vector, 0)
        while not queue.empty():
            if queue.top().first == end:
                return shortPath[end][0]
            temp = queue.top()
            print("Верхний элемент очереди равен {}".format(queue.top()))
            print("Текущая вершина {}".format(temp[0]))
            queue.pop()
            if temp.first in self.graph:
                for i in list(self.graph[temp.first].keys()):
                    currentPathLength = shortPath[temp.first][1] + self.graph[temp.first][i]
                    if i not in shortPath or shortPath[i][1] > currentPathLength:
                        path = []
                        for j in shortPath[temp.first][0]:
                            path.append(j)
                        path.append(i)
                        shortPath[i] = (path, currentPathLength)
                        evristic = abs(ord(end) - ord(i))
                        queue.push(pair(i, evristic + shortPath[i][1]))
        return shortPath[end][0]


def priority_sort(tree, end):
    for node in tree.graph.items():
        temp_list = sorted(list(node[1]), key=lambda x: abs(ord(end) - ord(x[0])))
        edges = dict()
        for x in temp_list:
            edges[x] = node[1][x]
        tree.graph[node[0]] = edges
    return tree

if __name__ == '__main__':
    data = []
    for line in stdin:
        data.append(line.split())

    tree = Graph()
    for i in range(len(data)):
        if i > 0:
            tree.add_edge(data[i][0], data[i][1], float(data[i][2]))
    tree = priority_sort(tree, data[-1][1])

    ans = tree.a_star(data[0][0], data[0][1])
    for i in ans:
        print(i, end='')


data = []
for line in stdin:
    data.append(line.split())

tree = Graph()
for i in range(len(data)):
    if i > 0:
        tree.add_edge(data[i][0], data[i][1], float(data[i][2]))
tree = priority_sort(tree, data[-1][1])

ans = tree.a_star(data[0][0], data[0][1])
for i in ans:
    print(i, end='')