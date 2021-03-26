#pragma once
#include <iostream>
#include <iostream>
#include <ctime>

class Square {
private:
	int** coloring; 
	int* abscissa; 
	int* ordinate; 
	int* length;    
	int  count;     
	int  size;      
	int  num;        
	bool last_sq;          

	void insert_square(int x, int y, int n, int side);
	void remove_square(int x, int y, int side);
	bool place_to_insert(int& x, int& y);
	bool multiple_of_three(int side);
	int  find_max_size(int x, int y);
	bool multiple_of_five(int side);
	bool insert_the_second_square();
	bool insert_the_third_square();
	bool even_square(int side);
	void print_square(int deep);
	friend class test;

public:
	void output_of_the_result(int amount);
	int  insert_the_first_square();
	int  backtracking(int deep);
	Square(int size);
	~Square();
};