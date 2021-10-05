#ifndef LAB3_SOLUTION_H
#define LAB3_SOLUTION_H

#define COMMENTS 0

#include <iostream>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>

class Solution {
 public:
  Solution();
  static void printEdges(const std::map<char, double>& edges, const char& vertex);
  static void printFrontier(const std::queue<char>& f);
  void printCapacity();
  static bool isNewFrontier(const std::queue<char>& f, char v);
  void findPath();
  double mainAlgorithm();
 private:
  char start{}, end{};
  std::map<char, std::map<char, double>> edges, capacity;
  std::set<char> visited;
  std::vector<char> path;
};

#endif //LAB3_SOLUTION_H
