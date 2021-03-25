import time

def check_box(width, height , box, ans):
    for y in range(height-box+1):
        x = 0
        while x < width-box+1:
            num = len(ans)
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
                    num -= 1
                if not num:
                    return [y, x, box]
            else:
                return [y, x, box]
            x += 1
    return False


def find_paving(width, height, curent_min, box, min, ans = list()):
    global ans_min
    global count
    if ans_min:
        if len(ans) > len(ans_min):
            return ans_min
    if len(ans) > curent_min:
        return ans_min
    fast = 0
    skip_box = 0

    for i in range(box - skip_box, 0+fast, -1):
        check = check_box(width, height, i, ans)
        if check:
            find_paving(width, height, curent_min, box, min + 1, ans + list([check]))
        elif i == 1:
            if ans_min:
                if len(ans) < len(ans_min):
                    ans_min = ans
                    return ans
                elif len(ans) == len(ans_min):
                    count += 1
                return ans_min
            else:
                ans_min = ans
        else:
            continue
    return [len(ans_min), count]


def start(width, height):
    if width < height:
        buf = height
        height = width
        width = buf

    curent_min = width * height
    rect = True

    if width == height:
        curent_min = 13
        rect = False

    if rect:
        box = height
    elif not width % 2:
        box = int(width / 2)
    elif not width % 3:
        box = int(width / 3 * 2)
    else:
        box = int(width / 2)+1

    if (width >= 2 and height >= 2) and (height <= 20 and width <= 20):
        return find_paving(width, height, curent_min, box, 0)
    else:
        print('2 <= width,height <= 20')


if __name__ == '__main__':
    width = int(input())
    height = int(input())
    ans_min = list()
    count = 1
    start(width, height)
    print(len(ans_min))
    print(count)



