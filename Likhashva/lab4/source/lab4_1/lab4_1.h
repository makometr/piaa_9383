#pragma once

#include <iostream>
#include <vector>


class KMP {
private:
	std::string P, T;
	mutable std::vector<int> arrPrefix;
	mutable std::vector<int> answer;
public:
	KMP() {};
	void Read();
	void PrintAnswer() const;
	void Prefix() const;
	void AlgorithmKMP() const;
};