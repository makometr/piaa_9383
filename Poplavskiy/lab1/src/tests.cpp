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
            BOOST_REQUIRE(table.multiple_of_five(14) == true);
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
            Square table(18);
            BOOST_REQUIRE(table.insert_the_first_square() == 6);
        }
        catch (...) {
            std::cout << "Test 5 not OK" << std::endl;
            check = false;
        }
        if (check) {
            std::cout << "Test 5 OK" << std::endl;
        }
        else {
            check = true;
        }

        try {
            Square table(12);
            table.insert_square(11, 13, 5, 1);
        }
        catch (...) {
            std::cout << "Test 6 not OK" << std::endl;
            check = false;
        }
        if (check) {
            std::cout << "Test 6 OK" << std::endl;
        }
        else {
            check = true;
        }

        try {
            Square table(12);
            table.insert_square(3, 3, 2, 1);
            table.remove_square(14, 12, 3);
        }
        catch (...) {
            std::cout << "Test 7 not OK" << std::endl;
            check = false;
        }
        if (check) {
            std::cout << "Test 7 OK" << std::endl;
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
