#pragma once

#include <iostream>
#include <ctime>

#define N 20 //maximum edge length

bool restore(int*, int, int, int&); //backtracking current branch solution
void fill(const int*, int, int); //insert square into figure
bool update(int*, int, int); //search coordinates to insert square
int find(int, int, int, int); //search square size to insert
void clean(const int*, int, int); //delete square from figure
void copy(int*&, int*, bool); //primitive copy array A to array B (if boolean param is true array A allocate)
void answer_delete(int); //need to control allocated memory
void answer_print(int, int); //print in console