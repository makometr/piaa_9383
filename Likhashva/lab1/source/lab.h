#ifndef LAB_H
#define LAB_H

#include <iostream>
#include <vector>
using namespace std;



struct Square { //Квадрат, который можно расположить на столешнице
	int size;
	int x;
	int y;

};

struct Table {
	bool Field[50][50];
	vector <Square> StepStack;  //Описывает заполнение столешницы
	vector <Square> CurrentStack; //Текущее заполнение столешницы
	vector <Square> BestStack; //Лучшее заполнение столешницы (наименьшее количество квадратов)

	Square DeleteSquare(const int& size);
	Square FreeCell(int size);
	Square Place(int size, Square Alleged);
	void Backtracking(int size);

};


#endif