#ifndef KMP_H
#define KMP_H

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <cstdlib>

void readStrings(std::string& str1, std::string& str2, std::istream& in);
std::vector<int> prefixFunc(std::string& text);
std::vector<int> KMP(std::string& substring, std::string& text);

#endif