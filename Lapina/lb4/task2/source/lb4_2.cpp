#include "lb4_2.hpp"


std::vector <int> create_pi(std::string B){
    std::vector <int> pi_;
    for (int i = 0; i!= B.length(); i++){
        pi_.push_back(0);
    }
    int i = 1;
    int j = 0;
    while (i!=B.length()){
        if (B[i] == B[j]){
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

std::vector <int> Alg_KMP(std::string A, std::string B, std::vector <int> pi_){
    int k = 0;
    int l = 0;
    std::vector <int> result;
    while (k!=A.length()){
        if (A[k] == B[l]){
            k++;
            l++;
            if (l==B.length()){
                result.push_back(k - B.length());
                break;
            }
        }
        else{
            if(l==0){
                k++;
                if (k == A.length()){
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
