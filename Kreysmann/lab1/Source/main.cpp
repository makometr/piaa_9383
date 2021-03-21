#include "header.hpp"


/*void printTable(const Table table)
{
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table.size(); j++)
        {
            std::cout << table[i][j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}*/
Table initTable()
{
    unsigned short N=0;
    while(N<2 || N>40)
    {
        std::cout<<"Input 2<=N<=40: ";
        std::cin >> N;
    }
    return createTableNxN(N);
}



Solution fillTable(Table& table)
{
    if (table.size() % 2 == 0)
    {
        return evenFillTable(table);
    }
    else if (table.size() % 3 == 0)
    {
        return multipleOfThreeFillTable(table);
    }
    else if (table.size() % 5 == 0)
    {
        return multipleOfFiveFillTable(table);
    }
    else
    {
        Solution tempSolution = initialFill(table);//расставляет первые три квадрата
        Solution result;
        auto start = std::chrono::steady_clock().now();
        Process(table,tempSolution, result);
        auto end = std::chrono::steady_clock().now();
        std::cout << "\nTime:" << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << '\n';
        return result;
    }
}

void printAnswer(Solution best)
{
    std::cout << best.size() << '\n';
    while (!best.empty())
    {
        std::cout << best.top().x + 1 << ' ' << best.top().y + 1 << ' ' << best.top().size << '\n';
        best.pop();
    }
}


int main()
{
    Table table = initTable();
    printAnswer(fillTable(table));
    return 0;
}




