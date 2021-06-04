#include "piaa4_1.hpp"

int main() {
	setlocale(LC_ALL, "Russian");
	std::string form;
	std::string line;
	getline(std::cin, form);
	getline(std::cin, line);
	std::vector <int> res = KMP(form, line);
	if (res.size() == 0) {
		std::cout << "-1";
	}
	for (size_t i = 0; i < res.size(); i++) {
		std::cout << res[i];
		if (i != res.size() - 1) {
			std::cout << ",";
		}
	}
	return 0;
}