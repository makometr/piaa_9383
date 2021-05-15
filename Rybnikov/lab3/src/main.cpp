#include <iostream>
#include <sstream>
#include "Orgraph.h"
#include "FF.h"


int main() {
	Orgraph g;
	//stringstream ss("7\na f\na b 7\na c 6\nb d 6\nc f 9\nd e 3\nd f 4\ne c 2");
	//istream& is = ss;
    std::istream& is = std::cin;

	// ввод данных
	int count;
	char in, out;
	is >> count;
	g.SetEdgesCount(count);
	is >> in >> out >> g;

	// вывод графа
	//cout << g << endl;

	// поиск решения
    FF go;
	go.Init(g, in, out);
    std::cout << "-------" << std::endl;
	// вывод результата
    std::cout << go << std::endl;

    return 0;
}
