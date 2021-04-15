#include <iostream>
#include <sstream>
#include "Graph.h"
#include "Resolver.h"
#include "Resolver2.h"
#include "Resolver3.h"

int main() {
	// ввод данных
	Graph g;
	
	std::cin >> g;

	// вывод графа
	std::cout << g << std::endl;

	// производим решение
	//Resolver r;
	//Resolver2 r;
	//r.Resolve(g, g.Start(), g.End());

	Resolver3 r;
	r.Resolve(g, g.Start(), g.End(), 'c');

	// вывод результата
	std::cout << r << std::endl;


	return 0;
}
