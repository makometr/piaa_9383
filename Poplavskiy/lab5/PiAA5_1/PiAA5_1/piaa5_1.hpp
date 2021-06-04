#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#define ALP 6

struct bohr_vertex {				//структура вершины бора
	int next_vertex[ALP];			//массив вершин, в которые можно попасть из данной
	int path_num;					//номер шаблона
	bool flag;						//финальная вершина для шаблона
	int suff_link;					//переменная для хранения суффиксной ссылки
	int auto_move[ALP];				//массив переходов из одного состояния в другое
	int par;						//номер вершины родителя
	char symbol;					//символ по которому осуществляется переход от родителя
	int suff_flink;					//сжатые суффиксные ссылки
};

std::vector <bohr_vertex> bohr;		//бор
std::vector <std::string> pattern;	//шаблоны

bohr_vertex make_bohr_vertex(int par, char symbol) {//создание вершины бора
	bohr_vertex vertex;
	memset(vertex.next_vertex, 255, sizeof(vertex.next_vertex));
	vertex.flag = false;
	vertex.suff_link = -1;
	memset(vertex.auto_move, 255, sizeof(vertex.auto_move));
	vertex.par = par;
	vertex.symbol = symbol;
	vertex.suff_flink = -1;
	return vertex;
}

void init_bohr() {//создает пустой бор
	bohr.push_back(make_bohr_vertex(-1, -1));
}

int find(char symbol) {//алфавит
	int ch;
	switch (symbol)
	{
	case 'A':
		ch = 0;
		break;
	case 'C':
		ch = 1;
		break;
	case 'G':
		ch = 2;
		break;
	case 'T':
		ch = 3;
		break;
	case 'N':
		ch = 4;
		break;
	default:
		break;
	}
	return ch;
}

char vertex(char v) {//для вывода на консоль
	char ch;
	switch (v)
	{
	case 0:
		ch = 'A';
		break;
	case 1:
		ch = 'C';
		break;
	case 2:
		ch = 'G';
		break;
	case 3:
		ch = 'T';
		break;
	case 4:
		ch = 'N';
		break;
	default:
		ch = '0';
		break;
	}
	return ch;
}

void info() {
	int count[20];
	int max = 0;
	for (int i = 0; i < bohr.size(); i++) {
		count[i] = 0;
		std::cout << std::endl << "Вершина номер " << i << std::endl;
		if (i == 0) std::cout << "Это корень бора" << std::endl;
		else std::cout << "Вершина-родитель с номером " << bohr[i].par << " по символу " << vertex(bohr[i].symbol) << std::endl;
		std::cout << "Соседние вершины:" << std::endl;
		for (int j = 0; j < ALP; j++) {
			if (bohr[i].next_vertex[j] != -1) {
				std::cout << "Вершина " << bohr[i].next_vertex[j] << " по символу " << vertex(bohr[bohr[i].next_vertex[j]].symbol) << std::endl;
				count[i]++;
			}
		}
		if (count[i] == 0) std::cout << "Это финальная вершина." << std::endl;
		std::cout << "Суффиксная ссылка: ";
		if (bohr[i].suff_link == -1) std::cout << "еще не посчитана." << std::endl;
		else std::cout << vertex(bohr[i].suff_link) << std::endl;
	}
	for (int i = 0; i < bohr.size(); i++)
		if (count[i] > max) max = count[i];
	std::cout << std::endl << "Максимальное количество дуг, исходящих из одной вершины " << max << std::endl;
}

void add_string_to_bohr(std::string s) {//вставляет строку в бор
	std::cout << std::endl << "Добавляем шаблон \"" << s << "\" в бор." << std::endl;
	int num = 0;
	for (int i = 0; i < s.length(); i++) {//проходится по строке
		char ch = find(s[i]);//находит номер символа
		if (bohr[num].next_vertex[ch] == -1) {//добавляется новая вершина если её не было
			bohr.push_back(make_bohr_vertex(num, ch));
			bohr[num].next_vertex[ch] = bohr.size() - 1;
			std::cout << "Добавим новую вершину " << bohr[num].next_vertex[ch] << " по символу " << s[i] << std::endl;
		}
		else std::cout << "Вершина по символу " << s[i] << " уже есть в боре" << std::endl;
		std::cout << "Перейдем к вершине " << bohr[num].next_vertex[ch] << std::endl;
		num = bohr[num].next_vertex[ch];//переходим к следующей вершине
	}
	std::cout << "Финальная вершина шаблона." << std::endl << std::endl;
	bohr[num].flag = true;
	pattern.push_back(s);
	bohr[num].path_num = pattern.size() - 1;
}

int get_auto_move(int v, char ch);

int get_suff_link(int v) {//реализует получение суффиксной ссылки для данной вершины
	std::cout << std::endl << "Найдем суффиксную ссылку для вершины " << v << std::endl;
	if (bohr[v].suff_link == -1) {
		if (v == 0 || bohr[v].par == 0) {//если это корень или начало шаблона
			if (v == 0) std::cout << "Текущая вершина - корень бора. Суффиксная ссылка равна 0." << std::endl;
			else std::cout << "Текущая вершина - начало шаблона. Суффиксная ссылка равна 0." << std::endl;
			bohr[v].suff_link = 0;
		}
		else {
			std::cout << "Пройдем по суффиксной ссылке предка " << bohr[v].par << " и запустим переход по символу " << vertex(bohr[v].symbol) << std::endl;
			bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symbol);  //пройдем по суф.ссылке предка и запустим переход по символу.
			std::cout << "Значит суффиксная ссылка для вершины " << v << " равна " << bohr[v].suff_link << std::endl << std::endl;
		}
	}
	else std::cout << "Суффиксная ссылка для вершины " << v << " равна " << bohr[v].suff_link << std::endl << std::endl;
	return bohr[v].suff_link;
}

int get_auto_move(int v, char ch) {//вычисляемая функция переходов
	if (bohr[v].auto_move[ch] == -1) {
		if (bohr[v].next_vertex[ch] != -1) {//если из текущей вершины есть ребро с символом ch
			std::cout << "Из вершины " << v << " есть ребро с символом " << vertex(ch) << std::endl;
			std::cout << "Переходим по этому ребру в вершину " << bohr[v].next_vertex[ch] << std::endl;
			bohr[v].auto_move[ch] = bohr[v].next_vertex[ch];    //то идем по нему
		}
		else {//если нет
			if (v == 0) {//если это корень бора
				bohr[v].auto_move[ch] = 0;
			}
			else {
				std::cout << "Перейдем по суффиксной ссылке." << std::endl << std::endl;
				bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);  //иначе перейдем по суффиксальной ссылке
			}
		}
	}
	return bohr[v].auto_move[ch];
}

int get_suff_flink(int v) {//функция вычисления сжатых суффиксальных ссылок
	if (bohr[v].suff_flink == -1) {
		int u = get_suff_link(v);
		if (u == 0) {//если корень или начало шаблона
			bohr[v].suff_flink = 0;
		}
		else {//если по суффиксальной ссылке конечная вершина-равен суффиксальной ссылке, если нет-рекурсия.
			bohr[v].suff_flink = (bohr[u].flag) ? u : get_suff_flink(u);
		}
	}
	return bohr[v].suff_flink;
}

void check(int v, int i) {
	for (int u = v; u != 0; u = get_suff_flink(u)) {
		if (bohr[u].flag) {
			std::cout << std::endl << "Вершина " << u << " конечная для шаблона " << bohr[u].path_num + 1 << std::endl;
			std::cout << std::endl << "Найден шаблон с номером " << bohr[u].path_num + 1 << ", позиция в тексте " << i - pattern[bohr[u].path_num].length() + 1 << std::endl;
		}
		else std::cout << std::endl << "Вершина " << u << " не конечная" << std::endl;
	}
}

std::vector<std::pair<int, int>> answer;

int cmp(std::pair<int, int> a, std::pair<int, int>  b) {
	if (a.first == b.first)
		return a.second < b.second;
	else
		return a.first < b.first;
}

std::vector<std::pair<int, int>> find_all_pos(std::string s) {//поиск шаблонов в строке
	int u = 0;//текущая вершина
	for (int i = 0; i < s.length(); i++) {
		std::cout << std::endl << "Символ текста " << s[i] << " с индексом " << i + 1 << std::endl;
		std::cout << std::endl << "Текущая вершина " << u << std::endl << "Вычислим функцию переходов." << std::endl << std::endl;
		u = get_auto_move(u, find(s[i]));
		if (u != 0) std::cout << "Переход к вершине " << u << " по символу " << vertex(bohr[u].symbol) << std::endl;
		else std::cout << "Из вершины " << u << " нет ребра с символом " << s[i] << std::endl;
		for (int v = u; v != 0; v = get_suff_flink(v)) {
			if (bohr[v].flag) {
				std::pair<int, int> res(i - pattern[bohr[v].path_num].length() + 2, bohr[v].path_num + 1);
				answer.push_back(res);
			}
		}
		std::cout << std::endl << "Перейдем по хорошим суффиксным ссылкам вершины  " << u;
		if (i + 1 != s.length()) std::cout << " по символу " << s[i + 1] << std::endl;
		check(u, i + 1);//отмечаем по сжатым суффиксным ссылкам строки, которые нам встретились и их позицию
	}
	std::cout << std::endl << "Проход по строке текста завершен." << std::endl;
	system("pause");
	std::cout << "------------------------------------------------------------------------------" << std::endl;
	for (int i = answer.size() - 1; i >= 0; i--) {
		std::string::const_iterator sub = find_end(s.begin(), s.end(), (pattern[answer[i].second - 1]).begin(), (pattern[answer[i].second - 1]).end());
		if (sub != s.end()) {
			if (i != 0 && answer[i - 1].first + pattern[answer[i - 1].second - 1].size() - 1 >= answer[i].first) {
				s.erase(sub + answer[i - 1].first + pattern[answer[i - 1].second - 1].size() - answer[i].first, sub + pattern[answer[i].second - 1].size());
			}
			else
				s.erase(sub, sub + pattern[answer[i].second - 1].size());
			//cout << "Строка: " << s << endl;
		}
	}
	sort(answer.begin(), answer.end(), cmp);
	std::cout << std::endl << "Ответ:" << std::endl << "Позиция в тексте/номер шаблона" << std::endl;
	for (int i = 0; i < answer.size(); i++)
		std::cout << answer[i].first << " " << answer[i].second << std::endl;
	std::cout << "Строка после удаления найденных шаблонов: " << s << std::endl;
	return answer;
}