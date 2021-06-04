from Source.lab4_kmp import kmp
from Source.lab4_kmp import prefix_function

print("<kmp> tests: ")
with open('./Tests/kmp_tests.txt', 'r') as reader:
	lines = reader.readlines()
	test_number = 1
	for line in lines:
		substr, str, result = line.strip().split(' ')
		result = list(map(int, result.split(',')))
		if len(result) == 1 and result[0] == -1:
			result = []
		soulution = kmp(str,substr)

		if soulution == result:
			print("[OK] Test #{}. {}".format(test_number, line.strip()))
		else:
			print("[Failed] Test #{}. {}".format(test_number, line.strip()))
		test_number += 1



print("<prefix_function> tests: ")
with open('./Tests/prefix_tests.txt', 'r') as reader:
	lines = reader.readlines()
	test_number = 1
	for line in lines:
		str, result = line.strip().split(' ')
		result = list(map(int, result.split(',')))
		soulution = prefix_function(str)
		if soulution == result:
			print("[OK] Test #{}. {}".format(test_number, line.strip()))
		else:
			print("[Failed] Test #{}. {}".format(test_number, line.strip()))
		test_number += 1