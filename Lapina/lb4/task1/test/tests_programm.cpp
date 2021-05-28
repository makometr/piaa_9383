#define CATCH_CONFIG_MAIN
#include "catch.hpp" 
#include "../source/lb4_1.hpp"

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
    std::string P =   "ab";
    std::string T =   "abab";
    std::vector <int> pi_ = create_pi(P);
    std::vector <int> check;
    check.push_back(0);
    check.push_back(2);
    CHECK(Alg_KMP(T, P, pi_) == check);   
    }

  SECTION("2 случай") { 
    std::string P =   "ab";
    std::string T =   "dasabdab";
    std::vector <int> pi_ = create_pi(P);
    std::vector <int> check;
    check.push_back(3);
    check.push_back(6);
    CHECK(Alg_KMP(T, P, pi_) == check);   
    }

  SECTION("3 случай") { //когда подстрока не найдена
    std::string P =   "qwe";
    std::string T =   "ababqknwegkrqe";
    std::vector <int> pi_ = create_pi(P);
    std::vector <int> check;
    CHECK(Alg_KMP(T, P, pi_) == check);   
    }

}


