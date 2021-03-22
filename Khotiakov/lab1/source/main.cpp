#include "functions.h"

int main()
{
    cin >> N;
    minCounter = N * N;
    if (N % 2 == 0)
    {
        division2();
        return 0;
    }
    //создание "карты" дял стола
    vector<vector<bool>> mainArr(N);
    for (int i = 0; i < N; i++)
        mainArr[i].resize(N);

    if (N % 3 == 0)
    {
        division3(mainArr);
    }
    else if (N % 5 == 0)
    {
        division5(mainArr);
    }
    else
    {
        primeNumber(mainArr);
        printAnswer();
    }

    return 0;
}