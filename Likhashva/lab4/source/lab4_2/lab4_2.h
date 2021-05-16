#pragma once

#include <iostream>
#include <vector>

class KMP {
private:
	std::string A, B;
	std::vector<int> arrPrefix;
	int answer;
public:
	KMP() {};
	void Read();
	void PrintAnswer();
	void Prefix();
	void CyclicShift();
};