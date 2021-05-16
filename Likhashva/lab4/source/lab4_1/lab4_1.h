#pragma once

#include <iostream>
#include <vector>


class KMP {
private:
	std::string P, T;
	std::vector<int> arrPrefix;
	std::vector<int> answer;
public:
	KMP() {};
	void Read();
	void PrintAnswer();
	void Prefix();
	void AlgorithmKMP();
};