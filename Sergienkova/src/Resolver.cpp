#include "Resolver.h"


std::ostream& operator<<(std::ostream& os, Resolver& resolver)
{
	std::cout << resolver.m_Result.size() << std::endl;
	for (auto i = resolver.m_Result.begin(); i != resolver.m_Result.end(); ++i)
		os << *i << std::endl;
	os << "Operations count: " << resolver.m_Operations;
	return os;
}

void Resolver::Resolve(int n)
{
	// сброс количества операций
	m_Operations = 0;

	// принимаем данные
	m_N = n;
	m_Div = 1;

	// если четное то выдаем результат
	if (n % 2 == 0) {
		Resolve2();
		return;
	}

	// пробуем пропорционально уменьшить размер, для поиска в этом размере
	for (int i = 2; i < m_N; ++i) {
		if (m_N % i == 0) { // если можно 
			m_Div = m_N / i;
			m_N = i;
			break;
		}
	}
	std::cout << "fact N=" << m_N << std::endl;// с каким размером идет фактический расчет

	// очистка
	m_Result.clear();
	m_Tiles.clear();

	// создаем массив занятых клеток
	m_Data = new int*[m_N];
	for (int i = 0; i < m_N; ++i) m_Data[i] = new int[m_N];
	
	// зануляем массив занятых клеток
	for (int i = 0; i < m_N; ++i)
		for (int j = 0; j < m_N; ++j)
			m_Data[i][j] = 0;

	// вставка первых 3 элементов
	Add(Tile(0, 0, m_N / 2 + 1));
	Add(Tile(m_N / 2 + 1, 0, m_N / 2));
	Add(Tile(0, m_N / 2 + 1, m_N / 2));

	// ищем первый пустой элемент
	auto pos = FindEmpty();

	// запуск перебора всех раскладок
	Scan(Tile(pos.x, pos.y, 1));

	// удаляем массив занятых клеток
	for (int i = 0; i < m_N; ++i) delete[] m_Data[i];

	// восстанавливаем размер
	m_N *= m_Div;
	for (auto i = m_Result.begin(); i != m_Result.end(); ++i) {
		(*i).Position.x *= m_Div;
		(*i).Position.y *= m_Div;
		(*i).Size *= m_Div;
	}

	delete[] m_Data;	
}
bool Resolver::CanAdd(Tile tile)
{
	// если тайл выходит за рамки то нельзя
	if (tile.Position.x + tile.Size > m_N) return false;
	if (tile.Position.y + tile.Size > m_N) return false;

	// если на месте тайла уже есть тайл то нельзя
	for (int y = tile.Position.y; y < tile.Position.y + tile.Size; ++y)
		for (int x = tile.Position.x; x < tile.Position.x + tile.Size; ++x)
			if(m_Data[x][y]) return false;

	// если все ок
	return true;
}
bool Resolver::HasResult()			// если истина, то получен результат
{
	// если где-то есть пустота то результата нет
	for (int y = 0; y < m_N; ++y)
		for (int x = 0; x < m_N; ++x)
			if (m_Data[x][y] == 0) return false;

	// если нигде нет то ок
	return true;
}
Position Resolver::FindEmpty()		// возвращает первое попавшееся пустое место
{
	// если гдето есть пустота то результата нет
	for (int y = m_N / 2; y < m_N; ++y) {
		if (y >= m_N / 2 + 1) {
			for (int x = m_N / 2; x < m_N; ++x) {
				++m_Operations;
				if (m_Data[x][y] == 0) return Position(x, y);
			}
		}
		else {
			for (int x = m_N / 2 + 1; x < m_N; ++x) {
				++m_Operations;
				if (m_Data[x][y] == 0) return Position(x, y);
			}
		}
	}

	// если гдето есть пустота то результата нет
	/*for (int y = 0; y < m_N; ++y) {
		for (int x = 0; x < m_N; ++x) {
			++m_Operations;
			if (m_Data[x][y] == 0) return Position(x, y);
		}
	}*/

	// если не найдено
	throw "has no empty position";
}
void Resolver::Remove()				// удаляет последний тайл из раскладки
{
	// берем последний тайл
	auto tile = m_Tiles.back();
	// удаляем из cписка
	m_Tiles.pop_back();
	// пишем данные в массив
	for (int y = tile.Position.y; y < tile.Position.y + tile.Size; ++y)
		for (int x = tile.Position.x; x < tile.Position.x + tile.Size; ++x)
			m_Data[x][y] = 0;
}
void Resolver::Add(Tile tile)
{
	// увеличиваем количество операций
	++m_Operations;
	// вставка в список
	m_Tiles.push_back(tile);
	// пишем данные в массив
	for (int y = tile.Position.y; y < tile.Position.y + tile.Size; ++y)
		for (int x = tile.Position.x; x < tile.Position.x + tile.Size; ++x)
			m_Data[x][y] = 1;
}
bool Resolver::Scan(Tile tile)		// попытка найти результат, начиная с добавления указанного тайла
{
	// ограничитель
	if (tile.Size >= m_N) return false;
	if (!CanAdd(tile)) return false;

	// добавляем тайл
	Add(tile);

	// если есть результат - анализируем его
	if (HasResult()) {
		// если рузультат лучший - запоминаем его
		if (m_Tiles.size() < m_Result.size() || m_Result.size() == 0)
			m_Result = m_Tiles;
		// откат назад
		/*Remove();
		// скан с большим тайлом
		++tile.Size;
		Scan(tile);
		// результат был - далее не сканируем (истина тк просканировано)
		return true;*/
	}
	else {
		// если результата нет - сканируем все возможные квадраты на первом попавшемся месте
		// берем первое попавшееся пустое место
		auto position = FindEmpty();
		// начинаем скан с этой свободной позиции
		tile = Tile(position.x, position.y, 1);
		while (Scan(tile)) ++tile.Size;
	}

	// откат назад
	Remove();

	// вывод истины, тк просканировано
	return true;
}
void Resolver::Resolve2()			// возвращает решение для четного n
{
	m_Result.push_back(Tile(0, 0, m_N / 2));
	m_Result.push_back(Tile(0, m_N / 2, m_N / 2));
	m_Result.push_back(Tile(m_N / 2, 0, m_N / 2));
	m_Result.push_back(Tile(m_N / 2, m_N / 2, m_N / 2));
}
