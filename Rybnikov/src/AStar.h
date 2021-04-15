#pragma once
#include <list>
#include "Orgraph.h"

class AStar
{
private:
	struct QueueData {
	public:
		char Node;
		int Priority;
		
		QueueData() {}
		QueueData(char node, char priority) {
			this->Node = node;
			this->Priority = priority;
		}

		friend bool operator<(QueueData d1, QueueData d2) { return d1.Priority < d2.Priority; }
		friend bool operator>(QueueData d1, QueueData d2) { return d1.Priority > d2.Priority; }
	};

	std::list<Orgraph::Edge> m_Result;
	Orgraph m_Graph;
	char m_Start;
	char m_End;
	float Weight(std::vector<Orgraph::Edge> path);

	int Heuristic(char point) { return abs(point - m_End); }
public:
	void Resolve(Orgraph g, char start, char end);	
	friend std::ostream& operator<<(std::ostream& os, AStar r);

	std::list<Orgraph::Edge>::iterator begin() { return m_Result.begin(); }
	std::list<Orgraph::Edge>::iterator end() { return m_Result.end(); }
};

