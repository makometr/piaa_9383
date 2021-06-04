
class AhoNode:

    def __init__(self):
        self.goto = {}
        self.out = []
        self.fail = None


def aho_create_forest(patterns):
    root = AhoNode()

    for path in patterns:
        node = root
        for symbol in path:
            node = node.goto.setdefault(symbol, AhoNode())
        node.out.append(path)
    return root


def aho_create_statemachine(patterns):
    root = aho_create_forest(patterns)
    queue = []
    for node in root.goto.values():
        queue.append(node)
        node.fail = root

    while len(queue) > 0:
        rnode = queue.pop(0)

        for key, unode in zip(rnode.goto.keys(), rnode.goto.values()):
            queue.append(unode)
            fnode = rnode.fail
            while fnode is not None and key not in fnode.goto:
                fnode = fnode.fail
            unode.fail = fnode.goto[key] if fnode else root
            unode.out += unode.fail.out
    return root


def aho_find_all(s, root):
    node = root
    ans = []
    for i in range(len(s)):
        while node is not None and s[i] not in node.goto:
            node = node.fail
        if node is None:
            node = root
            continue
        node = node.goto[s[i]]

        for pattern in node.out:
            if [i - len(pattern) + 2, patterns.index(pattern)+1] in ans:
                ans.append(check_index(ans, pattern, patterns, i))
            else:
                ans.append([i - len(pattern) + 2, patterns.index(pattern)+1])
    return ans


def check_index(ans, pattern, patterns, i):
    index = 0
    while [i - len(pattern) + 2, patterns[index:].index(pattern)+1+index] in ans:
        index += 1
    return [i - len(pattern) + 2, patterns[index:].index(pattern)+1+index]


def create_patterns(pattern, wild_card):
    patterns = list(filter(None, pattern.split(wild_card)))
    start_indices = []
    start_index = 0
    for p in patterns:
        tmp = pattern[start_index:]
        index = tmp.index(p)
        start_indices.append(index + (len(pattern)-len(tmp)))
        start_index = index + len(p) + (len(pattern)-len(tmp))
    return patterns, start_indices


def sort_col(i): 
    return (i[0]*10)+i[1]


s = input()
pattern = input()
joker = input()

patterns, start_indices = create_patterns(pattern, joker)
root = aho_create_statemachine(patterns)
ans = sorted(aho_find_all(s, root))


c = [0]*len(s)
for i in ans:
    index = i[0]-1 - start_indices[i[1]-1]
    if index >= 0 and index < len(c):
        c[index] += 1

for i in range(len(c)-len(pattern)+1):
    if c[i] == len(patterns):
        print(i+1)
