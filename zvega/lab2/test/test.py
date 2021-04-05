import a_star

print("test matrix")

with open('./Tests/tests_matrix.txt', 'r') as reader:
    lines = reader.readlines()
    test_number = 1
    for line in lines:
        args, outp = line.strip().split('-')
        args = args.split(';')
        args[0] = args[0].split(' ')
        args[1] = args[1].split(',')
        for i in range(len(args[1])):
            args[1][i] = args[1][i].split(' ')
            args[1][i][2] = float(args[1][i][2])

        outp = outp.split(' ')
        for i in range(len(outp)):
            outp[i] = float(outp[i])

        fail = 0
        if len(args[0])*len(args[0]) != len(outp):
            fail = 1
        else:
            soulution = a_star.create_matrix(list(), args[0], args[1])
        index = 0

        for i in soulution:
            if fail:
                break
            for j in i:
                if j != outp[index]:
                    fail = 1
                    break
                index += 1
            if fail:
                break
        if not fail:
            print("[OK] Test #{}. {}".format(test_number, line.strip()))
        else:
            print("[Failed] Test #{}. {}".format(test_number, line.strip()))

        test_number += 1

print("test a* algorithm")


with open('./Tests/tests_a_star.txt', 'r') as reader:
    lines = reader.readlines()
    test_number = 1
    for line in lines:
        fail = 0
        args, outp = line.strip().split('-')
        args = args.split(';')
        args[0] = args[0].split(' ')
        args[1] = args[1].split(',')
        args[2] = args[2].split(' ')
        for i in range(len(args[1])):
            args[1][i] = args[1][i].split(' ')
            if len(args[1][i]) != 3:
                fail = 1
                break
            if not args[1][i][0] in args[0]:
                fail = 1
                break
            if not args[1][i][1] in args[0]:
                fail = 1
                break
            if args[1][i][2] and args[1][i][2].isdigit():
                args[1][i][2] = float(args[1][i][2])
            else:
                fail = 1
                break
        if fail:
            print("[Failed] Test #{}. {}".format(test_number, line.strip()))
        else:
            matrix = a_star.create_matrix(list(), args[0], args[1])
            index = 0
            a_star.list_vertex = args[0]

            ans = a_star.a_star_search(matrix, args[2][0], args[2][1])
            add = args[2][1]
            string = add

            while add != args[2][0]:
                add = ans[add]
                string += add

            string = string[::-1]
            if string == outp:
                print("[OK] Test #{}. {}".format(test_number, line.strip()))
            else:
                print("[Failed] Test #{}. {}".format(test_number, line.strip()))
        test_number += 1
