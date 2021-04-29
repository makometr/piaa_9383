from Source import lab3
from Source import lab3_1


print("<max_flow> tests: ")
with open('./Tests/max_flow_tests', 'r') as reader:
	graph = {}
	lines = reader.readlines()
	current_index = 1
	number_of_tests = int(lines[0])

	for t in range(number_of_tests):
		start, end, count, answer = lines[current_index].strip().split()
		count = int(count)
		answer = int(answer)
		current_index += 1

		for i in range(count):
			v1, v2, weight = lines[current_index+i].split()
			if v1 in graph: 
				graph[v1][v2] = int(weight)
			else:
				graph[v1] = {v2: int(weight)}
			if v2 not in graph:
				graph[v2] = {}
		current_index += (count+1)

		flow, flow_graph = lab3.max_flow(graph, start, end)
		if flow == answer:
			print("[OK] Test #{}".format(t+1))
		else:
			print("[Failed] Test #{}".format(t+1))
	


print("<find_path> tests: ")
with open('./Tests/find_path_tests', 'r') as reader:
	graph = {}
	lines = reader.readlines()
	current_index = 1
	number_of_tests = int(lines[0])

	for t in range(number_of_tests):
		start, end, count, answer = lines[current_index].strip().split()
		count = int(count)
		current_index += 1

		for i in range(count):
			v1, v2, weight = lines[current_index+i].split()
			if v1 in graph: 
				graph[v1][v2] = int(weight)
			else:
				graph[v1] = {v2: int(weight)}
			if v2 not in graph:
				graph[v2] = {}
		current_index += (count+1)

		path, min_weight = lab3.find_path(graph, start, end)
		print(start+path, answer)
		if start+path == answer:
			print("[OK] Test #{}".format(t+1))
		else:
			print("[Failed] Test #{}".format(t+1))
