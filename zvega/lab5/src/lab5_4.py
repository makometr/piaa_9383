
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
            ans.append([i - len(pattern) + 2, patterns.index(pattern)+1])
            node = root
            break
    return ans


def sort_col(i): 
    return (i[0]*10)+i[1]


s = input()
n = int(input())
patterns = []
while n > 0:
    patterns.append(input())
    n -= 1
root = aho_create_statemachine(patterns)
ans = aho_find_all(s, root)
ans.sort(key=sort_col)
for enter in ans:
    print(enter[0], enter[1])
