#include <iostream>
#include <chrono>
#include <vector>

struct Position { // позиция на столе
	int x;
	int y;
};

struct Item {	// один элемент столешницы
	int x;
	int y;
	int w;	// размер обрезка

	Item(int x, int y, int w) {
		this->x = x;
		this->y = y;
		this->w = w;
	}

	friend std::ostream& operator <<(std::ostream& os, Item item);
};

std::vector<Item> GetRes(int N); // поиск результата
std::vector<Item> GetResEven(int N); // возвращает результата, если размер четный
bool PutItem(Item item, bool** table, int N, std::vector<Item>& m_Arr, std::vector<Item>& res, int sumS); // попытка добавить еще один итем в текущую раскладку
void Add(bool** table, std::vector<Item>& m_Arr, Item item); // добавляет указанный обрезок в раскладку
void RemoveLast(bool** table, std::vector<Item>& m_Arr); // удаляет последний элемент из раскладки
void ShowTable(bool** table, int N); // вывод таблицы на экран (для дебага)
bool CanAdd(bool** table, int N, Item item); // можно ли добавить указанный итем в таблицу
bool GetFirstEmpty(bool** table, int N, Position &position); // возвращает первую свободную позицию

int main() {
	int N;
	std::cout << "Size N = ";
	std::cin >> N;
    std::cout << std::endl;

	// расчет
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	auto res = GetRes(N);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << std::endl;
	// вывод результата
	std::cout << res.size() << std::endl;
	for (auto i = res.begin(); i != res.end(); ++i)
		std::cout << *i << std::endl;
    
    std::cout << std::endl;
    std::cout << "Time: " << std::chrono::duration<double>(end - start).count() << " s." << std::endl << std::endl;
	return 0;
}

std::ostream& operator <<(std::ostream& os, Item item) {
	return os << item.x + 1 << ' ' << item.y + 1 << ' ' << item.w; // +1 тк расчет ведем в системе координат от 0 а на экран требуют от 1
}
std::vector<Item> GetRes(int N) {
	if (N % 2 == 0) return GetResEven(N);
	// если сторона составная
	int div = 1;
	for (int i = 2; i <= N; ++i) {
		if (N % i == 0) {
			div = N / i;
			N = i;
		}
	}

	std::vector<Item> m_Arr;	// текущий список выложенных квадратов
	std::vector<Item> res;	// результат

	// создаем двумерный массив, описывающий доску
	bool** table = new bool* [N];
	for (auto i = 0; i < N; ++i) {
		table[i] = new bool[N];
		for (auto j = 0; j < N; ++j)
			table[i][j] = false;
	}
	// вывод дебага
	std::cout << "scan N=" << N << std::endl;

	// вставка 3 изначальных квадратов
	Add(table, m_Arr, Item(0, 0, N / 2 + 1));
	Add(table, m_Arr, Item(N / 2 + 1, 0, N / 2));
	Add(table, m_Arr, Item(0, N / 2 + 1, N / 2));
	int sumS = (N / 2 + 1) * (N / 2 + 1) + (N / 2) * (N / 2) + (N / 2) * (N / 2); // суммарная занятая площадь

	// ищем первое свободное
	Position pos;
	GetFirstEmpty(table, N, pos);	

	// поиск результата (вставкой всех возможных плиток вначало)
	for (int i = N/2+1; i > 0; --i)
		PutItem(Item(pos.x, pos.y, i), table, N, m_Arr, res, sumS);

	// удаляем доску
	for (auto i = 0; i < N; ++i) delete[] table[i];
	delete[] table;

	// восстановление размера
	for (auto i = res.begin(); i != res.end();++i) {
		(*i).x *= div;
		(*i).y *= div;
		(*i).w *= div;
	}

	// вывод результата
	return res;
}
std::vector<Item> GetResEven(int N) // возвращает результата, если размер четный
{
	if (N % 2 != 0) throw "N is not even";
	std::vector<Item> res;
	res.push_back(Item(0, 0, N / 2));
	res.push_back(Item(0, N / 2, N / 2));
	res.push_back(Item(N / 2, 0, N / 2));
	res.push_back(Item(N / 2, N / 2, N / 2));
	return res;
}
bool PutItem(Item item, bool** table, int N, std::vector<Item>& m_Arr, std::vector<Item>& res, int sumS) // попытка добавить еще один итем в текущую раскладку
{
	// ограничитель
	if (m_Arr.size() > res.size() && res.size() > 0) return false;
	if (sumS >= N * N) return false; // если площадь вся занята
	if (!CanAdd(table, N, item)) return false;

	// вставка итема
	Add(table, m_Arr, item);
	sumS += item.w * item.w;

	// берем индекс первого пустого места
	Position position;
	if (GetFirstEmpty(table, N, position)) {
		// делаем вставку всех итемов, которые возможны
		for (int i = N/2+1; i > 0; --i) {
			PutItem(Item(position.x, position.y, i), table, N, m_Arr, res, sumS);
		}
	}
	else { // если попали сюда, то доска стала заполненой - проверяем результат
		if (m_Arr.size() < res.size() || res.size() == 0)
			res = m_Arr;
	}

	// удаление итема
	RemoveLast(table, m_Arr);

	return true;
}
bool GetFirstEmpty(bool** table, int N, Position& position) // возвращает первую свободную позицию
{
	for (int x = 0; x < N; ++x)
		for (int y = 0; y < N; ++y)
			if (!table[x][y]) {
				position.x = x;
				position.y = y;
				return true;
			}
	return false;
}
bool CanAdd(bool** table, int N, Item item) // можно ли добавить указанный итем в таблицу
{
	if (item.x < 0 || item.x + item.w > N) return false;
	if (item.y < 0 || item.y + item.w > N) return false;

	for (int x = item.x; x < item.x + item.w; ++x)
		for (int y = item.y; y < item.y + item.w; ++y)
			if(table[x][y]) return false;
	return true;
}

void Add(bool** table, std::vector<Item>& m_Arr, Item item) // добавляет указанный обрезок в раскладку
{
	// добавляем в список
	m_Arr.push_back(item);

	// в таблицу
	for (int x = item.x; x < item.x + item.w; ++x)
		for (int y = item.y; y < item.y + item.w; ++y)
			table[x][y] = true;
}
void RemoveLast(bool** table, std::vector<Item>& m_Arr) // удаляет последний элемент из раскладки
{
	auto item = m_Arr.back();
	m_Arr.pop_back();

	for (int x = item.x; x < item.x + item.w; ++x)
		for (int y = item.y; y < item.y + item.w; ++y)
			table[x][y] = false;
}
