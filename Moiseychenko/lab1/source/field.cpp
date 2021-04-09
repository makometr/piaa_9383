#include "field.h"

Field::Field(int n) {
	this->n = n;
	freeArea = n * n;
	field.resize(n, std::vector<int>(n, 0));
	squares.reserve(n * n);
}

std::vector<int>& Field::operator[](int index) {
	return field[index];
}

int Field::SquaresAmount() {
	return squares.size();
}

int Field::GetN() {
	return n;
}

int Field::GetArea() {
	return freeArea;
}
void Field::PrintSquares() {
	for (const auto& square : squares) {
		std::cout << square.x << " " << square.y << " " << square.size << std::endl;
	}
}

void Field::PrintField() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << field[j][i] << ' ';
		}
		if(field[j][i] < 10) {
			std::cout << ' ';
		}
		std::cout << "\n\n";
	}
}

void Field::AddSquare(Square& square) {
	if (square.x + square.size > n + 1 || square.y + square.size > n + 1)
		return;

	for (int i = square.x; i < square.x + square.size; i++) {
		for (int j = square.y; j < square.y + square.size; j++) {
			field[j - 1][i - 1] = squares.size() + 1;
		}
	}

	squares.push_back(square);
	freeArea -= square.size * square.size;
}

bool Field::CheckIntersection(const Square& square) {
	for (int i = square.x; i < square.x + square.size; ++i) {
		for (int j = square.y; j < square.y + square.size; ++j) {
			if (field[j - 1][i - 1])
				return true;
		}
	}

	return false;
}

void Field::RemoveLastSquare() {
	if (squares.empty()) {
		return;
	}

	Square& square = squares.back();
	for (int i = square.x; i < square.x + square.size; ++i) {
		for (int j = square.y; j < square.y + square.size; ++j) {
			field[j - 1][i - 1] = 0;
		}
	}
	freeArea += square.size * square.size;
	squares.pop_back();
}
