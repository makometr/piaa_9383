#include <iostream>
#include <sstream>
#include "Orgraph.h"
#include "GreedyAlg.h"
#include "AStar.h"
#include "Option.h"

int main() {
	Orgraph g;
	char end2;
	//std::stringstream ss("a e\n a b 3.0\nb c 1.0\nc d 1.0\na d 5.0\nd e 1.0");
    //std::stringstream ss("a e\n a b 3.0\nb c 1.0\na d 100\na g 40\ne c 40\nc d 1.0\na d 5.0\nd e 1.0 c");

	//ss >> g;
	//ss >> end2;
	std::cin >> g;
	std::cin >> end2;

    std::cout << g << std::endl;

	
	//GreedyAlg resolver;
	//resolver.Resolve(g, g.Start(), g.End());

    //AStar resolver;
	//resolver.Resolve(g, g.Start(), g.End());

	Option resolver;
	resolver.Resolve(g, g.Start(), g.End(), end2);

    std::cout << resolver << std::endl;
	

    return 0;
}
