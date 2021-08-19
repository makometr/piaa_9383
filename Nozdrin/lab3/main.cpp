#include <iostream>
#include "Solution.h"


int main() {
  Solution f;
  double res = f.mainAlgorithm();
  std::cout << res << '\n';
  f.printCapacity();
  return 0;
}