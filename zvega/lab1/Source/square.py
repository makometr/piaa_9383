
def check_box(box, ans, skip):
    for y in range(height-box+1):
        x = 0
        while x < width-box+1:
            count = len(ans)
            if ans:
                for i in ans:
                    if i[0] <= y and i[1] <= x:
                        if i[1]+i[2]-1 >= x and i[0]+i[2]-1 >= y:
                            x += i[2] - 1
                            break
                    elif i[0] <= y and i[1] >= x:
                        if x+box-1 >= i[1] and i[0]+i[2]-1 >= y:
                            x += i[2] - 1
                            break
                    elif i[0] >= y and i[1] <= x:
                        if y+box-1 >= i[0] and i[1]+i[2]-1 >= x:
                            x += i[2] - 1
                            break
                    else:
                        if y + box - 1 >= i[0] and x+box-1 >= i[1]:
                            x += i[2] - 1
                            break
                    count -= 1
                if not count:
                    if skip:
                        skip -= 1
                        x += 1
                        continue
                    return [y, x, box]
            else:
                return [y, x, box]
            x += 1
    return False


def is_prime(N):
    return N in [7, 11, 13, 17, 19]


def find_ans(box, min, ans):
    global ans_min
    if ans_min:
        if len(ans) > len(ans_min):
            return ans_min
    if len(ans) > curent_min:
        return ans_min
    fast = 0
    skip = 0
    skip_box = 0

    if min == 0:
        fast = box - 1
    if is_prime(width):
        if min == 1:
            box -= 1
            fast = box-1
        elif min == 2:
            fast = box - 1
            skip = 1
        elif min == 3:
            box = 2
            fast = box-1
        elif min == 4:
            box = int(height / 3)
            if width < 17:
                fast = box - 1
            else:
                skip_box = 1
                fast = box-2
        elif min == 5:
            if width == 19:
                fast = box - 2
            else:
                skip_box = 1
                fast = box - 3

    for i in range(box - skip_box, 0+fast, -1):
        check = check_box(i, ans, skip)
        if check:
            find_ans(box, min + 1, ans + list([check]))
        elif i == 1:
            if ans_min:
                if len(ans) < len(ans_min):
                    ans_min = ans
                    return ans
                return ans_min
            else:
                ans_min = ans
        else:
            continue
    return ans_min


width = int(input())
height = width

if width < height:
    w = height
    height = width
    width = w
curent_min = width * height

rect = True

if width == height:
    curent_min = 13
    rect = False

if not height % 2:
    box = int(height / 2)
elif not height % 3:
    box = int(height / 3 * 2)
else:
    box = int(height / 2 + 1)

ans_min = list()
find_ans(box, 0, list())
print(len(ans_min))
for i in ans_min:
    print(i[0], i[1], i[2])