#include "header.hpp"
#include <fstream>

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

integer getInput()
{
    integer N=0;
    while(N<2 || N>40)
    {
        std::cout<<"Input 2<=N<=40: ";
        std::cin >> N;
    }
    return N;
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
        //auto start = std::chrono::steady_clock().now();
        backTracking(table,tempSolution, result);
        //auto end = std::chrono::steady_clock().now();
        //std::cout << "\nTime:" << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << '\n';
        return result;
    }
}

std::ostream& operator<<(std::ostream& out, Solution solution)
{
    out << solution.size() << '\n';
    while (!solution.empty())
    {
        out << solution.top().x + 1 << ' ' << solution.top().y + 1 << ' ' << solution.top().size << '\n';
        solution.pop();
    }
    return out;
}


int main()
{
    integer N = getInput();
    Table table = createTableNxN(N);
    std::cout<<fillTable(table);

    //std::ofstream file("output.txt");
    //file<<fillTable(table);
    //file.close();
    return 0;
}




