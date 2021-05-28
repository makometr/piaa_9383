#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

namespace AStar {
  /// Input/output functions
  std::vector<std::string> split(std::string&, std::vector<std::string>&);
  std::tuple<int, int, float> readEdge(std::string);
  void readData(int&, int&, std::vector<std::tuple<int, int, float>>&);
  void printData(int&, int&, std::vector<std::tuple<int, int, float>>&);
  /// Realisation
  int heuristicFunction(const int&, const int&);
  class Vertex {
   public:
    int name, route_prev;
    float f, g, h;

    Vertex(int name, float g, int end) : name(name), g(g), route_prev(-1) {
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
  bool belongs(int, const std::vector<int>&);
  void addToQueue(Vertex&, int&, const std::vector<std::tuple<int, int, float>>&, std::vector<Vertex>&, std::priority_queue<Vertex,std::vector<Vertex>,
                  std::greater_equal<>>&, std::vector<int>&);
  std::string makePath(int, int, const std::vector<std::tuple<int, int, float>>&);
}

std::vector<std::string> AStar::split(std::string &str, std::vector<std::string> &result) {
  for (int i = 0, j = 0; j < str.size(); j++) {
    if (str[j] == ' ' || str[j] == '\n') {
      result.emplace_back(str.substr(i, j - i));
      i = j + 1;
    } else if (j == str.size() - 1)
      result.emplace_back(str.substr(i));
  }
  return result;
}

std::tuple<int, int, float> AStar::readEdge(std::string edge) {
  std::vector<std::string> vec;
  split(edge, vec);
  int v1 = stoi(vec[0]);
  int v2 = stoi(vec[1]);
  float len = stof(vec[2]);
  return std::make_tuple(v1, v2, len);
}

void AStar::readData(int &start, int &end, std::vector<std::tuple<int, int, float>> &edges) {
  std::string edge;

  std::getline(std::cin, edge);
  std::vector<std::string> vec;
  split(edge, vec);

  start = stoi(vec[0]);
  end = stoi(vec[1]);

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

void AStar::printData(int &start, int &end, std::vector<std::tuple<int, int, float>> &edges) {
  std::cout << start << ' ' << end << '\n';
  for (auto i : edges)
    std::cout << std::get<0>(i) << ' ' << std::get<1>(i) << ' ' << std::get<2>(i) << '\n';
}

int AStar::heuristicFunction(const int &v, const int &u) {
  return abs(v - u);
}

bool AStar::belongs(int name, const std::vector<int> &close) {
  return std::any_of(close.cbegin(), close.cend(), [name](auto x) { return x == name; });
}

void AStar::addToQueue(Vertex &cur, int &end, const std::vector<std::tuple<int, int, float>> &edges,
                       std::vector<Vertex>&                                                  vertices,
                       std::priority_queue<Vertex,std::vector<Vertex>,std::greater_equal<>>& open,
                       std::vector<int>&                                                     close) {
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

std::string AStar::makePath(int start, int end, const std::vector<std::tuple<int, int, float>>& edges) {
  std::string result, errorMsg = "ERROR:\tNO PATH";

  std::vector<Vertex> vertices;
  std::priority_queue<Vertex, std::vector<Vertex>, std::greater_equal<>> open;
  std::vector<int> close;

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
  std::vector<int> res;
  while (true) {
    if (cur.route_prev == -1) {
      res.push_back(cur.name);
      break;
    }
    res.push_back(cur.name);
    cur = vertices[cur.route_prev];
  }

  for (int i = (int)(res.size()) - 1; i >= 0; i--)
    result += std::to_string(res[i]) + ' ';

  return result;
}
