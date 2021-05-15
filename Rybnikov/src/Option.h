#pragma once
#include <iostream>
#include <vector>
#include "Orgraph.h"

class Option
{
	std::vector<char> m_Result1;
	std::vector<char> m_Result2;
	std::vector<char> m_Result3;
public:
	void Resolve(Orgraph &g, char start, char end1, char end2);
	friend std::ostream& operator<<(std::ostream& os, Option& resolver);
};

