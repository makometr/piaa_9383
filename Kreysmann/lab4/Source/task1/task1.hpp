#include <iostream>
#include <string>
#include <vector>
using Result = std::vector<int>;

void input(std::string& str1, std::string& str2, std::istream& in);
Result KMP(std::string P, std::string T);
void output(Result result, std::ostream& out);
std::vector<int> prefix(std::string &str);