#include "lb4_2.hpp"

 int main(){
    std::string A, B;
    std::cin >> A;
    std::cin >> B;

    A = A+A;

    std::vector <int> pi_ = create_pi(B);
    std::vector <int> result = Alg_KMP(A, B, pi_);
    if (result.empty() || (2 * B.length()!= A.length()))
        std::cout << "-1\n";
    else{
        std::cout << result[0] << "\n";
    }
    return 0;
 }

