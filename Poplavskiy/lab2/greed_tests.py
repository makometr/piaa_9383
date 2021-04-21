import unittest
from greed import *

class TestCaseGreed(unittest.TestCase):
	def test1(self):
		tree = Graph()
		tree.add_edge('a', 'b', 3.7)
		tree.add_edge('g', 'b', 2.5)
		self.assertEqual(tree.graph['a']['b'], 3.7)

	def test2(self):
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
		ans = tree.preparing(data[0][0], data[0][1])
		self.assertEqual(''.join(ans), "abcde")


	def test3(self):
		data = [['a', 'e'],
				['a', 'b', 4.2],
				['b', 'd', 3.0],
				['a', 'b', 3.4],
				['d', 'e', 1.0]]
		tree = Graph()
		for i in range(len(data)):
		    if i > 0:
		        tree.add_edge(data[i][0], data[i][1], float(data[i][2]))
		ans = tree.preparing(data[0][0], data[0][1])
		self.assertEqual(''.join(ans), "abde")


	def test4(self):
		data = [['a', 'f'],
				['a', 'b', 3.0],
				['b', 'd', 4.0],
				['c', 'f', 6.3],
				['a', 'c', 4.0]]
		tree = Graph()
		for i in range(len(data)):
		    if i > 0:
		        tree.add_edge(data[i][0], data[i][1], float(data[i][2]))
		ans = tree.preparing(data[0][0], data[0][1])
		self.assertEqual(''.join(ans), "acf")

if __name__ == '__main__':
    unittest.main() 
