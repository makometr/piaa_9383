#include "piaa4_2.hpp"
#include <boost/test/minimal.hpp>
#include <memory>
#include <cstdio>


class unitTest {
public:
    virtual void check() = 0;
};

class test : public unitTest {
public:
    void check() override {
        bool check = true;
        try {
            std::string form;
            std::string line;
            freopen("data_tests_1.txt", "r", stdin);
            getline(std::cin, form);
            getline(std::cin, line);
            int res = CYCLE_KMP(form, line);
            BOOST_REQUIRE(res == 3);
        }
        catch (...) {
            std::cout << "Test 1 not OK" << std::endl;
            check = false;
        }
        if (check) {
            std::cout << "Test 1 OK" << std::endl;
        }
        else {
            check = true;
        }

        try {
            std::string form;
            std::string line;
            freopen("data_tests_2.txt", "r", stdin);
            getline(std::cin, form);
            getline(std::cin, line);
            int res = CYCLE_KMP(form, line);
            BOOST_REQUIRE(res == -1);
        }
        catch (...) {
            std::cout << "Test 2 not OK" << std::endl;
            check = false;
        }
        if (check) {
            std::cout << "Test 2 OK" << std::endl;
        }
        else {
            check = true;
        }

        try {
            std::string form;
            std::string line;
            freopen("data_tests_3.txt", "r", stdin);
            getline(std::cin, form);
            getline(std::cin, line);
            int res = CYCLE_KMP(form, line);
            BOOST_REQUIRE(res == -1);
        }
        catch (...) {
            std::cout << "Test 3 not OK" << std::endl;
            check = false;
        }
        if (check) {
            std::cout << "Test 3 OK" << std::endl;
        }
    }

};

int test_main()
{
    test untest;
    untest.check();
    return 0;
}