from Source import lab1_rect_field


with open('./Tests/tests.txt', 'r') as reader:
	lines = reader.readlines()
	test_number = 1
	for line in lines:
		args, outp = line.strip().split('-')
		args = args.split(' ')
		args = int(args[0]), int(args[1])
		
		outp = outp.split(' ')
		outp = int(outp[1]), int(outp[2])


		soulution = lab1_rect_field.solve(args[0], args[1])
		if len(soulution[0]) == outp[0] and soulution[1] == outp[1]:
			print("[OK] Test #{}. {}".format(test_number, line.strip()))
		else:
			print("[Failed] Test #{}. {}".format(test_number, line.strip()))

		test_number += 1
