#include "API.h"

extern int* mutation[N+N];
extern int* answer[N+N];
extern int table[N*N];
extern bool rectangle;

int main(int argc, char *argv[]) {
    int width, height;
    std::cin >> width >> height;
    if (width < 2 || width > 20 || height < 2 || height > 20) {
        std::cout << "BAD CONFIGURATION: 1 < width,height < 21" << std::endl;
        std::exit(1);
    }

    int min = width * height;
    int solve_count = 0;
    
    if (width < height) {
        std::swap(width, height);
    }

    width == height ? rectangle = false, min = 17 : rectangle = true;

    int square[3] = {0, 0, std::min(width, height) - 1};
    /*  square[0] = x
        square[1] = y
        square[2] = width */

    int count = 0;

    for(;;) {
        if (count >= min && !restore(square, width, height, count)) {
            break;
        }
        fill(square, width, height);
        copy(mutation[count++], square, true);
        if (!update(square, width, height) && count <= min) {
            count < min ? answer_delete(min), min = count, solve_count = 1 : solve_count++;
            for (int i = 0; i < min; ++i) {
                copy(answer[i], mutation[i], true);
            }
        }
    }
    answer_print(min, solve_count);

    return 0;
}