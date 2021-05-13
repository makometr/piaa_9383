#define CATCH_CONFIG_MAIN
#include "catch.hpp" 
#include "../source/lb4_2.hpp"

TEST_CASE("Тест для функции create_pi") {

  SECTION("1 случай") { 
    std::string P =   "ab";
    std::vector <int> check;
    check.push_back(0);
    check.push_back(0);
    CHECK(create_pi(P) == check);   
    }

  SECTION("2 случай") { 
    std::string P =   "abbaabbab";
    std::vector <int> check;
    check.push_back(0);
    check.push_back(0);
    check.push_back(0);
    check.push_back(1);
    check.push_back(1);
    check.push_back(2);
    check.push_back(3);
    check.push_back(4);
    check.push_back(2);
    CHECK(create_pi(P) == check);   
    }

  SECTION("3 случай") { 
    std::string P =   "efefeftef";
    std::vector <int> check;
    check.push_back(0);
    check.push_back(0);
    check.push_back(1);
    check.push_back(2);
    check.push_back(3);
    check.push_back(4);
    check.push_back(0);
    check.push_back(1);
    check.push_back(2);
    CHECK(create_pi(P) == check);   
    }
}

TEST_CASE("Тест для функции Alg_KMP") {

  SECTION("1 случай") { 
    std::string A =   "defabc";
    std::string B =   "abcdef";
    A = A+A;
    std::vector <int> pi_ = create_pi(B);
    std::vector <int> check;
    check.push_back(3);
    CHECK(Alg_KMP(A, B, pi_) == check);   
    }

  SECTION("1 случай") { 
    std::string A =   "yqwert";
    std::string B =   "qwerty";
    A = A+A;
    std::vector <int> pi_ = create_pi(B);
    std::vector <int> check;
    check.push_back(1);
    CHECK(Alg_KMP(A, B, pi_) == check);   
    }

  SECTION("3 случай") { //когда найдено несколько вариантов
    std::string P =   "abcdabc";
    std::string T =   "abcdabc";
    std::vector <int> pi_ = create_pi(P);
    std::vector <int> check;
    check.push_back(0);
    CHECK(Alg_KMP(T, P, pi_) == check);   
    }

  SECTION("4 случай") { //когда A не является циклическим сдвигом B
    std::string P =   "qweabc";
    std::string T =   "abcaew";
    std::vector <int> pi_ = create_pi(P);
    std::vector <int> check;
    CHECK(Alg_KMP(T, P, pi_) == check);   
    }
}


