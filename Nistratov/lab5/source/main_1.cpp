#include "lab5_1.hpp"

int main(){
    std::string text;
    std::cin >> text;
    AhoCorasick ak(text);
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++){
        std::string temp;
        std::cin >> temp;
        ak.addPattern(temp, i+1);
    }

    ak.createSuffixLinks();
    auto result = ak.find_ak();
    std::sort(result.begin(), result.end(), [](auto a, auto b){
        if (a.first != b.first){
            return a.first < b.first;
        }
        return a.second < b.second;
    });
    for (auto pos : result){
        std::cout << pos.first << ' ' << pos.second << std::endl;
    }
    return 0;
}