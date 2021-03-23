#include "Table.h"

void Table::printAnswer(int scale)
{
    cout << minCounter << '\n';
    for (int i = 0; i < minCounter; i++)
    {
        cout << resArr[i].second.first * scale + 1 << ' ' << resArr[i].second.second * scale + 1 << ' ' << resArr[i].first * scale << '\n';
    }
}

void Table::insertBlock(int m, int x, int y) //Вставка квадрата размером m * m с левым верхним углов в точке (x, y)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mainArr[x + i][y + j] = true;
        }
    }
}

void Table::removeBlock(int m, int x, int y) //Вставка квадрата размером m * m с левым верхним углов в точке (x, y)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mainArr[x + i][y + j] = false;
        }
    }
}

pair<int, int> Table::findEmpty() //Поиск первой свободной ячейки для вставки
{
    for (int i = N / 2; i < N; i++)
    {
        for (int j = N / 2; j < N; j++)
        {
            if (!mainArr[i][j])
                return make_pair(i, j);
        }
    }
    return make_pair(-1, -1);
}

pair<int, bool> Table::findMaxSize(int x, int y)
{
    for (int i = y + 1; i < N; i++)
    {
        if (mainArr[x][i])
        {
            if (N - x == i - y)
                return make_pair(N - x, true);
            return make_pair((N - x > i - y) ? i - y : N - x, false);
        }
    }
    if (N - x == N - y)
        return make_pair(N - x, true);
    return make_pair((N - x > N - y) ? N - y : N - x, false);
}

void Table::chooseBlock(vector<pair<int, pair<int, int>>> &tmpArr, int counter, int x, int y)
{
    pair<int, int> coord = findEmpty();
    if (coord.first == -1)
    {
        if (tmpArr.size() < minCounter)
        {
            resArr = tmpArr;
            minCounter = tmpArr.size();
        }
        return;
    }
    if (counter + 1 >= minCounter)
    {
        return;
    }
    int tmpBestCounter = minCounter;
    //поиск места для вставки блока
    pair<int, bool> maxSize = findMaxSize(coord.first, coord.second); //поиск максимального размера блока для вставки на найденное пустое место
    if (maxSize.second)                                               //Если можно вставить сразу блок максимального размера
    {
        tmpArr.push_back(make_pair(maxSize.first, coord));
        insertBlock(maxSize.first, coord.first, coord.second);
        chooseBlock(tmpArr, counter + 1, x, y); //вставляем очередной блок
        removeBlock(maxSize.first, coord.first, coord.second);
        tmpArr.pop_back();
    }
    else
    {
        for (int i = maxSize.first; i >= 1; i--)
        {
            if (tmpBestCounter > minCounter && i == 1)
                continue;
            tmpArr.push_back(make_pair(i, coord));
            insertBlock(i, coord.first, coord.second);
            chooseBlock(tmpArr, counter + 1, x, y); //вставляем очередной блок
            removeBlock(i, coord.first, coord.second);
            tmpArr.pop_back();
        }
    }
}

void Table::primeNumber() //вставка начальных блоков и начало работы бэктрекинга
{
    insertBlock(N / 2 + 1, 0, 0);
    insertBlock(N / 2, N / 2 + 1, 0);
    insertBlock(N / 2, 0, N / 2 + 1);
    int counter = 3;
    int minCounter = N * N;
    vector<pair<int, pair<int, int>>> tmpArr;
    tmpArr.push_back(make_pair(N / 2 + 1, make_pair(0, 0)));
    tmpArr.push_back(make_pair(N / 2, make_pair(N / 2 + 1, 0)));
    tmpArr.push_back(make_pair(N / 2, make_pair(0, N / 2 + 1)));
    chooseBlock(tmpArr, counter, N / 2, N / 2);
}

void Table::division2()
{
    if (N % 2 == 0)
    {
        int N_div = N / 2;
        cout << 4 << '\n';
        cout << 1 << ' ' << 1 << ' ' << N_div << '\n';
        cout << N_div + 1 << ' ' << 1 << ' ' << N_div << '\n';
        cout << 1 << ' ' << N_div + 1 << ' ' << N_div << '\n';
        cout << N_div + 1 << ' ' << N_div + 1 << ' ' << N_div << '\n';
    }
}

void Table::division3()
{
    int realN = N;
    int scale = N / 3;
    N = 3;
    primeNumber();
    printAnswer(scale);
}

void Table::division5()
{
    int realN = N;
    int scale = N / 5;
    N = 5;
    primeNumber();
    printAnswer(scale);
}
