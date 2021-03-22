#include "Square.h"
#include <boost/test/minimal.hpp>
#include <memory>

using namespace std;

class unitTest {
public:
    virtual void check() = 0;
};

class test : public unitTest {
public:
    void check() override {
        bool check = true;
        int size = 11;
        Square table(size);
        try {
            BOOST_REQUIRE(table.even_square(18) == true);
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
            BOOST_REQUIRE(table.insert_the_third_square() == true);
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
            BOOST_REQUIRE(table.insert_the_second_square() == true);
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
            BOOST_REQUIRE(table.multiple_of_five() == true);
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

        try {
            BOOST_REQUIRE(table.multiple_of_five(15) == true);
        }
        catch (...) {
            std::cout << "Test 5 not OK" << std::endl;
            check = false;
        }
        if (check) {
            std::cout << "Test 5 OK" << std::endl;
        }
    }

};
