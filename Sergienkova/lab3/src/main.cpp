#include <iostream>
#include <sstream>
#include "Graph.h"
#include "Resolver.h"
#include "Finder.h"

int main() {
	// ввод данных
	Graph g;
	//std::stringstream ss("7\na\nf\na b 7\na c 6\nb d 6\nc f 9\nd e 3\nd f 4\ne c 2");
	std::istream& is = std::cin;
	//std::istream& is = ss;

	// ввод данных
	int count;
	is >> count;
	g.Reset(count);
	char in, out;
	is >> in >> out;
	is >> g;

	// вывод графа
	std::cout << g << std::endl;

	// производим решение
    Resolver r;
	r.Resolve(g, in, out);
	// вывод результата
	std::cout << r << std::endl;

	// производим поиск в глубину
	//Finder f;
	//std::cout << "Find result: " << f.Find(g, 'e') << std::endl;

	
	return 0;
}
