import heapq

def greedy(graph, start, end):
	queue = [start]
	visited = set()

	while len(queue):
		current = queue.pop()
		if current[-1] == end:
			return current

		for node in graph[current[-1]]:
			if current[-1]+node not in visited:
				queue.append(current)
				queue.append(current+node)
				visited.add(current[-1]+node)
				break


def read_graph():
	graph = {}
	while True:
		try:
			input_string = input()
		except EOFError:
			break
		if not input_string:
			break
		start_vertex, end_vertex, weight = input_string.split(' ')

		if start_vertex in graph:
			graph[start_vertex][end_vertex] = float(weight)
		else:
			graph[start_vertex] = {end_vertex: float(weight)}
		
		if end_vertex not in graph:
			graph[end_vertex] = {}	

	for i in graph:
		graph[i] = dict(sorted(graph[i].items(), key=lambda x: x[1], reverse=False))
	return graph


if __name__ == '__main__':
	start, end = input().split(' ')
	graph = read_graph()
	print(greedy(graph, start, end))