#include "lb1.hpp"

int main() {
    clock_t start_time = clock();
    int n;
    cin >> n;
    int result = 3+n+1;
    List_of_squares result_squares;  //для итоговых значений
    if (n % 2 == 0) {  //для чисел, делящихся на 2
        Divisible_2(n, result, result_squares);
    }
    else if (n % 3 ==0){//для чисел, делящихся на 3
        Divisible_3(n, result, result_squares);
    }
    else{               //для оставшихся (простых) чисел
        Map map(n);
        for (int i = 0; i < n; i++)
            map[i] = vector<int>(n, 0);
        Simple_Number(n, map, result, result_squares);
    }
    Print(result, result_squares);
    clock_t end_time = clock();
    Time_Information(start_time, end_time);
    return 0;
}
