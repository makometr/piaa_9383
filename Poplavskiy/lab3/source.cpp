#include "ford_falk.h"

int main() {
	setlocale(LC_ALL, "Russian");
	Ford_Falkerson ford(0, '\0');
	ford.creation_graph();
	std::cout << ford.alg_ff() << std::endl;
	ford.print_result();
	system("pause");
	return 0;
}