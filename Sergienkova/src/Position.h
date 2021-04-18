#pragma once
#include <iostream>

class Position
{
public:
	int x;
	int y;

	Position(int x, int y);

	friend std::ostream& operator<<(std::ostream& os, Position& position);
};

