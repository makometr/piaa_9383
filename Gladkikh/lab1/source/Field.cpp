#include "Field.h"


Field::Field(int size) {
    size_ = size;
    default_square_size_ = size_ / 2;
    cur_square_size_ = default_square_size_;
    Init();
}

void Field::Print() {
    for(auto line: matrix_) {
        for(auto cell: line) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

void Field::PrintStack() {
    //std::cout << "Total: " << square_stack_.size() << " squares\n";
    std::cout << square_stack_.size() << "\n";
    while(!square_stack_.empty()) {
        Square square = square_stack_.top();
        square_stack_.pop();
        std::cout << square.x + 1 << " " << square.y + 1 << " " << square.size << "\n";
    }
}

void Field::PlaceSquare(int x, int y) {
    if (y + cur_square_size_ > size_ || y < 0) return;
    if (x + cur_square_size_ > size_ || x < 0) return;

    squares_amount_++;

    for (int i = y; i < y + cur_square_size_; i++) {
        for (int j = x; j < x + cur_square_size_; j++) {
            ++operations_amount_;
            matrix_[i][j] = squares_amount_;
        }
    }

	square_stack_.push({ x, y, cur_square_size_ });

    cur_square_size_ = default_square_size_;
}

bool Field::Fill(int min_amount) {
	for (int y = size_ / 2; y < size_; y++) {
        for (int x = size_ / 2; x < size_; x++) {
            ++operations_amount_;
            if (!matrix_[y][x]) {
                if (squares_amount_ >= min_amount) {
                    return false;
				}
                while(!CheckEnoughPlace(x, y)) {
                    --cur_square_size_;
                }
                //std::cout << "x: " << x << " y: " << y << "\n";
                //std::cout << cur_square_size_ << "\n";
                PlaceSquare(x, y);
			}
		}
	}
	return true;
}

void Field::Backtrace() {
    Square last_square = square_stack_.top();
    while(square_stack_.size() > 3 && last_square.size == 1) {
        DeleteSquare();
        last_square = square_stack_.top();
    }
    if(square_stack_.size() == 3) { // && square_stack_.top().size == 1 // square_stack_.top().size < size_ / 2
        running_ = false;
        return;
    }

    int x = last_square.x;
    int y = last_square.y;
    cur_square_size_ = last_square.size - 1;

    DeleteSquare();

    PlaceSquare(x, y);
}


void Field::Init() {
    matrix_.resize(size_);
    for(auto& line: matrix_) {
        line.resize(size_);
        for(auto& cell: line) {
            cell = 0;
        }
    }
}

bool Field::CheckEnoughPlace(int start_x, int start_y) {
    if (start_y + cur_square_size_ > size_ || start_y < 0) return false;
    if (start_x + cur_square_size_ > size_ || start_x < 0) return false;

    for (int y = start_y; y < start_y + cur_square_size_; y++) {
        for (int x = start_x; x < start_x + cur_square_size_; x++) {
            if(matrix_[y][x]) {
                return false;
            }
        }
    }

    return true;
}

void Field::DeleteSquare() {
    Square last_square = square_stack_.top();
    square_stack_.pop();
    --squares_amount_;

    for (int y = last_square.y; y < last_square.y + last_square.size; y++) {
        for (int x = last_square.x; x < last_square.x + last_square.size; x++) {
            ++operations_amount_;
            matrix_[y][x] = 0;
        }
    }
}
