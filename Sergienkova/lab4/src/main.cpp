#include <iostream>
#include <vector>
#include <string>

#define RES
//#define RES2

std::vector<int> Prefix(const std::string &myText){
    int n = myText.length();
    std::vector<int> pi(myText.length(), 0);
    
    for(size_t i = 1; i < n; ++i){
        size_t j = pi[i - 1];
        while(j > 0 && myText[i] != myText[j]){
            j = pi[j - 1];
        }
        if(myText[i] == myText[j]){
            pi[i] = j + 1;
        }
        else{
            pi[i] = j;
        }
    }
    return pi;
}


std::vector<int> KMPForTask1(const std::string &myText, const std::string &myString){
    if(myText.empty() || myString.empty()) throw -1;
    std::vector<int> result;
    std::string currStr = myString + '#' + myText;
    std::vector<int> pi = Prefix(currStr);
    
    const int LenText = myText.length();
    const int LenStr = myString.length();
    
    for(int i = 0; i < LenText; ++i){
        if(pi[LenStr + 1 + i] == LenStr)
            result.push_back(i - LenStr + 1);
    }
    
    if(result.empty())
        result.push_back(-1);
    return result;
}

std::vector<int> KMPForTask2(const std::string &myText, const std::string &myString){
    std::vector<int> result;
    std::string currStr = myText + '#' + myString + myString;
    std::vector<int> pi = Prefix(currStr);
    
    const int LenText = myText.length();
    const int LenStr = myString.length();
    
    for(int i = 0; i < 2*LenText; ++i){
        if(pi[LenStr + 1 + i] == LenStr){
            result.push_back(i - LenStr + 1);
            break;
        }
    }
    return result;
}

int main() {
    std::vector<int> ans;
    std::string str;
    std::string text;
    std::cout << "Enter frist substring then text: " << std::endl;
    std::cin >> str;
    std::cin >> text;
    std::cout << "-----" << std::endl;
#ifdef RES
    ans = KMPForTask1(text, str);
#endif
#ifdef RES2
    ans = KMPForTask2(text, str);
#endif

    for(auto i = 0; i < ans.size(); i++){
        std::cout << ans[i];
        if(i + 1 != ans.size())
            std::cout << ", ";
    }
    std::cout << std::endl;
    return 0;
}
