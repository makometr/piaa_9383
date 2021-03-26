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

Square::Square(integer y,integer x, integer size)
{
    this->y=y;
    this->x=x;
    this->size=size;
}

bool checkPlaceForSquare(const Coordinate& coord,integer size, const Table& table)
{
    try
    {
        if(size==0 || size>=table.size())
        {
            throw(0);
        }
        if (coord.first + size > table.size() || coord.second + size > table.size())
        {
            return false;
        }
        for (integer i = coord.first; i < coord.first + size; i++)
        {
            for (integer j = coord.second; j < coord.second + size; j++)
            {
                if (table[i][j] == 1)
                {
                    return false;
                }
            }
        }
        return true;
    }
    catch(int)
    {
        std::cerr<<"invalid size (checkPlaceForSquare())"<<'\n';
        exit(0);
    }
}

void addSquare(const Square& square, Table& table, Solution& solution)
{
    try{
        if(square.size > table.size()-1)
        {
            throw(0);
        }
    
        for (integer i = square.y; i < square.y + square.size; i++)
        {
            for (integer j = square.x; j < square.x + square.size; j++)
            {
                if(table[i][j]==1)
                {
                    throw(0);
                }
                table[i][j] = 1;
            }
        }
        solution.push(square);
    }
    catch(int)
    {
        std::cerr<<"invalid square size or coordinate (addSquare())"<<'\n';
        exit(0);
    }
}

void delSquare(Table& table, Solution& solution)
{
    Square square = solution.top();
    try
    {
        if(solution.size()==0)
        {
            throw 0;
        }
        if(solution.top().x + solution.top().size > table.size() || solution.top().y+solution.top().size>table.size())
        {
            throw 0;
        }
        for (integer i = square.y; i < square.y + square.size; i++)
        {
            for (integer j = square.x; j < square.x + square.size; j++)
            {
                if(table[i][j]==0)
                {
                    throw 0;
                }
                table[i][j] = 0;
            }
        }
        solution.pop();
    }
    catch(int)
    {
        std::cerr<<"error (delSquare())"<<'\n';
        exit(0);
    }


}


std::optional<Coordinate> nextCoordinate(const Table& table)
{
    const integer N = table.size();
    for (integer i = N / 2 + 1; i < N; i++)
    {
        if (table[N / 2][i] == 0)
        {
            return Coordinate(N / 2, i);
        }
    }
    for (integer i = N / 2 + 1; i < N; i++)
    {
        for (integer j = N / 2; j < N; j++)
        {
            if (table[i][j] == 0)
            {
                return Coordinate(i, j);
            }
        }
    }
    return std::nullopt;
}

bool isBadSolution(const Solution &tempSolution,const Solution &bestSolution, integer minSize)
{
    return tempSolution.size() >= bestSolution.size()-1 && bestSolution.size()!=0 || tempSolution.size()> minSize-1 && bestSolution.size()==0;
}



void backTracking(Table& table, Solution& tempSolution, Solution& bestSolution)
{
    StackBacktrack Stack;
    const integer startSize=1;
    Coordinate tempCoord = nextCoordinate(table).value();
    Stack.push(Pair(startSize,tempCoord));
    const integer minSizeBestSolution = table.size() +3;
    while (!Stack.empty())
    {
        if (isBadSolution(tempSolution,bestSolution,minSizeBestSolution))
        {
            delSquare(table, tempSolution);
            Stack.pop();
            continue;
        }
        tempCoord = Stack.top().second;
        integer sizeSquare = Stack.top().first;
        if (checkPlaceForSquare(tempCoord, sizeSquare, table))
        {
            addSquare(Square(tempCoord.first, tempCoord.second, sizeSquare), table, tempSolution);
            std::optional<Coordinate> coord = nextCoordinate(table);
            if (coord)
            {
                Stack.pop();
                Stack.push(Pair(sizeSquare + 1, tempCoord));
                Stack.push(Pair(startSize, coord.value()));
            }
            else
            {
                bestSolution = tempSolution;
                delSquare(table, tempSolution);
                delSquare(table, tempSolution);
                Stack.pop();
            }
        }
        else
        {
            delSquare( table, tempSolution);
            Stack.pop();
            continue;
        }
    }
}

Solution evenFillTable(Table& table)
{
    const integer N = table.size();
    Solution result;
    addSquare(Square(0, 0, N / 2), table, result);
    addSquare(Square(0, N / 2 , N / 2), table, result);
    addSquare(Square(N / 2, 0, N / 2),table, result);
    addSquare(Square(N / 2, N / 2, N / 2), table, result);
    
    return result;
}
Solution multipleOfThreeFillTable(Table& table)
{
    const integer N = table.size();
    Solution result;
    addSquare(Square(0, 0, N * 2 / 3), table, result);
    addSquare(Square(0, N * 2 / 3, N * 1 / 3), table, result);
    addSquare(Square(N * 1 / 3, N * 2 / 3, N * 1 / 3), table, result);
    addSquare(Square(N * 2 / 3, N * 2 / 3, N * 1 / 3), table, result);
    addSquare(Square(N * 2 / 3, 0, N * 1 / 3), table, result);
    addSquare(Square(N * 2 / 3, N * 1 / 3, N * 1 / 3), table, result);
    return result;
}
Solution multipleOfFiveFillTable(Table& table)
{
    const integer N = table.size();
    Solution result;
    addSquare(Square(0, 0, N * 3 / 5), table, result);
    addSquare(Square(0, N * 3 / 5, N * 2 / 5), table, result);
    addSquare(Square(N * 3 / 5, 0, N * 2 / 5), table, result);
    addSquare(Square(N * 3 / 5, N * 3 / 5, N * 2 / 5), table, result);
    addSquare(Square(N * 2 / 5, N * 3 / 5, N * 1 / 5), table, result);
    addSquare(Square(N * 2 / 5, N * 4 / 5, N * 1 / 5), table, result);
    addSquare(Square(N * 3 / 5, N * 2 / 5, N * 1 / 5), table, result);
    addSquare(Square(N * 4 / 5, N * 2 / 5, N * 1 / 5), table, result);
    return result;
}
Solution initialFill(Table& table)
{
    const integer N = table.size();
    Solution result;
    addSquare(Square(0, 0, N / 2 + 1), table, result);
    addSquare(Square(0, N / 2 + 1, N / 2), table, result);
    addSquare(Square(N / 2 + 1, 0, N / 2), table, result);
    return result;
}

Table createTableNxN(integer N)
{
    try
    {
        if(N<2 || N>40)
        {
            throw(0);
        }
        Table table = Table();
        table.resize(N);
        std::for_each(table.begin(), table.end(), [N](std::vector<integer>& i)
            {
                i.resize(N, 0);
            });
        return table;
    }
    catch(int)
    {
        std::cerr<<"N must be >=2 && <=40 ( createTableNxN() )"<<'\n';
        exit(0);
    }
}

