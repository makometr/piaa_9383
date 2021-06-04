#include "piaa5_1.hpp"

int main() {
	setlocale(LC_ALL, "Russian");
	std::string text;
	int n;//количество шаблонов
	init_bohr();
	std::cout << "Введите текст:" << std::endl;
	std::cin >> text;
	std::cout << "Введите количество шаблонов:" << std::endl;
	std::cin >> n;
	std::cout << "Введите набор шаблонов:" << std::endl;
	for (int i = 0; i < n; i++) {
		std::string temp;//шаблон
		std::cin >> temp;
		add_string_to_bohr(temp);
	}
	system("pause");
	std::cout << "------------------------------------------------------------------------------" << std::endl;
	std::cout << "Индивидуализация:\nВычислим количество дуг из вершин." << std::endl;
	info();
	system("pause");
	std::cout << "------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << "Найдем шаблоны в тексте." << std::endl;
	find_all_pos(text);
	system("pause");
	return 0;
}