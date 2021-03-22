#include "Square.h"
#define N 40


void Square::insert_square(int x, int y, int n, int side) { //заполнение квадрата (координаты, цвет и сторона)
	for (int i = x; i < side + x; i++)
		for (int j = y; j < side + y; j++)
			coloring[i][j] = n;
}

void Square::remove_square(int x, int y, int side) { //удаление квадрата (координаты и сторона)
	for (int i = x; i < side + x; i++)
		for (int j = y; j < side + y; j++)
			coloring[i][j] = 0;
}

bool Square::place_to_insert(int &x, int &y) { //поиск места для вставки нового квадрата, функция ищет самую верхнюю и левую пустую клетку поля
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (!coloring[i][j]) {
				x = i;
				y = j;
				return true;
			}
	return false;
}

bool Square::multiple_of_three(int side) { //разбиение квадрата, сторона которого кратна трём
	try
	{
		abscissa[1] = abscissa[2] = abscissa[3] = ordinate[3] = ordinate[5] = ordinate[4] = side;
		abscissa[5] = ordinate[2] = side * 1 / 2;
		abscissa[4] = ordinate[1] = 0;
		for (int i = 1; i < 6; i++) {
			length[i] = size * 1 / 3;
			insert_square(abscissa[i], ordinate[i], i + 1, length[i]);
		}
		return true;
	}
	catch (...)
	{
		return false;
	}

}

int Square::find_max_size(int x, int y) { //находит максимальное значение стороны квадрата, который возможно поместить на поле
	int  max_size;
	bool allowed = true;
	for (max_size = 1; allowed && max_size <= size - x && max_size <= size - y; max_size++) //проверка на пересечение границ квадрата
		for (int i = 0; i < max_size; i++)
			for (int j = 0; j < max_size; j++)
				if (coloring[x + i][y + j]) { //проверка на пересечение с уже существующим квадратом
					allowed = false;
					max_size--;
				}
	max_size--;
	return max_size;
}

bool Square::multiple_of_five(int side) {  //разбиение квадрата, сторона которого кратна пяти
	try
	{
		abscissa[1] = abscissa[2] = abscissa[7] = ordinate[4] = ordinate[5] = ordinate[7] = side;
		abscissa[5] = abscissa[6] = ordinate[2] = ordinate[3] = size * 2 / 5;
		length[2] = length[3] = length[5] = length[6] = side * 1 / 3;
		length[1] = length[4] = length[7] = side * 2 / 3;
		abscissa[3] = ordinate[6] = size * 4 / 5;
		abscissa[4] = ordinate[1] = 0;
		for (int i = 1; i < 8; i++) {
			insert_square(abscissa[i], ordinate[i], i + 1, length[i]);
		}
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool Square::insert_the_second_square() {  //вставляет второй квадрат слева от 1 на поле так, чтобы его сторона была максимально возможной
	try
	{
		abscissa[num] = length[0];
		ordinate[num] = 0;
		length[num] = find_max_size(abscissa[num], ordinate[num]);
		insert_square(abscissa[num], ordinate[num], num + 1, length[num]);
		num++;
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool Square::insert_the_third_square() {  //вставляет третий квадрат снизу от 1 на поле так, чтобы его сторона была максимально возможной
	try
	{
		abscissa[num] = 0;
		ordinate[num] = length[0];
		length[num] = find_max_size(abscissa[num], ordinate[num]);
		insert_square(abscissa[num], ordinate[num], num + 1, length[num]);
		num++;
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool Square::even_square(int side) {  //разбиение квадрата, сторона которого кратна двум
	try
	{
		abscissa[1] = abscissa[3] = ordinate[2] = ordinate[3] = size * 1 / 2;
		abscissa[2] = ordinate[1] = 0;
		for (int i = 0; i < 4; i++) {
			length[i] = size * 1 / 2;
			insert_square(abscissa[i], ordinate[i], i + 1, length[i]);
		}
		return true;
	}
	catch (...)
	{
		return false;
	}

}

void Square::print_square(int deep) { //вспомогательная функция, которая выводит получившийся квадрат
	for (int i = 0; i < size; i++) {
		for (int f = 0; f < deep - 3; f++) std::cout << "\t";
		for (int j = 0; j < size; j++)
			std::cout << coloring[i][j] << ' ';
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Square::output_of_the_result(int amount) {  //выводит результат работы программы на консоль
	std::cout <<"Минимальное число квадратов для разбиения "<< amount << std::endl;//количество квадратов
	std::cout << amount << std::endl;
	for (int i = 0; i < amount; i++)
		std::cout << abscissa[i] + 1 << " " << ordinate[i] + 1 << " " << length[i] << std::endl;
	for (int j = 3; j < amount; j++) insert_square(abscissa[j], ordinate[j], j + 1, length[j]);
	std::cout << "Матричное представление результата" << std::endl;
	print_square(3);
}

int Square::insert_the_first_square() {  //функция вставки самого первого квадрата
	abscissa[num] = ordinate[num] = 0;
	if (size % 2 == 0) { 
		std::cout << "Квадрат с четной стороной. Частный случай. Делим квадрат на 4 части." << std::endl;
		insert_square(0,0,1, size * 1 / 2);
		even_square(size * 1 / 2);  //квадраты со стороной 1/2 от длины
		return 4;
	}
	if (size % 3 == 0) {                 //если сторона квадрата кратна 3-м
		std::cout << "Квадрат со стороной кратной 3. Частный случай. Делим квадрат на 6 частей." << std::endl;
		length[num] = size * 2 / 3;
		insert_square(0, 0, 1, length[num]);
		multiple_of_three(length[num]); //рисуем 6 квадратов со сторонами 2/3 и 5 по 1/3 от длины
		return 6;
	}
	if (size % 5 == 0) {                 //если сторона квадрата кратна 5-ти
		std::cout << "Квадрат со стороной кратной 5. Частный случай. Делим квадрат на 8 частей." << std::endl;
		length[num] = size * 3 / 5;
		insert_square(0, 0, 1, length[num]);
		multiple_of_five(length[num]); //рисуем 8 квадратов со сторонами 3/5 3 по 2/5 и 4 по 1/5 от длины
		return 8;
	}
	else {                              //все остальные случаи
		std::cout << "Общий случай. Используем бэктрекинг." << std::endl;
		length[num] = size * 1 / 2 + 1;
		insert_square(abscissa[num], ordinate[num], num + 1, length[num]);//вставляем квадрат со стороной больше половины
		num++;
		insert_the_second_square();//второй квадрат с максимальной длиной стороны
		insert_the_third_square();//и третий
		std::cout << "Построили первые три квадрата и запустили рекурсивную функцию." << std::endl;
		print_square(3);
		return backtracking(4);
	}
}

int Square::backtracking(int deep) {//перебирает всевозможные варианты кадрирования неразбитого участка поля
	if (f && deep > num) //bool f-последний квадрат              //если текущее разбиение больше предыдущего
		return deep;
	int min_result = size * size;
	int temp_length;
	int temp_result;
	int temp_x;
	int temp_y;
	if (!place_to_insert(temp_x, temp_y)) { //если нет места для вставки
		for (int i = 0; i < deep - 3; i++) std::cout << "\t";
		std::cout << "Больше нет места для вставки. Текущее разбиение " << deep-1 << std::endl;

		if (deep < min_result) {
			for (int i = 0; i < deep - 3; i++) std::cout << "\t";
			std::cout << "Получили новый меньший результат " << deep-1 << std::endl;
		}

		if (!f || (f && deep - 1 < num))
			num = deep - 1;//номер последнего квадрата
		f = true;//последний квадрат
		return num;//количество квадратов
	}
	for (temp_length = find_max_size(temp_x, temp_y); temp_length > 0; temp_length--) {//длина-максимальная для вставки
		for (int i = 0; i < deep - 3; i++) std::cout << "\t";
		std::cout << "Вставляем новый квадрат по координатам " << temp_x + 1 << ' ' << temp_y + 1 <<" со стороной " << temp_length << " под номером " << deep << std::endl;
		insert_square(temp_x, temp_y, deep, temp_length);//вставляем новый квадрат
		print_square(deep);
		temp_result = backtracking(deep + 1);//рекурсия-вставляем квадраты дальше
		min_result = min_result < temp_result ? min_result : temp_result;//если промежуточный результат меньше, то заменяем
		
		if (temp_result <= num) { //если текущий результат не превосходит номер текущего квадрата (получили меньший результат)
			for (int i = 0; i < deep - 3; i++) std::cout << "\t";
			std::cout << "Сохраним координаты и размер текущего квадрата" << std::endl;
			length[deep - 1] = temp_length;//сохраняем в массивы данные
			abscissa[deep - 1] = temp_x;
			ordinate[deep - 1] = temp_y;
		}
		for (int i = 0; i < deep - 3; i++) std::cout << "\t";
		std::cout << "Вернемся назад. Удалим последний квадрат." << std::endl;
		remove_square(temp_x, temp_y, temp_length);//удаляем квадрат
	}
	return min_result;
}

Square::Square(int size) : size(size) {//конструктор
	coloring = new int*[size];//массив квадрата заполнен 0
	for (int i = 0; i < size; i++) {
		coloring[i] = new int[size];
		for (int j = 0; j < size; j++)
			coloring[i][j] = 0;
	}
	abscissa = new int[N];
	ordinate = new int[N];
	length = new int[N];
	count = N;
	f = false;
	num = 0;
}

Square::~Square() {
	delete[] abscissa;
	delete[] ordinate;
	delete[] length;
	for (int i = 0; i < size; i++)
		delete[] coloring[i];
	delete[] coloring;
}

int main() {
	setlocale(LC_ALL, "Russian");
	int size, count;
	clock_t time;
	std::cout << "Введите размер стола:" << std::endl;
	while (std::cin >> size && size > 1) {
		time = clock();
		Square table(size);
		count = table.insert_the_first_square();
		table.output_of_the_result(count);
		time = clock() - time;
		std::cout << "Время работы программы в секундах  " << time / CLOCKS_PER_SEC << std::endl;
		std::cout << std::endl << "Введите размер стола:" << std::endl;
	}
	std::cout << "Неверный ввод" << std::endl;
}