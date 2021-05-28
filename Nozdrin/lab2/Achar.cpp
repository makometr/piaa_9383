#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

namespace AChar {
  /// Input/output functions
  std::vector<std::string> split(std::string&, std::vector<std::string>&);
  std::tuple<char, char, float> readEdge(std::string);
  void readData(char&, char&, std::vector<std::tuple<char, char, float>>&);
  void printData(char&, char&, std::vector<std::tuple<char, char, float>>&);
  /// Realisation
  int heuristicFunction(const char&, const char&);
  class Vertex {
   public:
    char name;
    int route_prev;
    float f, g, h;

    Vertex(char name, float g, char end) : name(name), g(g), route_prev(-1) {
      h = (float) heuristicFunction(name, end);
      f = g + h;
    }

    friend bool operator<=(const Vertex &a, const Vertex &b) {
      return a.f <= b.f;
    }

    friend bool operator>=(const Vertex &a, const Vertex &b) {
      return a.f >= b.f;
    }

    friend bool operator==(const Vertex &a, const Vertex &b) {
      return a.name == b.name;
    }
  };
  bool belongs(char, const std::vector<char>&);
  void addToQueue(Vertex&, char&, const std::vector<std::tuple<char, char, float>>&, std::vector<Vertex>&, std::priority_queue<Vertex,std::vector<Vertex>,
                  std::greater_equal<Vertex>>&, std::vector<char>&);
  std::string makePath(char, char, const std::vector<std::tuple<char, char, float>>&);
}

std::vector<std::string> AChar::split(std::string &str, std::vector<std::string> &result) {
  for (int i = 0, j = 0; j < str.size(); j++) {
    if (str[j] == ' ' || str[j] == '\n') {
      result.emplace_back(str.substr(i, j - i));
      i = j + 1;
    } else if (j == str.size() - 1)
      result.emplace_back(str.substr(i));
  }
  return result;
}

std::tuple<char, char, float> AChar::readEdge(std::string edge) {
  std::vector<std::string> vec;
  split(edge, vec);
  char v1 = vec[0][0];
  char v2 = vec[1][0];
  float len = stof(vec[2]);
  return std::make_tuple(v1, v2, len);
}

void AChar::readData(char &start, char &end, std::vector<std::tuple<char, char, float>> &edges) {
  std::string edge;

  std::getline(std::cin, edge);
  std::vector<std::string> vec;
  split(edge, vec);

  start = vec[0][0];
  end = vec[1][0];

  do {
    std::getline(std::cin, edge);
    if (!std::cin)
      break;
    int c = 0;
    for (auto x: edge)
      if (x == ' ')
        c++;
    if (c == 2)
      edges.emplace_back(readEdge(edge));
    else
      break;
  } while (std::cin);
}

void AChar::printData(char &start, char &end, std::vector<std::tuple<char, char, float>> &edges) {
  std::cout << start << ' ' << end << '\n';
  for (auto i : edges)
    std::cout << std::get<0>(i) << ' ' << std::get<1>(i) << ' ' << std::get<2>(i) << '\n';
}

int AChar::heuristicFunction(const char &v, const char &u) {
  return abs((int)v - (int)u);
}

bool AChar::belongs(char name, const std::vector<char> &close) {
  return std::any_of(close.cbegin(), close.cend(), [name](char x) { return x == name; });
}

void AChar::addToQueue(Vertex &cur, char &end, const std::vector<std::tuple<char, char, float>> &edges,
                       std::vector<Vertex>&                                                  vertices,
                       std::priority_queue<Vertex,std::vector<Vertex>,std::greater_equal<Vertex>>& open,
                       std::vector<char>&                                                     close) {
  for (const auto &edge : edges) {
    if (cur.name == std::get<0>(edge)) {
      if (belongs(std::get<1>(edge), close))
        continue;
      Vertex x(std::get<1>(edge), std::get<2>(edge) + cur.g, end);
      x.route_prev = (int) vertices.size() - 1;
      open.push(x);
    }
  }
}

std::string AChar::makePath(char start, char end, const std::vector<std::tuple<char, char, float>>& edges) {
  std::string result, errorMsg = "ERROR:\tNO PATH";

  std::vector<Vertex> vertices;
  std::priority_queue<Vertex, std::vector<Vertex>, std::greater_equal<Vertex>> open;
  std::vector<char> close;

  Vertex cur(start, 0, 0);
  open.push(cur);

  while (cur.name != end && !open.empty()) {
    cur = open.top();
    open.pop();
    if (belongs(cur.name, close))
      continue;
    vertices.push_back(cur);
    addToQueue(cur, end, edges, vertices, open, close);
  }

  if (open.empty())
    return errorMsg;

  // restore the path
  // cur == end
  std::string res1;
  std::string res2;
  std::vector<char> res;
  while (true) {
    if (cur.route_prev == -1) {
      res1 += cur.name;
      res.push_back(cur.name);
      break;
    }
    res.push_back(cur.name);
    res1 += cur.name;
    cur = vertices[cur.route_prev];
  }

  for (auto x = res1.rbegin(); x != res1.rend(); ++x)
    res2 += *x;

//  for (int i = (int)(res.size()) - 1; i >= 0; i--)
//    result += res[i] + ' ';

  return res2;
}
