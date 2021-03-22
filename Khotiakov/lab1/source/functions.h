#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
using namespace std;

extern int N;
extern int minCounter;
extern vector<pair<int, pair<int, int>>> resArr;

void insertBlock(vector<vector<bool>> &, int, int, int);

void removeBlock(vector<vector<bool>> &, int, int, int);

pair<int, int> findEmpty(vector<vector<bool>> &);

pair<int, bool> findMaxSize(vector<vector<bool>> &, int, int);

void chooseBlock(vector<vector<bool>> &, vector<pair<int, pair<int, int>>> &, int, int, int);

void primeNumber(vector<vector<bool>> &);

void printAnswer(int scale = 1);

void division2();

void division3(vector<vector<bool>> &);

void division5(vector<vector<bool>> &);

#endif