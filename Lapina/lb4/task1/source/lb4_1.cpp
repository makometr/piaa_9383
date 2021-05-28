#include "lb4_1.hpp"

std::vector <int> create_pi(std::string P){
    std::vector <int> pi_;
    for (int i = 0; i!= P.length(); i++){
        pi_.push_back(0);
    }
    int i = 1;
    int j = 0;
    while (i!=P.length()){
        if (P[i] == P[j]){
            pi_[i] = j+1;
            i++;
            j++;
        }
        else{
            if (j==0){
                pi_[i] = 0;
                i++;
            }
            else{
                j = pi_[j-1];
            }
        }
    }
    return pi_;
}

std::vector <int> Alg_KMP(std::string T, std::string P, std::vector <int> pi_){
    int k = 0;
    int l = 0;
    std::vector <int> result;
    while (k!=T.length()){
        if (T[k] == P[l]){
            k++;
            l++;
            if (l==P.length()){
                result.push_back(k - P.length());
            }
        }
        else{
            if(l==0){
                k++;
                if (k == T.length()){
                    break;
                }
            }
            else{
                l = pi_[l-1];
            }
        }
    }
    return result;
}
 
