#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>

class Table
{
    int N;
    int minCounter;
    std::vector<std::pair<int, std::pair<int, int>>> resArr;
    std::vector<std::vector<bool>> mainArr;

public:
    Table(int N) : N(N), minCounter(N * N), mainArr(N)
    {
        for (int i = 0; i < N; i++)
            mainArr[i].resize(N);
    }

    void insertBlock(int, int, int);

    void removeBlock(int, int, int);

    std::pair<int, int> findEmpty();

    std::pair<int, bool> findMaxSize(int, int);

    void chooseBlock(std::vector<std::pair<int, std::pair<int, int>>> &, int, int, int);

    void primeNumber();

    void printAnswer(int scale = 1);

    void division2();

    void division3();

    void division5();
};

#endif