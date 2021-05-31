#include "lab5_2.h"

int main() {
	setlocale(LC_ALL, "Russian");
	std::string T, P;
	char joker;
	std::vector<std::pair<std::string, int>> patterns;
	std::vector<std::pair<int, int>> result;

	std::cout << "Введите текст, шаблон и символ джокера:\n";
	std::cin >> T;
	std::cin >> P;
	std::cin >> joker;
	Partitioning(P, joker, patterns);
	AhoCorasick(T, patterns, result, P.length());
	sort(result.begin(), result.end());

	std::cout << "\n_Результаты поиска_\n";
	std::cout << "Индекс вхождения шаблона в строку:\n";
	for (auto i : result) {
		std::cout << i.first << '\n';
	}

	return 0;
}