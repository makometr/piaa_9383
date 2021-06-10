#include "piaa5_2.hpp"
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
            std::string text;
            std::string temp;
            std::string joker;
            std::string pat;
            std::vector<std::string> patterns;
            std::vector<int> patterns_pos;
            freopen("data_tests_1.txt", "r", stdin);
            getline(std::cin, text);
            getline(std::cin, temp);
            getline(std::cin, joker);
            for (int i = 0; i < temp.length(); i++) {
                if (temp[i] != joker[0]) {
                    patterns_pos.push_back(i + 1);
                    for (int j = i; temp[j] != joker[0] && j != temp.length(); j++) {
                        pat += temp[j];
                        i++;
                    }
                    add_string_to_bohr(pat);
                    patterns.push_back(pat);
                    pat.clear();
                }
            }
            BOOST_REQUIRE(patterns[0] == "A");
            BOOST_REQUIRE(patterns[1] == "A");
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
            std::string text;
            std::string temp;
            std::string joker;
            std::string pat;
            std::vector<std::string> patterns;
            std::vector<int> patterns_pos;
            freopen("data_tests_2.txt", "r", stdin);
            getline(std::cin, text);
            getline(std::cin, temp);
            getline(std::cin, joker);
            for (int i = 0; i < temp.length(); i++) {
                if (temp[i] != joker[0]) {
                    patterns_pos.push_back(i + 1);
                    for (int j = i; temp[j] != joker[0] && j != temp.length(); j++) {
                        pat += temp[j];
                        i++;
                    }
                    add_string_to_bohr(pat);
                    patterns.push_back(pat);
                    pat.clear();
                }
            }
            int arr[10];
            int n = 0;
            std::vector<int> c(text.length(), 0);
            for (int i = 0; i < num.size(); i++) {
                if (num[i].index < patterns_pos[num[i].pattern_num] - 1) {    
                    continue;
                }
                c[num[i].index - patterns_pos[num[i].pattern_num] + 1]++;
                if (c[num[i].index - patterns_pos[num[i].pattern_num] + 1] == patterns.size() && 
                    num[i].index - patterns_pos[num[i].pattern_num] + 1 <= text.length() - temp.length()) {
                    arr[n] = num[i].index - patterns_pos[num[i].pattern_num] + 2;
                    n++;
                }

            }
            BOOST_REQUIRE(arr[0] == 1);
            BOOST_REQUIRE(arr[1] == 4);
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
            std::string text;
            std::string temp;
            std::string joker;
            std::string pat;
            std::vector<std::string> patterns;
            std::vector<int> patterns_pos;
            freopen("data_tests_2.txt", "r", stdin);
            getline(std::cin, text);
            getline(std::cin, temp);
            getline(std::cin, joker);
            for (int i = 0; i < temp.length(); i++) {
                if (temp[i] != joker[0]) {
                    patterns_pos.push_back(i + 1);
                    for (int j = i; temp[j] != joker[0] && j != temp.length(); j++) {
                        pat += temp[j];
                        i++;
                    }
                    add_string_to_bohr(pat);
                    patterns.push_back(pat);
                    pat.clear();
                }
            }
            int arr[10];
            int n = 0;
            std::vector<int> c(text.length(), 0);
            for (int i = 0; i < num.size(); i++) {
                if (num[i].index < patterns_pos[num[i].pattern_num] - 1) {
                    continue;
                }
                c[num[i].index - patterns_pos[num[i].pattern_num] + 1]++;
                if (c[num[i].index - patterns_pos[num[i].pattern_num] + 1] == patterns.size() &&
                    num[i].index - patterns_pos[num[i].pattern_num] + 1 <= text.length() - temp.length()) {
                    arr[n] = num[i].index - patterns_pos[num[i].pattern_num] + 2;
                    n++;
                }

            }
            BOOST_REQUIRE(arr[0] == 1);
            BOOST_REQUIRE(arr[1] == 4);
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
            std::string text;
            std::string temp;
            std::string joker;
            std::string pat;
            std::vector<std::string> patterns;
            std::vector<int> patterns_pos;
            freopen("data_tests_3.txt", "r", stdin);
            getline(std::cin, text);
            getline(std::cin, temp);
            getline(std::cin, joker);
            for (int i = 0; i < temp.length(); i++) {
                if (temp[i] != joker[0]) {
                    patterns_pos.push_back(i + 1);
                    for (int j = i; temp[j] != joker[0] && j != temp.length(); j++) {
                        pat += temp[j];
                        i++;
                    }
                    add_string_to_bohr(pat);
                    patterns.push_back(pat);
                    pat.clear();
                }
            }
            int arr[10];
            int n = 0;
            std::vector<int> c(text.length(), 0);
            for (int i = 0; i < num.size(); i++) {
                if (num[i].index < patterns_pos[num[i].pattern_num] - 1) {
                    continue;
                }
                c[num[i].index - patterns_pos[num[i].pattern_num] + 1]++;
                if (c[num[i].index - patterns_pos[num[i].pattern_num] + 1] == patterns.size() &&
                    num[i].index - patterns_pos[num[i].pattern_num] + 1 <= text.length() - temp.length()) {
                    arr[n] = num[i].index - patterns_pos[num[i].pattern_num] + 2;
                    n++;
                }

            }
            BOOST_REQUIRE(arr.size() == 0);
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