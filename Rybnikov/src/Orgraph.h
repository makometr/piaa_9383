#pragma once
#include <iostream>
#include <vector>

class Orgraph
{
public:
	class Edge;
private:
	char m_Start = 0;
	char m_End = 0;
	std::vector<Edge> m_Edges;
public:

	char Start() { return m_Start; }
	char End() { return m_End; }

	Edge& operator[](int index) { return m_Edges[index]; } // возвращает ребро по его индексу
	std::vector<Edge> operator[](char node);	// возвращает все исходящие ребра из указанной вершины, причем все исходящие вершины сортируются

	friend std::istream& operator>>(std::istream& is, Orgraph& g);
	friend std::ostream& operator<<(std::ostream& os, Orgraph& g);
};

class Orgraph::Edge {
	char m_Start;	// откуда
	char m_End;		// куда 
	float m_W;		// вес
public:
	Edge() {
		m_Start = 0;
		m_End = 0;
		m_W = 0;
	}
	Edge(char start, char end, float w) {
		this->m_Start = start;
		this->m_End = end;
		this->m_W = w;
	}

	const char Start() { return m_Start; }
	const char End() { return m_End; }
	const float W() { return m_W; }

	friend std::istream& operator>>(std::istream& is, Edge& e);
	friend std::ostream& operator<<(std::ostream& os, Edge& e);
	friend bool operator<(const Orgraph::Edge& e1, const Orgraph::Edge& e2);
	friend bool operator>(const Orgraph::Edge& e1, const Orgraph::Edge& e2);
};

inline bool operator<(const Orgraph::Edge& e1, const Orgraph::Edge& e2) {
	return e1.m_W < e2.m_W;
}
inline bool operator>(const Orgraph::Edge& e1, const Orgraph::Edge& e2) {
	return e1.m_W > e2.m_W;
}