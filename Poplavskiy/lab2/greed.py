from sys import stdin
import numpy as np

class Graph:
    def __init__(self):
        self.graph = {}
        self.node_in_graph = []

    def add_edge(self, head, leave, value):
        if head not in self.graph:
            self.graph[head] = {}
        self.graph[head][leave] = value

    def print_graph(self):
        print(self.graph)

    def preparing(self, start, end):
        done = []
        check = False
        ans = []

        while not check:
            ans, done = self.greedy(start, end, done)
            if ans[-1] == end:
                check = True
        return ans

    def greedy(self, start, end, done):
        key = start
        ans = []
        while key in self.graph and any(self.graph[key]):
            ans.append(key)
            min = np.Inf
            next = None
            for i in self.graph[key]:
                if min > self.graph[key][i] and i not in done:
                    if i in self.graph:
                        next = i
                        min = self.graph[key][i]
                    elif i == end:
                        next = i
                        min = self.graph[key][i]
            key = next
            done.append(key)
            if key == end:
                ans.append(key)
                return ans, done
        return ans, done

    def get_graph(self):
        return self.graph


if __name__ == "__main__":
    a_lst = []
    for line in stdin:
        a_lst.append(line.split())
    tree = Graph()
    for i in range(len(a_lst)):
        if i > 0:
            tree.add_edge(a_lst[i][0], a_lst[i][1], float(a_lst[i][2]))
    ans = tree.preparing(a_lst[0][0], a_lst[0][1])
    for i in ans:
        print(i, end='')