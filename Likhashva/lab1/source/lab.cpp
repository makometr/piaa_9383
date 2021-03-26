#include "lab.h"

Table table;


Square Table::DeleteSquare(int size) { //Функция для удаления последнего квадрата
	if (table.CurrentStack.size() == 0)
		return Square{ -1, -1, -1 };
	Square Last = table.CurrentStack.back();
	table.CurrentStack.pop_back();
	//cout << "Был удален квадрат: " << Last.x + 1 << ' ' << Last.y + 1 << ' ' << Last.size << '\n';
	for (int i = 0; i < Last.size; ++i) {
		for (int j = 0; j < Last.size; ++j) {
			table.Field[i + Last.y][j + Last.x] = 0;
		}
	}
	return Last;
}



Square Table::FindFreeCell(int size) {  //Функция поиска пустой клетки на столешнице
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (table.Field[i][j] == 0)
				return { 0, j, i };
		}
	}
	return { -1, -1, -1 };
}


Square Table::Place(int size, Square Alleged) { //Функция, которая помещает квадрат на столешнице (используя последнюю позицию удаленного квадрата)
	Square Result;
	int SizeOfRes = 1;
	if (Alleged.size > 0) { //используем информацию о последнем удаленном квадрате
		Result = Alleged;
		Result.size--;
	}
	else {
		Result = { size - 1, 0, 0 }; //первый шаг
	}
	//Определяем размер квадрата, который будет меньше, чем предыдущий квадрат. Также он должен помещаться на столешницу.
	while (SizeOfRes < Result.size && SizeOfRes < size - Result.x && SizeOfRes < size - Result.y) {
		if(table.Field[Result.y][Result.x + SizeOfRes] == 0)
			SizeOfRes++;
	}

	Result.size = SizeOfRes;
	for (int i = 0; i < Result.size; ++i) { // Расположение квадрата
		for (int j = 0; j < Result.size; ++j) {
			table.Field[Result.y + i][Result.x + j] = 1;
		}
	}
	return Result;
}


void Table::Backtracking(int size) {  //Итеративный поиск с возратом
	bool back = false;
	bool full = false;
	int div = 1;
	Square Alleged{ -1, 0, 0 };
	Square ResultPlace{ 0, 0, 0 };
	for (int i = 2; i <= size; i++) { //Уменьшение размера столешницы до наименьшего простого делителя
		if (size % i == 0) {
			div = size / i;
			size = i;
		}
	}

	//cout << "Расположение первых квадратов:\n";
	//cout << "Первый квадрат: 1 1 " << (size + 1) / 2 << "\n";
	//cout << "Второй квадрат: 1 " << (size + 1) / 2 + 1 << " " << size - (size + 1) / 2 << "\n";
	//cout << "Третий квадрат: " << (size + 1) / 2 + 1 << " 1 " << size - (size + 1) / 2 << "\n";

	ResultPlace = Place(size, { (size + 1) / 2 + 1, 0, 0 }); //Сохранение в стэк квадратов
	table.CurrentStack.push_back(ResultPlace);
	ResultPlace = Place(size, { size - (size + 1) / 2 + 1, 0, (size + 1) / 2 });
	table.CurrentStack.push_back(ResultPlace);
	ResultPlace = Place(size, { size - (size + 1) / 2 + 1, (size + 1) / 2, 0 });
	table.CurrentStack.push_back(ResultPlace);
	Alleged = FindFreeCell(size);
	Alleged.size = size - 1;

	//Начало цикла
	do {
		int last_size = 0;
		full = false;
		back = false;
		while (!full) {  //Пока столешница не будет полностью заполнена
			ResultPlace = Place(size, Alleged); //Расположим один квадрат
			table.CurrentStack.push_back(ResultPlace);
			if ((table.BestStack.size() > 0) && (table.CurrentStack.size() > 0) && (table.CurrentStack.size() >= table.BestStack.size())) {
				back = true;  //Если текущее расположение хуже, то делаем шаг назад (удаляем квадрат)
				DeleteSquare(size);
				Alleged = DeleteSquare(size); //Квадраты были расположены наилучшим способом
				break;
			}
			Alleged = FindFreeCell(size); //Подготовка к следующему размещению квадратов
			full = (Alleged.size == -1);
			Alleged.size = size;
		}
		if (!back) { //Если столешница заполнена
			if ((table.CurrentStack.size() < table.BestStack.size()) || (table.BestStack.size() == 0)) { //Сравнение текущего расположения с лучшим расположением
				table.BestStack = table.CurrentStack;
			}
		}

		do {
			Alleged = DeleteSquare(size); //Сделать шаг назад, если размер квадрата равен 1 или 2, если столешница заполнена
		} while (Alleged.size == 1 || (full && Alleged.size == 2) && table.CurrentStack.size() >= 3);


	} while (table.CurrentStack.size() >= 3);

	for (int i = 0; i < table.BestStack.size(); i++) {
		table.BestStack[i].x *= div;
		table.BestStack[i].y *= div;
		table.BestStack[i].size *= div;
	}
}


int main() {
	setlocale(LC_ALL, "Russian");
	int N;
	cout << "Введите размер столешницы:\n";
	cin >> N;
	double time = clock();

	if (N % 2 == 0) {
		cout << "\nРазмер четный, бэктрекинг не требуется.\n";
		cout << 4 << "\n";
		cout << 1 << ' ' << 1 << ' ' << N / 2 << "\n";
		cout << N / 2 + 1 << ' ' << 1 << ' ' << N / 2 << "\n";
		cout << 1 << ' ' << N / 2 + 1 << ' ' << N / 2 << "\n";
		cout << N / 2 + 1 << ' ' << N / 2 + 1 << ' ' << N / 2 << "\n";
	}
	else {
		cout << "\nВыполнение бэктрекинга:\n";
		table.Backtracking(N);
		cout << table.BestStack.size() << "\n";
		for (auto& Res : table.BestStack)
			cout << Res.x + 1 << ' ' << Res.y + 1 << ' ' << Res.size << '\n';
	}

	cout << "\n------------------------------------------------------\n";
	cout << "_Исследование времени выполнения от размера квадрата_\n";
	cout << "При размере квадрата " << N << " было затрачено времени: " << (clock() - time) / 1000.0 << '\n';
	return 0;
}