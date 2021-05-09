#include "Edge.h"


char Edge::From() {
	return _From;
}
char Edge::To() {
	return _To;
}
double Edge::Weight() {
	return _Weight;
}

std::istream& operator>>(std::istream& is, Edge& e) {
	return is >> e._From >> e._To >> e._Weight;
}
std::ostream& operator<<(std::ostream& os, Edge& e) {
	return os << e._From << "->" << e._To << ": " << e._Weight;
}
bool operator<(const Edge& a, const Edge& b) {
	return a._Weight < b._Weight;
}
bool operator>(const Edge& a, const Edge& b) {
	return a._Weight > b._Weight;
}
Edge::Edge() {
	_From = 0;
	_To = 0;
	_Weight = 0;
}
Edge::Edge(char from, char to, double weight) {
	_From = from;
	_To = to;
	_Weight = weight;
}