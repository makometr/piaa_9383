
def prefix(s):
    l = len(s)
    P = [0]*l
    i, j = 0, 1
    while j < l :
        if s[i] == s[j]:
            P[j] = i + 1
            i += 1
            j += 1
        elif i:
            i = P[i - 1]
        else:
            P[j] = 0
            j += 1
    return P


def kmp(sub, text):
    sub_len = len(sub)
    text_len = len(text)
    if not text_len or sub_len > text_len:
        return []
    P = prefix(sub)
    i = j = 0
    while i < text_len and j < sub_len:
        if text[i] == sub[j]:
            if j == sub_len - 1:
                return i - sub_len + 1
            else:
                j += 1
            i += 1
        elif j:
            j = P[j-1]
        else:
            i += 1
    return -1


if __name__ == '__main__':
    sub = input()
    s = input()
    if len(sub) != len(s):
        print(-1)
    else:
        print(kmp(s, sub*2))
