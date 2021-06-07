#include "Bohr.hpp"

#define RES_2

#ifdef RES_1
Bohr Read(Bohr &resolve, std::string &text, std::string &pattern, int &n){
    std::cin >> text;
    std::cin >> n;
    for(int i = 0; i < n; i++){
        std::cin >> pattern;
        resolve.AddInBohr(pattern);
    }
    return resolve;
}
#endif

int main(int argc, const char * argv[]) {
#ifdef RES_1
    int n;
    Bohr resolve;

    std::string text;
    std::string pattern;

    resolve = Read(resolve, text, pattern, n);
    resolve.AhoK(text);
#endif
    
#ifdef RES_2
    Bohr resolveJoker;
    resolveJoker.Init();
#endif
    return 0;
}
