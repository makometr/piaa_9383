#define CATCH_CONFIG_MAIN
#include "catch.hpp" 
#include "../source/lb2.hpp"
TEST_CASE("Тест для эвристической функции h") {
  SECTION("Сравниваем, когда finish == finish") {
    REQUIRE(h('a', 'a') == 0); 
    REQUIRE(h('n', 'n') == 0); 
    REQUIRE(h('w', 'w') == 0); 
    REQUIRE(h('z', 'z') == 0); 
  }

  SECTION("Средний случай при вводе finish>start") {
    REQUIRE(h('a', 'z') == 25); 
    REQUIRE(h('b', 'z') == 24); 
    REQUIRE(h('n', 'r') == 4); 
    REQUIRE(h('c', 'd') == 1); 
    REQUIRE(h('f', 'i') == 3); 
    REQUIRE(h('x', 'z') == 2); 
    REQUIRE(h('d', 'y') == 21); 
    REQUIRE(h('d', 'w') == 19); 
  }

  SECTION("При вводе start>finish (не должно ломаться, тк используем модуль)") {
    REQUIRE(h('z', 'a') == 25); 
    REQUIRE(h('z', 'b') == 24); 
    REQUIRE(h('r', 'n') == 4); 
    REQUIRE(h('d', 'c') == 1); 
  }

  SECTION("Если вершины не типа char, а типа int/float") {
    REQUIRE(h(98, 122) == 24); 
    REQUIRE(h(100, 118) == 18); 
    REQUIRE(h(100.8, 122.5) == 22); 
    REQUIRE(h(99.1, 100.2) == 1); 
  }

}

TEST_CASE("Тест для функции Algoritm_A") {

  SECTION("1 случай") {      
    float priority = 0;
    char start = 'a';
    char finish = 'e';
    Graph G = {{'a', {{'b', 3.0}, {'d', 5.0}}}, {'b', {{'v', 1.0}}}, {'c',{{'d', 1.0}}}, {'d',{{'e', 1.0}}}};

    std::string result = Algoritm_A(priority, start, finish, G);
    CHECK(priority!=0);
    CHECK(priority==6);
    CHECK(result=="ade");
    }

  SECTION("2 случай") {      
    float priority = 0;
    char start = 'a';
    char finish = 'z';
    Graph G = {{'a', {{'w', 17}, {'b', 1}}}, {'b', {{'w', 1}}}, {'w',{{'x', 1}}}, {'x',{{'y', 18}}}, {'y',{{'z', 1}}}};

    std::string result = Algoritm_A(priority, start, finish, G);
    CHECK(priority!=0);
    CHECK(priority==22);
    CHECK(result=="abwxyz");
    }

  SECTION("3 случай") {      
    float priority = 0;
    char start = 'b';
    char finish = 'e';
    Graph G = {{'b', {{'c', 1}, {'d', 5}}}, {'c', {{'e', 100}}}, {'d',{{'e', 10}}}};

    std::string result = Algoritm_A(priority, start, finish, G);
    CHECK(priority!=0);
    CHECK(priority==15);
    CHECK(result=="bde");
    }
}

