#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
using namespace std;

class Table
{
    int N;
    int minCounter;
    vector<pair<int, pair<int, int>>> resArr;
    vector<vector<bool>> mainArr;

public:
    Table(int N) : N(N), minCounter(N * N), mainArr(N)
    {
        for (int i = 0; i < N; i++)
            mainArr[i].resize(N);
    }

    void insertBlock(int, int, int);

    void removeBlock(int, int, int);

    pair<int, int> findEmpty();

    pair<int, bool> findMaxSize(int, int);

    void chooseBlock(vector<pair<int, pair<int, int>>> &, int, int, int);

    void primeNumber();

    void printAnswer(int scale = 1);

    void division2();

    void division3();

    void division5();
};

#endif