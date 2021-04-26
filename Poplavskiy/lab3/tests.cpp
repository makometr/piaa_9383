#include "ford_falk.h"
//#include <boost/test/minimal.hpp>
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
            Ford_Falkerson ford_1(0, '\0');
            freopen("data_tests_1.txt", "r", stdin);
            ford_1.creation_graph();
            std::cout << ford_1.alg_ff();
            BOOST_REQUIRE(ford_1.alg_ff() == 12);
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
            Ford_Falkerson ford_2(0, '\0');
            freopen("data_tests_2.txt", "r", stdin);
            ford_2.creation_graph();
            std::cout << ford_1.alg_ff();
            BOOST_REQUIRE(ford_1.alg_ff() == 3);
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
            Ford_Falkerson ford_3(0, '\0');
            freopen("data_tests_3.txt", "r", stdin);
            ford_3.creation_graph();
            std::cout << ford_3.alg_ff();
            BOOST_REQUIRE(ford_3.alg_ff() == 4);
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