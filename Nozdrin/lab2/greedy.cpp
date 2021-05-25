#include <iostream>
#include <vector>
#include <tuple>

namespace Greedy {
  std::tuple<char, char, float> readEdge(std::string);

  void readData(char &, char &, std::vector<std::tuple<char, char, float>> &);

  __attribute__((unused)) void printData(char &, char &, std::vector<std::tuple<char, char, float>> &);

  std::tuple<char, char, float> *getVerticeGreedy(char, const std::vector<std::tuple<char, char, float>> &);

  std::string makePath(char, char, std::vector<std::tuple<char, char, float>>);
}

std::tuple<char,char,float> Greedy::readEdge(std::string edge) {
  char  v1  = edge[0],
      v2  = edge[2];
  float len = stof(edge.substr(4));
  return std::make_tuple(v1, v2, len);
}

void Greedy::readData(char& start, char& end, std::vector<std::tuple<char, char, float>>& edges) {
  std::string edge;
  std::getline(std::cin, edge);
  start = edge[0];
  end   = edge[2];
  do {
    std::getline(std::cin, edge);
    if (!std::cin)
      break;
    if (edge.length() >= 5)
      edges.emplace_back(readEdge(edge));
    else
      break;
  } while (std::cin);
}

__attribute__((unused)) void Greedy::printData(char& start, char& end, std::vector<std::tuple<char, char, float>>& edges) {
  std::cout << start << ' ' << end << '\n';
  for (auto i : edges)
    std::cout << std::get<0>(i) << ' ' << std::get<1>(i) << ' ' << std::get<2>(i) << '\n';
}

std::tuple<char,char,float>* Greedy::getVerticeGreedy(char start, const std::vector<std::tuple<char,char,float>>& edges) {
  std::tuple<char, char, float> *min = nullptr;
  for (auto i: edges) {
    if (std::get<0>(i) == start) {
      if (!min) {
        min = new std::tuple<char, char, float>();
        *min = i;
      }
      if (std::get<2>(*min) > std::get<2>(i))
        *min = i;
    }
  }
  return min;
}

std::string Greedy::makePath(char start, char end, std::vector<std::tuple<char, char, float>> edges) {
  std::string result, errorMsg = "ERROR:\tNO PATH";
  while (true) {
    result += start;
    if (start == end)
      return result;
    if (edges.empty())
      return errorMsg;

    std::tuple<char,char,float> *min = getVerticeGreedy(start, edges);
    if (!min) {
      result.erase(result.size() - 1);
      start = result[result.size() - 1];
      result.erase(result.size() - 1);
      continue;
    }

    start = std::get<1>(*min);
    for (int i = 0; i < edges.size(); i++)
      if (std::get<1>(edges[i]) == start) {
        edges.erase(edges.begin() + i);
        i--;
      }
  }
}
