import heapq


class PriorityQueue:
    def __init__(self):
        self.elements = []

    def empty(self):
        return len(self.elements) == 0

    def put(self, item, priority):
        heapq.heappush(self.elements, (priority, item))

    def get(self):
        return heapq.heappop(self.elements)[1]


def heuristic(a, b):
    return abs(ord(b)-ord(a))


def a_star_search(graph, start, goal):
    priority = PriorityQueue()
    priority.put(start, 0)
    cost = dict()
    cost[start] = 0.0
    came_from = dict()
    came_from[start] = None

    while priority:
        current = priority.get()
        if current == goal:
            break
        index = list_vertex.index(current)
        current_index = -1
        for i in graph[index]:
            current_index += 1
            if not i:
                continue
            new_cost = cost[current]+i
            if list_vertex[current_index] not in cost or new_cost < cost[list_vertex[current_index]]:
                cost[list_vertex[current_index]] = new_cost
                priority_next = new_cost + heuristic(list_vertex[current_index], goal)
                # heuristic(list_vertex[current_index], goal) main
                # list_heuristic[list_vertex[current_index]] task
                priority.put(list_vertex[current_index], priority_next)
                came_from[list_vertex[current_index]] = current
    return came_from


def create_list_vertex(list_vertex, graph):
    while True:
        try:
            add_way = input().split()
        except EOFError:
            break
        if not add_way:
            break
        add_way[2] = float(add_way[2])
        graph += [add_way]
        skip1 = 1
        skip2 = 1
        if list_vertex:
            for i in list_vertex:
                if add_way[0] == i:
                    skip1 = 0
                if add_way[1] == i:
                    skip2 = 0
            if skip1:
                list_vertex += add_way[0]
            if skip2:
                list_vertex += add_way[1]
        else:
            list_vertex += add_way[0]
            if add_way[0] != add_way[1]:
                list_vertex += add_way[1]
    list_vertex.sort()
    return list_vertex, graph


def create_matrix(matrix_graph, list_vertex, graph):
    for i in range(len(list_vertex)):
        add_matrix = list()
        for j in range(len(list_vertex)):
            add_matrix += [0]
        for g in graph:
            if g[0] == list_vertex[i]:
                add_matrix[list_vertex.index(g[1])] = g[2]
        matrix_graph += [add_matrix]
    return matrix_graph


def add_heuristic(list_vertex):
    list_heuristic = dict()
    for i in list_vertex:
        print('heuristic ', i, ':')
        list_heuristic[i] = abs(int(input()))
    return list_heuristic


if __name__ == '__main__':
    way = input().split(' ')
    graph = list()
    matrix_graph = list()
    list_vertex = list()

    vertex_and_graph = create_list_vertex(list_vertex, graph)
    list_vertex = vertex_and_graph[0]
    graph = vertex_and_graph[1]

    matrix_graph = create_matrix(matrix_graph, list_vertex, graph)

    index_exit = list_vertex.index(way[1])

    list_heuristic = add_heuristic(list_vertex)
    print(list_heuristic)

    ans = a_star_search(matrix_graph, way[0], way[1])

    add = way[1]
    string = add

    while add != way[0]:
        add = ans[add]
        string += add

    print(string[::-1])
