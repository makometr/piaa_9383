
def clear(from_a, to_b):
    if to_b and from_a:
        matrix_graph[list_vertex.index(from_a)][list_vertex.index(to_b)] = 0
    return matrix_graph


def greed_sort(current, prev, prev_ans, ans):
    global min_ans
    if len(ans) > len(list_vertex):
        return min_ans
    index = list_vertex.index(current)
    current_index = -1
    current_weight = 0
    if current == list_vertex[index_exit]:
        if min_ans:
            if len(ans) < len(min_ans):
                min_ans = ans
                return ansф
            else:
                return min_ans
        else:
            min_ans = ans
            return ans
    for i in range(len(matrix_graph[index])):
        if matrix_graph[index][i] == 0:
            continue
        elif current_weight == 0:
            current_index = i
            current_weight = matrix_graph[index][i]
        elif current_weight > matrix_graph[index][i]:
            current_index = i
            current_weight = matrix_graph[index][i]
    clear(prev, current)
    if current_index < 0:
        min = greed_sort(prev, prev, prev_ans, prev_ans)
    else:
        min = greed_sort(list_vertex[current_index], current, ans, ans + list_vertex[current_index])
    if not min:
        matrix_graph[index][current_index] = 0
        greed_sort(current, prev, prev_ans, ans)
    return min


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
    min_ans = str()
    print(greed_sort(way[0], 0, str(), str(way[0])))
