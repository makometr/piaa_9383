#include <iostream>

#include "kmp.hpp"

int main(int argc, char** argv) {

    int task = -1;

    for(int i = 0; i < argc; ++i) {
        if(std::string(argv[i]) == "-kmp") {
            task = 1;
            break;
        }

        else if(std::string(argv[i]) == "-cycle") {
            task = 2;
            break;
        }

        else if(std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help") {
            task = 0;
            break;
        }
    }

    if(task == -1) {
        std::cout << "You have to specialize the task: either choose KMP or Cycle Check.\nTo get more info use key -h or --help.\n";
        return 0;
    }
    else if(task == 0) {
        std::cout << "Use -kmp to start Knuth–Morris–Pratt Algorithm\n";
        std::cout << "Use -cycle to check if a string is a cycle shift of another one\n";
        return 0;
    }

    std::string pattern, temp;

    if(!read_strings(pattern, temp, std::cin)) {
        std::cout << "You've entered empty string\n";
        return 0;
    }

    if(task == 1) {
        std::vector<int> res = kmp(pattern, temp, false);
        print_vector(res);
        return 0;
    }
    else {
        std::cout << check_cycle(pattern, temp) << '\n';
        return 0;
    }

    return 0;
}