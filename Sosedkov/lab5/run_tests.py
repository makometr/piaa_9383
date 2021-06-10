from Source.lab5_2 import Aho_Corasick
from Source.lab5_2 import cut_patterns_from_string
from Source.lab5_2 import max_num_edges_from_vertex


print("<Aho_Corasick> tests: ")
with open('./Tests/aho_tests.txt', 'r') as reader:
	lines = reader.readlines()
	test_number = 1
	for line in lines:
		text, patterns, res = line.strip().split(' ')
		patterns = patterns.split(',')
		res = list(map(int, res.split(',')))
		result = []
		for i in range(0, len(res), 2):
			result.append((res[i], res[i+1]))

		soulution = Aho_Corasick(text, patterns)

		if soulution == result:
			print("[OK] Test #{}. {}".format(test_number, line.strip()))
		else:
			print("[Failed] Test #{}. {}".format(test_number, line.strip()))
		test_number += 1

print("<cut_patterns_from_string> tests: ")
with open('./Tests/cut_tests.txt', 'r') as reader:
	lines = reader.readlines()
	test_number = 1
	for line in lines:
		text, seg, result = line.strip().split(' ')
		seg = list(map(int, seg.split(',')))

		segments = []
		for i in range(0, len(seg), 2):
			segments.append((seg[i], seg[i+1]))

		soulution = cut_patterns_from_string(text, segments)

		if soulution == result:
			print("[OK] Test #{}. {}".format(test_number, line.strip()))
		else:
			print("[Failed] Test #{}. {}".format(test_number, line.strip()))
		test_number += 1