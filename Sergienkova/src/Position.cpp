#include "Position.h"

std::ostream& operator<<(std::ostream& os, Position& position)
{
	return os << position.x + 1 << ' ' << position.y + 1;
}

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}