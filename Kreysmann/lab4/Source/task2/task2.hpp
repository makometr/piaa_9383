#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void input(std::string& str1, std::string& str2, std::istream& in);
int KMP(std::string& A, std::string& B);
std::vector<int> prefix(std::string &str);