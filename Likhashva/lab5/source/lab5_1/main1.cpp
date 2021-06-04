#include "lab5_1.h"

int main() {
	setlocale(LC_ALL, "Russian");
	std::string T;
	std::vector<std::pair<std::string, int>> patterns;
	std::vector<std::pair<int, int>> result;
	int n = 0;

	std::cout << "¬ведите текст и число n:\n";
	std::cin >> T;
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		std::cout << "¬ведите строки:\n";
		std::string s;
		std::cin >> s;
		patterns.push_back({ s, 0 });
	}
	AhoCorasick(T, patterns, result);
	sort(result.begin(), result.end());

	std::cout << "\n_–езультаты поиска_\n";
	std::cout << "»ндекс вхождени€ в строке и пор€дковый номер шаблона:\n";
	for (auto i : result) {
		std::cout << i.first;
		std::cout << ' ' << i.second << '\n';
	}
	return 0;
}