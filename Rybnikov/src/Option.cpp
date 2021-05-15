#include "Option.h"
#include "AStar.h"

std::ostream& operator<<(std::ostream& os, Option& resolver)
{
	if (resolver.m_Result1.size() == 0 &&
		resolver.m_Result2.size() == 0 &&
		resolver.m_Result3.size() == 0)
		return os << "Option has no result";

	os << "start to end1: ";
	for (auto i : resolver.m_Result1) os << i;
	os << std::endl;
	os << "start to end2: ";
	for (auto i : resolver.m_Result2) os << i;
	os << std::endl;
	os << "end1 to end2: ";
	for (auto i : resolver.m_Result3) os << i;
	os << std::endl;
	return os;
}

void Option::Resolve(Orgraph& g, char start, char end1, char end2)
{
    AStar res;

	m_Result1.clear();
	m_Result2.clear();
	m_Result3.clear();

	// ищем решение от начала до первого конца
	res.Resolve(g, start, end1);
	// пишем решение без 1 элемента
	int n = 0;
	for (auto i : res) {
		if (n++ == 0) continue;
		m_Result1.push_back(i.End());
	}

	res.Resolve(g, start, end2);
	for (auto i : res) m_Result2.push_back(i.End());	

	res.Resolve(g, end1, end2);
	for (auto i : res) m_Result3.push_back(i.End());	
}
