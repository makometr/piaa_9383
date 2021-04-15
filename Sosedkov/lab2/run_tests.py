from Source import lab2_astar
from Source import lab2_greedy


print("<a_star> tests: ")
with open('./Tests/a_star_tests.txt', 'r') as reader:
	lines = list(map(lambda x: x.strip(), reader.readlines()))
	index = 2

	number_of_tests = int(lines[0])

	for i in range(number_of_tests):
		graph = {}
		start, end = lines[index].split()
		number_of_edges = int(lines[index+1])

		for j in range(number_of_edges):
			v1, v2, weight = lines[index+2+j].split()
			weight = float(weight)
			if v1 in graph:
				graph[v1][v2] = float(weight)
			else:
				graph[v1] = {v2: float(weight)}
			if v2 not in graph:
				graph[v2] = {}	

		answer = lines[index+2+number_of_edges]
		soulution = lab2_astar.a_star(graph, start, end)
		if soulution == answer:
			print("[OK] Test #{}".format(i))
		else:
			print("[Failed] Test #{}".format(i))

		index += number_of_edges + 4




print("<greedy> tests: ")
with open('./Tests/greedy_tests.txt', 'r') as reader:
	lines = list(map(lambda x: x.strip(), reader.readlines()))
	index = 2

	number_of_tests = int(lines[0])

	for i in range(number_of_tests):
		graph = {}
		start, end = lines[index].split()
		number_of_edges = int(lines[index+1])

		for j in range(number_of_edges):
			v1, v2, weight = lines[index+2+j].split()
			weight = float(weight)
			if v1 in graph:
				graph[v1][v2] = float(weight)
			else:
				graph[v1] = {v2: float(weight)}
			if v2 not in graph:
				graph[v2] = {}	

		answer = lines[index+2+number_of_edges]
		soulution = lab2_greedy.greedy(graph, start, end)
		if soulution == answer:
			print("[OK] Test #{}".format(i))
		else:
			print("[Failed] Test #{}".format(i))

		index += number_of_edges + 4




print("<heuristic> tests: ")
with open('./Tests/heuristic_tests.txt', 'r') as reader:
	lines = list(map(lambda x: x.strip(), reader.readlines()))
	test_number = 1
	for line in lines:
		a, b, answer = line.split()
		soulution = lab2_astar.heuristic(a, b)

		if soulution == int(answer):
			print("[OK] Test #{}".format(test_number))
		else:
			print("[Failed] Test #{}".format(test_number))

		test_number += 1