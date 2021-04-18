#pragma once
#include <iostream>
#include "Position.h"

class Tile
{
public:
	Position Position;
	int Size;

	Tile(int x, int y, int size);

	friend std::ostream& operator<<(std::ostream& os, Tile& tile);
};

