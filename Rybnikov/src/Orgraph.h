#pragma once
#include <iostream>
#include <vector>

class Orgraph
{
public:
	class Edge;
private:
	std::vector<Edge> m_Edges;
	int m_EdgesCount;
public:

	int EdgesCount() { return m_EdgesCount; }
	Edge& operator[](int index) { return m_Edges[index]; }
	std::vector<Edge> operator[](char node);	// возвращает все исходящие ребра из указанной вершины, причем все исходящие вершины сортируются
	void Set(Edge e);
	Edge& Get(char start, char end);				// получает ребро из графа
	void SetEdgesCount(int count);	// задает новое количество ребер

	std::vector<Edge>::iterator begin() { return m_Edges.begin(); }
	std::vector<Edge>::iterator end() { return m_Edges.end(); }

	friend std::istream& operator>>(std::istream& is, Orgraph& g);
	friend std::ostream& operator<<(std::ostream& os, Orgraph& g);
};

class Orgraph::Edge {
	char m_Start;		// откуда
	char m_End;			// куда 
	unsigned int m_W;	// вес
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
	const unsigned int W() { return m_W; }
	void SetW(unsigned int value) {
		m_W = value;
	}

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
