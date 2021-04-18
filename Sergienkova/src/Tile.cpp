#include "Tile.h"


std::ostream& operator<<(std::ostream& os, Tile& tile)
{
	return os << tile.Position << ' ' << tile.Size;
}

Tile::Tile(int x, int y, int size) :
	Position(x, y)
{
	this->Size = size;
}