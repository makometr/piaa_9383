import unittest
from Astar import *

class TestCaseAstar(unittest.TestCase):
	def test1(self):
		queue = Queue()
		queue.push((1, 3))
		self.assertEqual(queue.top(), (1, 3))

	def test2(self):
		queue = Queue()
		queue.push((4, 2))
		queue.push((4, 6))
		queue.push((6, 2))
		self.assertEqual(queue.empty(), 0)

	def test3(self):
		tree = Graph()
		tree.add_edge('a', 'z', 5.2)
		tree.add_edge('a', 'c', 52.4)
		tree.print_graph()
		priority_sort(tree, 'A')
		tree.print_graph()
		self.assertEqual(tree.graph['a'], {'c': 52.4 ,'z': 5.2})

	def test4(self):
		data = [['a', 'e'],
				['a', 'b', 3.0],
				['b', 'c', 1.0],
				['c', 'd', 1.0],
				['a', 'd', 5.0],
				['d', 'e', 1.0]]
		
		tree = Graph()
		for i in range(len(data)):
		    if i > 0:
		        tree.add_edge(data[i][0], data[i][1], float(data[i][2]))
		tree = priority_sort(tree, data[-1][1])
		ans = tree.a_star(data[0][0], data[0][1])
		self.assertEqual(''.join(ans), 'ade')


if __name__ == '__main__':
    unittest.main() 
