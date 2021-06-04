#include "piaa4_1.hpp"
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
            std::vector <int> res = KMP(form, line);
            BOOST_REQUIRE(res[0] == 0);
            BOOST_REQUIRE(res[1] == 3);
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
            std::vector <int> res = KMP(form, line);
            BOOST_REQUIRE(res.size() == 0);
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
            std::string line;
            freopen("data_tests_3.txt", "r", stdin);
            getline(std::cin, line);
            std::vector <int> res = prefix(line);
            BOOST_REQUIRE(res.size() == 7);
            BOOST_REQUIRE(res[4] == 1);
            int sum = 0;
            for (int i = 0; i < res.size(); i++)
            {
                sum += res[i];
            }
            BOOST_REQUIRE(sum == 1);
        }
        catch (...) {
            std::cout << "Test 3 not OK" << std::endl;
            check = false;
        }
        if (check) {
            std::cout << "Test 3 OK" << std::endl;
        }
        else {
            check = true;
        }

        try {
            std::string form;
            std::string line;
            freopen("data_tests_4.txt", "r", stdin);
            getline(std::cin, form);
            getline(std::cin, line);
            std::vector <int> res = KMP(form, line);
            BOOST_REQUIRE(res[0] == 0);
        }
        catch (...) {
            std::cout << "Test 4 not OK" << std::endl;
            check = false;
        }
        if (check) {
            std::cout << "Test 4 OK" << std::endl;
        }
        else {
            check = true;
        }
    }

};

int test_main()
{
    test untest;
    untest.check();
    return 0;
}