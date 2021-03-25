import rect_lab1

print("test start")

with open('./Tests/tests.txt', 'r') as reader:
    lines = reader.readlines()
    test_number = 1
    for line in lines:
        args, outp = line.strip().split('-')
        args = args.split(' ')
        args = int(args[0]), int(args[1])

        outp = outp.split(' ')
        outp = int(outp[1]), int(outp[2])

        rect_lab1.ans_min = list()
        rect_lab1.count = 1

        soulution = rect_lab1.start(args[0], args[1])
        if soulution[0] == outp[0] and soulution[1] == outp[1]:
            print("[OK] Test #{}. {}".format(test_number, line.strip()))
        else:
            print("[Failed] Test #{}. {}".format(test_number, line.strip()))

        test_number += 1

print("test find paving")

with open('./Tests/tests_paving.txt', 'r') as reader:
    lines = reader.readlines()
    test_number = 1
    for line in lines:
        args, outp = line.strip().split('-')
        args = args.split(' ')
        args = int(args[0]), int(args[1]), int(args[2]), int(args[3]), int(args[4])

        outp = outp.split(' ')
        outp = int(outp[1]), int(outp[2])

        rect_lab1.ans_min = list()
        rect_lab1.count = 1

        soulution = rect_lab1.find_paving(args[0], args[1], args[2], args[3], args[4])
        if soulution[0] == outp[0] and soulution[1] == outp[1]:
            print("[OK] Test #{}. {}".format(test_number, line.strip()))
        else:
            print("[Failed] Test #{}. {}".format(test_number, line.strip()))

        test_number += 1

print("test check box")

with open('./Tests/tests_check_box.txt', 'r') as reader:
    lines = reader.readlines()
    test_number = 1
    for line in lines:
        args, outp = line.strip().split('-')
        args = args.split(' ')
        ans = list()
        buf = list()
        skip = 4
        for i in args:
            if not i:
                continue
            if skip:
                skip -= 1
                continue
            if len(buf) == 3:
                ans += buf
                buf = list()
            buf.append(int(i))
        ans += [buf]
        args = int(args[0]), int(args[1]), int(args[2]), ans

        outp = outp.split(' ')
        outp = int(outp[1]), int(outp[2])

        rect_lab1.ans_min = list()
        rect_lab1.count = 1

        soulution = rect_lab1.check_box(args[0], args[1], args[2], args[3])
        if soulution:
            if soulution[0] == outp[0] and soulution[1] == outp[1]:
                print("[OK] Test #{}. {}".format(test_number, line.strip()))
            else:
                print("[Failed] Test #{}. {}".format(test_number, line.strip()))
        else:
            if outp[0] == 21 and outp[1] == 21:
                print("[OK] Test #{}. {}".format(test_number, line.strip()))
            else:
                print("[Failed] Test #{}. {}".format(test_number, line.strip()))
        test_number += 1