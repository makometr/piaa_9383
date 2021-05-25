#include <iostream>
#include <vector>
#include <tuple>

#include "A.cpp"
//#include "greedy.cpp"

#define MODE 1

#if MODE == 1
int main() {
/**1 5
1 2 3.0
2 3 1.0
3 4 1.0
1 4 5.0
4 5 1.0*/
  int start, end;
  std::vector<std::tuple<int, int, float>> edges;
  AStar::readData(start, end, edges);
  std::cout << AStar::makePath(start, end, edges);
  return 0;
}
#elif MODE == 2
int main() {
  char  start, end;
  std::vector<std::tuple<char, char, float>> edges;
  Greedy::readData(start, end, edges);
  std::cout << Greedy::makePath(start, end, edges);
  return 0;
}
#else
int main() {
  return 0;
}
#endif // MODE
