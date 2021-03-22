#include "API.h"

int* mutation[N+N]; //current branch solution
int* answer[N+N]; //need to copy mutation for save the best solution
int table[N*N]; //figure projection
bool rectangle; //boolean to switch moving in an array

bool restore(int* square, int width, int height, int& count) {
    int w = std::min(width, height);
    
    while (count) {
        copy(square, mutation[count - 1], false);
        delete [] mutation[count - 1];
        mutation[count - 1] = nullptr;
        count--;
        clean(square, width, height);
        if (!count && square[2] < 2) {
            return false;
        }
        
        if (square[2] > 1) {
            square[2]--;
            return true;
        }

    }
    return false;
}

void fill(const int* square, int width, int height) {
    for (int *i = &table[square[0] + square[1] * width]; i != &table[square[0] + square[1] * width + square[2]]; ++i) {
        for (int j = 0; j < square[2]; ++j) {
            *(i + j * width) = square[2];
        }
    }
}

bool update(int* square, int width, int height) {
    int index = square[0] + square[1] * width;

    while (index < height * width) {
        if (!table[index]) {
            square[0] = index % width;
            square[1] = index / width;
            square[2] = find(square[0], square[1], width, height);
            return true;
        }

        index += table[index];
    }
    return false;
}

int find(int x, int y, int width, int height) {
    int w = std::min(width, height) - 1;
    int min = 1;
    while (min <= w) {
        
        if (x + min > width || y + min > height) {
            return min - 1;
        }

        if (rectangle) {
            for (int *i = &table[x + y * width]; i != &table[x + y * width + min]; ++i) {
                for (int j = 0; j < min; ++j) {
                    if (*(i + j * width)) {
                        return min - 1;
                    }
                }
            }
        }

        else if (table[x + y * width + min - 1] || table[x + y * width + (min - 1) * width] || table[x + y * width + min - 1 + (min - 1) * width]) {
            return min - 1;
        }

        min++;
    }

    return min - 1;
}

void clean(const int* square, int width, int height) {
    for (int *i = &table[square[0] + square[1] * width]; i != &table[square[0] + square[1] * width + square[2]]; ++i) {
        for (int j = 0; j < square[2]; ++j) {
            *(i + j * width) = 0;
        }
    }
}

void copy(int*& a, int* b, bool memory) {
    if (memory) {
        if (a) {
            delete [] a;
        }
        a = new int[3];
    }
    for (int i = 0; i < 3; ++i) {
        a[i] = b[i];
    }
}

void answer_delete(int count) {
    if(!answer[0]) {
        return;
    }

    for (int i = 0; i < count; ++i) {
        delete [] answer[i];
        answer[i] = nullptr;
    }
}

void answer_print(int square_count, int solve_count) {
    std::cout << "minimal square count: " << square_count << std::endl;
    std::cout << "{x,y,w}" << std::endl;
    for (int i = 0; i < square_count; ++i) {
        std::cout << "{" << answer[i][0] + 1 << "," << answer[i][1] + 1 << "," << answer[i][2] << "}" << std::endl;
        delete [] answer[i];
    }

    std::cout << "variation count: " << solve_count << std::endl;
    std::cout << "time = " << clock()/1000000.0 << " sec" << std::endl;
}