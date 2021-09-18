#include <iostream>
#include "Squaring.h"

int main() {
  int N;
  if ((std::cin >> N) && (N >=2)) {
    Squaring squaring(N);
    squaring.run();
  } else {
    std::cout << "Bad input. (enter N >= 2)\n";
  }
  return 0;
}
