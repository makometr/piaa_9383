#include "kmp.hpp"

std::vector<int> prefix_function(const std::string& str) {
    int n = str.length();
    if(n == 0) return std::vector<int> (0);
    
    std::vector<int> prefix_arr(n);

    int j;
    for (int i = 1; i < n; ++i) {
        j = prefix_arr[i - 1];
        while (j > 0 && str[i] != str[j]) j = prefix_arr[j - 1];
        if (str[i] == str[j]) j++;
        prefix_arr[i] = j;
    }
    return prefix_arr;
}

std::vector<int> kmp(const std::string& patt, const std::string& temp, bool stop_at_first) {
    std::vector<int> answer;
    int patt_len = patt.size();
    int temp_len = temp.size();

    if(patt_len == 0 || temp_len == 0) {
        answer.push_back(-1);
        return answer;
    }

    std::vector<int> p = prefix_function(patt + "#");
    int j = 0;
    for(int i = 0; i < temp_len; ++i) {
        while(j > 0 && patt[j] != temp[i]) j = p[j-1];
        if(patt[j] == temp[i]) j++;
        if(j == patt_len) {
            answer.push_back(i - patt_len + 1);
            if(stop_at_first) break;
        }
    }

    if(!answer.size()) answer.push_back(-1);
    
    return answer;
}

int check_cycle(const std::string& patt, const std::string& temp) {
    int patt_len = patt.size();
    int temp_len = temp.size();

    if(patt_len == 0 || temp_len == 0) return -1;

    if(patt_len != temp_len) return -1;

    std::vector<int> res = kmp(temp, patt + patt, true);

    return res[0];
}

bool read_strings(std::string& patt, std::string& temp, std::istream& in) {
    in >> patt;
    in >> temp;

    if(patt.size() == 0 || temp.size() == 0) return false;
    return true;
}

void print_vector(const std::vector<int>& vec) {
    for(int i = 0; i < vec.size(); ++i) {
        if(i == vec.size() - 1) {
            std::cout << vec[i] << "\n";
        }
        else {
            std::cout << vec[i] << ",";
        }
    }
}