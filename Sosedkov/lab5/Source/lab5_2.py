import sys

class Node:
    def __init__(self, link=None):
        self.children = {}
        self.suffix_link = link
        self.words = []

    def print(self, v='', offset=0):
        print(offset*'.',v)
        for i in self.children:
            self.children[i].print(i, offset+2)


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


def max_num_edges_from_vertex(tree):
    max_n = -1
    queue = [tree]
    while queue:
        current = queue.pop()
        if len(current.children.keys()) > max_n:
            max_n = len(current.children.keys())
        for i in current.children:
            queue.append(current.children[i])
    return max_n


def cut_patterns_from_string(string, segments):
    if segments:
        segment_without_intersections = []
        current_segment = segments[0]
        for index in range(len(segments)-1):
            first_segment = segments[index]
            second_segment = segments[index+1]
            if second_segment[0] > first_segment[1]:
                segment_without_intersections.append(current_segment)
                current_segment = (second_segment[0], second_segment[1])
            else:
                current_segment = (current_segment[0], max(first_segment[1], second_segment[1]))
        else:
            segment_without_intersections.append(current_segment)

        index = 0
        result_string = string

        for segment in segment_without_intersections:
            result_string = result_string[0:segment[0]-index] + result_string[segment[1]+1-index:] 
            index += segment[1] - segment[0] + 1
        return result_string
    else:
        return string

if __name__ == '__main__':
    text = input()
    n = int(input())
    patterns = []
    for i in range(n):
        patterns.append(input())


    segments = []
    result = sorted(Aho_Corasick(text, patterns))

    for i in result:
        segments.append((i[0]-1, i[0]-1+len(patterns[i[1]-1])-1))


    print('Maximum number of edges from one vertex:', max_num_edges_from_vertex(create_tree(patterns)))
    print('Before:', text)
    print('After:',cut_patterns_from_string(text, segments))  
