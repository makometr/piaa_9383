#include "lb4_1.hpp"

 int main(){
    std::string P, T;
    std::cin >> P;
    std::cin >> T;
    if (P.length()>T.length()){
        std::cout << "−1";
        return 0;
    }
  
    std::vector <int> pi_ = create_pi(P);
    std::vector <int> result = Alg_KMP(T, P, pi_);
    if (result.empty())
        std::cout << "-1";
    else{
        for (int i = 0; i!=result.size(); i++){
            if (i == result.size()-1)
                std::cout << result[i];
            else
                std::cout <<  result[i]  << ",";
        }
    }
    return 0;
 }
