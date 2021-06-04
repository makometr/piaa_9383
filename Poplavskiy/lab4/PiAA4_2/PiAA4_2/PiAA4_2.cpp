#include "piaa4_2.hpp"

int main() {
	setlocale(LC_ALL, "Russian");
	std::string a;
	std::string b;
	getline(std::cin, a);
	getline(std::cin, b);
	std::cout << CYCLE_KMP(a, b);
	return 0;
}