#define CATCH_CONFIG_MAIN
#include "catch.hpp" 
#include "../source/lb3.hpp"


TEST_CASE("Тест для функции dec_metric") {

  SECTION("1 случай") {      
    char start = 'a';
    char finish = 'd';
    Graph G = {{'a', {{'b', 3}, {'c', 5}}}, {'b', {{'d', 2}}}};

    dec_metric(G, "abd", 2);
    CHECK(G['a'][0].len() == 1);
    CHECK(G['a'][1].len() == 5);
    CHECK(G['b'][0].len() == 0);
    }

  SECTION("2 случай") {      
    char start = 'a';
    char finish = 'd';
    Graph G = {{'a', {{'b', 3}, {'c', 5}}}, {'b', {{'d', 2}}}, {'c', {{'e', 7}}}, {'e', {{'d', 20}}}};

    dec_metric(G, "aced", 5);
    CHECK(G['a'][0].len() == 3);
    CHECK(G['a'][1].len() == 0);
    CHECK(G['b'][0].len() == 2);
    CHECK(G['c'][0].len() == 2);
    CHECK(G['e'][0].len() == 15);
    }

  SECTION("3 случай") {      
    char start = '1';
    char finish = '3';
    Graph G = {{'1', {{'2', 10}, {'4', 5}}}, {'2', {{'3', 15}}}, {'4', {{'5', 7}}}, {'5', {{'6', 2}}}};

    dec_metric(G, "123", 10);
    CHECK(G['1'][0].len() == 0);
    CHECK(G['1'][1].len() == 5);
    CHECK(G['2'][0].len() == 5);
    CHECK(G['4'][0].len() == 7);
    CHECK(G['5'][0].len() == 2);
    }

}


TEST_CASE("Тест для функции Search_path") {

  SECTION("1 случай") {      
    char start = 'a';
    char finish = 'd';
    Graph G = {{'a', {{'b', 3}, {'c', 5}}}, {'b', {{'d', 2}}}};

    CHECK(Search_path(G, start, finish, "a") == "abd");
    }

  SECTION("2 случай") {      
    char start = 'a';
    char finish = 'd';
    Graph G = {{'a', {{'b', 3}, {'c', 5}}}, {'b', {{'d', 2}}}, {'c', {{'e', 7}}}, {'e', {{'d', 20}}}};

    CHECK(Search_path(G, start, finish, "a") == "abd");
    }

  SECTION("3 случай") {      
    char start = '1';
    char finish = '6';
    Graph G = {{'1', {{'2', 10}, {'4', 5}}}, {'2', {{'3', 15}}}, {'4', {{'5', 7}}}, {'5', {{'6', 2}}}};

    CHECK(Search_path(G, start, finish, "1") == "1456");
    }

}

TEST_CASE("Тест для функции Search_min") {

  SECTION("1 случай") {      
    char start = 'a';
    char finish = 'd';
    Graph G = {{'a', {{'b', 3}, {'c', 5}}}, {'b', {{'d', 2}}}};

    CHECK(Search_min("abd", G) == 2);
    }

  SECTION("2 случай") {      
    char start = 'a';
    char finish = 'd';
    Graph G = {{'a', {{'b', 3}, {'c', 5}}}, {'b', {{'d', 2}}}, {'c', {{'e', 7}}}, {'e', {{'d', 20}}}};

    CHECK(Search_min("aced", G) == 5);
    CHECK(Search_min("abd", G) == 2);
    }

  SECTION("3 случай") {      
    char start = '1';
    char finish = '3';
    Graph G = {{'1', {{'2', 10}, {'4', 5}}}, {'2', {{'3', 15}}}, {'4', {{'5', 7}}}, {'5', {{'6', 2}}}};

    CHECK(Search_min("123", G) == 10);
    CHECK(Search_min("1456", G) == 2);
    }

}


TEST_CASE("Тест для функции Check_v") {

  SECTION("1 случай") {      
    char start = 'a';
    char finish = 'd';
    Graph G = {{'a', {{'b', 3}, {'c', 5}}}, {'b', {{'d', 2}}}};

    CHECK(Check_v(G, 'a') == 1); 
    G['a'][0].dec(3);    //делаем длину ребер равной 0
    G['a'][1].dec(5);    //делаем длину ребер равной 0
    CHECK(Check_v(G, 'a') == 0);
    }

  SECTION("2 случай") {      
    char start = 'a';
    char finish = 'd';
    Graph G = {{'a', {{'b', 20}, {'c', 7}}}, {'b', {{'d', 2}}}, {'c', {{'e', 7}}}, {'e', {{'d', 20}}}};

    CHECK(Check_v(G, 'a') == 1); 
    G['a'][0].dec(20);    //делаем длину ребер равной 0
    G['a'][1].dec(7);     //делаем длину ребер равной 0
    CHECK(Check_v(G, 'a') == 0);
    }

}


TEST_CASE("Тест для функции Algoritm") {

  SECTION("1 случай") {      
    char start = 'a';
    char finish = 'd';
    Graph G = {{'a', {{'b', 3}, {'c', 5}}}, {'b', {{'d', 2}}}};

    CHECK(Algoritm(G, start, finish) == 2);

    }

  SECTION("2 случай") {      
    char start = 'a';
    char finish = 'd';
    Graph G = {{'a', {{'b', 20}, {'c', 7}}}, {'b', {{'d', 2}}}, {'c', {{'e', 7}}}, {'e', {{'d', 20}}}};

    CHECK(Algoritm(G, start, finish) == 9);

    }
  SECTION("3 случай") {      
    char start = 'a';
    char finish = 'f';
    Graph G = {{'a', {{'b', 7}, {'c', 6}}}, {'b', {{'d', 6}}}, {'c', {{'f', 9}}}, {'d', {{'e', 3}, {'f', 4}}}, {'e', {{'c', 2}  }}};

    CHECK(Algoritm(G, start, finish) == 12);

    }

}

