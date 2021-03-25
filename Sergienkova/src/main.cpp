#include <iostream>
#include "Resolver.h"

int main() {
	// ввод исходных данных
	Resolver resolver;
	int n = 40;
	std::cout << "N=";
	std::cin >> n;

	// расчет
	resolver.Resolve(n);

	// вывод результата
	std::cout << resolver << std::endl;

	system("PAUSE");
	return 0;
}