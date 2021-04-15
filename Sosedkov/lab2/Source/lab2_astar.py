import heapq

def heuristic(a, b):
	return abs(ord(b)-ord(a))

def a_star(graph, start, end):
	path_cost = {start:0}
	pqueue = []
	heapq.heappush(pqueue, (0, start))
	graph_map = {start: None}

	while len(pqueue):
		current = heapq.heappop(pqueue)[1]

		if current == end:
			break

		for node in graph[current]:
			cost = path_cost[current] + graph[current][node]
			if node not in path_cost or cost < path_cost[node]:
				path_cost[node] = cost
				priority = cost + heuristic(end, node)
				heapq.heappush(pqueue, (priority, node))
				graph_map[node] = current

	answer = end
	while graph_map[answer[0]]:
		answer = graph_map[answer[0]] + answer
	return answer



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
	print(a_star(graph, start, end))