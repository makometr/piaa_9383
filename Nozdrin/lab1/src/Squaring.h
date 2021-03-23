#ifndef SQUARING_H
#define SQUARING_H

#include <iostream>
#include <vector>
#include <stack>
#include <utility>

struct Square {
    int m_x = 0;
    int m_y = 0;
    int m_size = 0;
    Square(int x, int y, int size): m_x(x), m_y(y), m_size(size) {};
};

class Squaring {
 public:
  explicit Squaring(int size);
  int getMaxSquareSize(int i, int j);
  bool placeSquare(int i, int j, int size=0);
  void baseCase1();
  void baseCase2();
  void eval();
  void printResult();
  void printSquares(const std::stack<Square>&) const;
  friend std::ostream& operator<<(std::ostream& os, Squaring& squaring);
  bool complete();
  void pop();
  bool backtrack();
  void run();

  std::vector<std::vector<int>> getCurrentSquaring();
  void setCurrentSquaring(std::vector<std::vector<int>> squaring);
  [[nodiscard]] int getCounter() const;

 private:
  int                           m_size;
  std::vector<std::vector<int>> m_current;
  std::vector<std::vector<int>> m_best;
  int                           m_counter = 0;
  int                           m_minimalSquaring = 0;
  std::stack<Square>            m_squares;
  std::stack<Square>            m_squares_best;
  int                           multiplier = 1;
};

#endif // SQUARING_H
