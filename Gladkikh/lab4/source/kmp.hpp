#pragma once

#include <vector>
#include <string>
#include <iostream>

std::vector<int> prefix_function(const std::string& str);
std::vector<int> kmp(const std::string& patt, const std::string& temp, bool stop_at_first);
int check_cycle(const std::string& patt, const std::string& temp);

bool read_strings(std::string& patt, std::string& temp, std::istream& in);
void print_vector(const std::vector<int>& vec);