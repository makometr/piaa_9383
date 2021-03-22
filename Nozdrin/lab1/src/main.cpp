#include <iostream>
#include "Squaring.h"

int main() {
  int N;
  std::cin >> N;
  Squaring squaring(N);
  squaring.run();
  return 0;
}
