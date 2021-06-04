#include "piaa5_1.hpp"
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
            init_bohr();
            std::string text;
            std::string n;
            freopen("data_tests_1.txt", "r", stdin);
            getline(std::cin, text);
            getline(std::cin, n);
            for (int i = 0; i < std::stoi(n); i++) {
                std::string temp;
                getline(std::cin, temp);
                add_string_to_bohr(temp);
            }
            auto res = find_all_pos(text);
            BOOST_REQUIRE(res[0].first == 2);
            BOOST_REQUIRE(res[0].second == 2);
            BOOST_REQUIRE(res[1].first == 2);
            BOOST_REQUIRE(res[1].second == 3);
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
            init_bohr();
            std::string text;
            std::string n;
            freopen("data_tests_2.txt", "r", stdin);
            getline(std::cin, text);
            getline(std::cin, n);
            for (int i = 0; i < std::stoi(n); i++) {
                std::string temp;
                getline(std::cin, temp);
                add_string_to_bohr(temp);
            }
            auto res = find_all_pos(text);
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
            init_bohr();
            std::string text;
            std::string n;
            freopen("data_tests_2.txt", "r", stdin);
            getline(std::cin, text);
            getline(std::cin, n);
            for (int i = 0; i < std::stoi(n); i++) {
                std::string temp;
                getline(std::cin, temp);
                add_string_to_bohr(temp);
            }
            auto res = find_all_pos(text);
            BOOST_REQUIRE(res.size() == 0);
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
    }

};

int test_main()
{
    test untest;
    untest.check();
    return 0;
}
