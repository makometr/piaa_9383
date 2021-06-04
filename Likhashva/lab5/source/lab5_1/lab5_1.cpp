#include "lab5_1.h"


Bor* CreateBor(const std::vector<std::pair<std::string, int>>& patterns) { //создание бора
	std::cout << "\n_Ќачало построени€ бора_";
	Bor* bor = new Bor();	// корень бора
	for (auto& pt : patterns) {
		int NumPattern = find(patterns.begin(), patterns.end(), pt) - patterns.begin();
		std::cout << "\n–ассматриваетс€ " << NumPattern + 1 << " шаблон: " << pt.first << '\n';
		Bor* current = bor;	// поиск пути, начина€ от корн€
		for (auto& c : pt.first) {
			if (current->next.find(c) == current->next.end()) { //если такого ребра нет, то добавл€етс€
				current->next.insert({ c, new Bor(current, c) });
				std::cout << "¬ бор добавлена вершина, куда ведЄт символ (" << c << ")\n";
			}
			else {
				std::cout << "–ебро (" << c << ") дл€ текущего шаблона уже существует. ¬ыполнение перехода.\n";
			}
			current = current->next[c]; // переход по данному ребру
			current->NumPattern.push_back(NumPattern);
		}
		current->TermNumPattern = NumPattern; // дл€ конечной вершины
		current->IsTerminal = true;
		std::cout << "¬ершина €вл€етс€ терминальной, закончено построение ветви бора.\n";
	}
	return bor;
}


void Automaton(Bor* bor) {  //вычисление суф. и конечных ссылок (построение автомата)
	std::cout << "\n\n_¬ычисление суффиксных и конечных ссылок_\n";
	std::queue<Bor*> front({ bor });  // вершины одного уровн€ в боре
	while (!front.empty()) {
		Bor* current = front.front();
		front.pop();
		Bor* CurrentLink = current->parent->SufLink; // родительска€ ссылка стала текущей
		const char& key = current->ToParent;	// сохран€етс€ символ, дл€ которого ищетс€ ссылка
		bool IsFound = true;	
		while (CurrentLink->next.find(key) == CurrentLink->next.end()) { 
			if (CurrentLink == bor) {
				std::cout << "—уффиксные ссылки не найдены, ссылка установлена на корень.\n";
				current->SufLink = bor;	// если из корн€ нет пути, то ссылка устанавливаетс€ в корень
				IsFound = false;  //ссылка, не равна€ корню, не найдена
				break;
			}
			CurrentLink = CurrentLink->SufLink;
		}
		if (IsFound) {
			CurrentLink = CurrentLink->next.at(key); 
			if (current->parent == bor) {
				std::cout << "“екуща€ вершина - начало слова, поэтому ссылка установлена на корень.\n";
				current->SufLink = bor;	// дл€ вершин первого уровн€ ссылки ведут в корень (иначе эти вершины будут ссылатьс€ на себ€)
			}
			else {
				current->SufLink = CurrentLink;
				Bor* CurEndLink = current->SufLink;
				while (CurEndLink != bor) {	// поиск конечной ссылки. если дошли до корн€, значит еЄ нет
					if (CurEndLink->IsTerminal) {
						current->EndLink = CurEndLink;
						break;
					}
					CurEndLink = CurEndLink->SufLink;
				}
			}
		}
		if (!current->next.empty()) {	// добавл€ютс€ новые вершины в очередь
			for (auto& i : current->next) {
				front.push(i.second);
			}
		}
	}
}


std::pair<int, int> LongestChain(Bor* bor, Bor* root, int& depth) {  //вычисление длин наибольших цепочек из суф. и конечных ссылок
	std::pair<int, int> longest = { 0, 0 };
	Bor* current = bor;
	while (current->SufLink != root) {
		longest.first++;
		current = current->SufLink;
	}
	longest.first++;
	current = bor;
	while (current->EndLink != nullptr) {
		longest.second++;
		current = current->EndLink;
	}
	for (auto& i : bor->next) {
		std::pair<int, int> next = LongestChain(i.second, root, ++depth);
		if (next.first > longest.first) {
			longest.first = next.first;
		}
		if (next.second > longest.second) {
			longest.second = next.second;
		}
	}
	depth--;
	return longest;
}


void AhoCorasick(const std::string& t, const std::vector<std::pair<std::string, int>>& patterns, std::vector<std::pair<int, int>>& result) {
	int length = 0;
	Bor* bor = CreateBor(patterns);
	Automaton(bor);
	std::cout << "\n\n_ѕоиск самых длинных цепочек из суффиксных и конечных ссылок_\n";
	int depth = 0;
	std::pair<int, int> longest = LongestChain(bor, bor, depth);
	std::cout << "ƒлина наибольшей цепочки из суффиксных ссылок: " << longest.first << '\n';
	std::cout << "ƒлина наибольшей цепочки из конечных ссылок: " << longest.second << '\n';
	Bor* current = bor;
	for (int i = 0; i < t.length(); i++) {
		current = current->GetLink(t.at(i));  // получена ссылка дл€ перехода 
		Bor* EndLink = current->EndLink;
		while (EndLink != nullptr) {  // если у этой вершины есть конечна€ ссылка, значит нашелс€ шаблон
			result.push_back({ i - patterns.at(EndLink->TermNumPattern).first.length() + 2, EndLink->TermNumPattern + 1 });
			EndLink = EndLink->EndLink;	// и так, пока цепочка из конечных ссылок не прервЄтс€
		}
		if (current->IsTerminal)  // если вершина терминальна€ - шаблон найден
			result.push_back({ i - patterns.at(current->TermNumPattern).first.length() + 2, current->TermNumPattern + 1 });
	}
	delete bor;
}

