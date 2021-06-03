class Node:
    def __init__(self, link=None):
        self.children = {}
        self.suffix_link = link
        self.words = []


def create_tree(patterns):
    root = Node()
    for index, pattern in enumerate(patterns):
        node = root
        for c in pattern:
            node = node.children.setdefault(c, Node(root))
        node.words.append(index)
    return root


def create_links(tree):
    queue = [value for key, value in tree.children.items()]

    while queue:
        current_node = queue.pop(0)

        for key, value_node in current_node.children.items():
            queue.append(value_node)
            link_node = current_node.suffix_link

            while link_node is not None and key not in link_node.children:
                link_node = link_node.suffix_link

            value_node.suffix_link = link_node.children[key] if link_node else tree
            value_node.words +=  value_node.suffix_link.words

    return tree



def Aho_Corasick(string, patterns):
    tree_root = create_links(create_tree(patterns))
    answer = []
    node = tree_root
    for i in range(len(string)):
        while node is not None and string[i] not in node.children:
            node = node.suffix_link
        if node is None:
            node = tree_root
            continue
        node = node.children[string[i]]
        for pattern in node.words:   
            answer.append((i - len(patterns[pattern]) + 2, pattern+1))
    return answer


text = input()
n = int(input())
patterns = []
for i in range(n):
    patterns.append(input())

result = sorted(Aho_Corasick(text, patterns))
for i in result:
    print(i[0],i[1])