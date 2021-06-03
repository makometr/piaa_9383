#include "lab5_2.hpp"

int main(){
    std::string text, pattern;
    std::cin >> text >> pattern;
    AhoCorasick ak(text, pattern);
    char joker;
    std::cin >> joker;
    ak.split_by_joker(joker);
    ak.createSuffixLinks();
    auto result = ak.find_ak();
    for (auto i : result){
        std::cout << i << std::endl;
    } 
    return 0;
}