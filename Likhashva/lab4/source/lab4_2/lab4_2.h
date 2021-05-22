#pragma once

#include <iostream>
#include <vector>

class KMP {
private:
	std::string A, B;
	mutable std::vector<int> arrPrefix;
	mutable int answer;
public:
	KMP() {};
	void Read();
	void PrintAnswer() const;
	void Prefix() const;
	void CyclicShift() const;
};