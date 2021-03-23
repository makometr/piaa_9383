#include "Table.h"

int main()
{

    int N;
    cin >> N;
    Table table(N);

    if (N % 2 == 0)
    {
        table.division2();
        return 0;
    }
    //создание "карты" дял стола

    if (N % 3 == 0)
    {
        table.division3();
    }
    else if (N % 5 == 0)
    {
        table.division5();
    }
    else
    {
        table.primeNumber();
        table.printAnswer();
    }

    return 0;
}