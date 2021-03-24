from Source import lab1_rect_field
from Source.lab1_rect_field import Rect


print("<backtracking> tests: ")
with open('./Tests/tests.txt', 'r') as reader:
	lines = reader.readlines()
	test_number = 1
	for line in lines:
		args, outp = line.strip().split('-')
		args = args.split(' ')
		args = int(args[0]), int(args[1])
		
		outp = outp.split(' ')
		outp = int(outp[1]), int(outp[2])

		soulution = lab1_rect_field.backtracking(args[0], args[1])
		if len(soulution[0]) == outp[0] and soulution[1] == outp[1]:
			print("[OK] Test #{}. {}".format(test_number, line.strip()))
		else:
			print("[Failed] Test #{}. {}".format(test_number, line.strip()))

		test_number += 1





print("<create_square> tests: ")
with open('./Tests/create_square_tests.txt', 'r') as reader:
	lines = reader.readlines()
	test_number = 1
	for line in lines:
		args, outp = line.strip().split('-')
		args = args.split(' ')
		args = list(map(lambda x: int(x), args[0:len(args)-1]))

		outp = outp.split(' ')
		outp = list(map(lambda x: int(x), outp[1:len(outp)]))

		soulution = lab1_rect_field.create_square(Rect(args[0],args[1],args[2],args[3]), args[4])
		if soulution.x == outp[0] and soulution.y == outp[1] and soulution.width == outp[2] and soulution.height == outp[3]:
			print("[OK] Test #{}. {}".format(test_number, line.strip()))
		else:
			print("[Failed] Test #{}. {}".format(test_number, line.strip()))

		test_number += 1




print("<find_free_rect> tests: ")
with open('./Tests/find_free_rect_tests.txt', 'r') as reader:
	lines = reader.readlines()
	test_number = 1
	for line in lines:
		args, outp = line.strip().split('-')
		args = args.split(' ')
		args = list(map(lambda x: int(x), args[0:len(args)-1]))

		outp = outp.split(' ')
		outp = list(map(lambda x: int(x), outp[1:len(outp)]))

		number_of_squares = args[0]
		squares = []
		for i in range(number_of_squares):
			s = args[i*4+1:i*4+5]
			squares.append(Rect(s[0], s[1], s[2], s[3]))

		y_min = args[1+len(squares)*4+1:]

		soulution = lab1_rect_field.find_free_rect(squares, y_min)
		if soulution.x == outp[0] and soulution.y == outp[1] and soulution.width == outp[2] and soulution.height == outp[3]:
			print("[OK] Test #{}. {}".format(test_number, line.strip()))
		else:
			print("[Failed] Test #{}. {}".format(test_number, line.strip()))

		test_number += 1