#include "piaa5_2.hpp"

int main() {
	setlocale(LC_ALL, "Russian");
	std::vector<std::string> patterns;  //подстроки при делении по джокеру
	std::vector<int> patterns_pos;		//позиции подстрок
	std::string text;					//текст
	std::string temp;					//шаблон
	char joker;							//джокер
	std::string pat;
	std::cout << "Введите текст:" << std::endl;
	std::cin >> text;
	std::cout << "Введите шаблон:" << std::endl;
	std::cin >> temp;
	std::cout << "Введите джокер:" << std::endl;
	std::cin >> joker;
	init_bohr();
	std::cout << std::endl << "Разделим шаблон на подстроки без джокера" << std::endl;
	for (int i = 0; i < temp.length(); i++) {
		if (temp[i] != joker) {
			patterns_pos.push_back(i + 1);
			for (int j = i; temp[j] != joker && j != temp.length(); j++) {
				pat += temp[j];
				i++;
			}
			add_string_to_bohr(pat);
			patterns.push_back(pat);
			pat.clear();
		}
	}
	system("pause");
	std::cout << "------------------------------------------------------------------------------" << std::endl;
	std::cout << "Индивидуализация:\nВычислим количество дуг из вершин." << std::endl;
	info();
	system("pause");
	std::cout << "------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << "Найдем шаблон в тексте." << std::endl;
	find_all_pos(text);
	int arr[10];
	int n = 0;
	std::vector<int> c(text.length(), 0);
	system("pause");
	std::cout << "------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << "Найдем шаблон с джокерами в тексте" << std::endl;
	for (int i = 0; i < num.size(); i++) {
		std::cout << std::endl << "Текущий подшаблон " << pattern[num[i].pattern_num] << " с индексом в тексте " << num[i].index + 1 << " и индексом в шаблоне " << patterns_pos[num[i].pattern_num] << std::endl;
		if (num[i].index < patterns_pos[num[i].pattern_num] - 1) {//если индекс подшаблона меньше позиции подшаблона в строке
			std::cout << "индекс подшаблона равен " << num[i].index + 1 << " и меньше позиции подшаблона в шаблоне " << patterns_pos[num[i].pattern_num] << std::endl;
			continue;
		}
		c[num[i].index - patterns_pos[num[i].pattern_num] + 1]++;//увеличиваем счетчик количества пропусков
		std::cout << std::endl << "Количество пропусков между шаблонами равно " << c[num[i].index - patterns_pos[num[i].pattern_num] + 1] << std::endl;
		std::cout << "Количество джокеров между шаблонами равно " << patterns.size() << std::endl << std::endl;
		if (c[num[i].index - patterns_pos[num[i].pattern_num] + 1] == patterns.size() && //если количество пропусков равно колличеству джокеров
			num[i].index - patterns_pos[num[i].pattern_num] + 1 <= text.length() - temp.length()) { //и есть место чтобы закончить шаблон
			std::cout << "Количество джокеров между шаблонами равно количеству пропусков. Найден исходный шаблон в тексте" << std::endl;
			std::cout << "На позиции " << num[i].index - patterns_pos[num[i].pattern_num] + 2 << std::endl;
			arr[n] = num[i].index - patterns_pos[num[i].pattern_num] + 2;
			n++;
		}
		
	}
	system("pause");
	std::cout << "------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << "Ответ:" << std::endl;
	for (int i = 0; i < n; i++) std::cout << arr[i] << std::endl;
	for (int i = n - 1; i >= 0; i--) {
		if (i != 0 && arr[i - 1] + temp.size() - 1 >= arr[i]) 
			text.erase(arr[i - 1] + temp.size() - 1, arr[i]-arr[i-1] );
		else 
			text.erase(arr[i] - 1, temp.size());
	}
	std::cout << "Строка после удаления найденных шаблонов: " << text << std::endl;
	return 0;
}