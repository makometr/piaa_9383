#include "lab1.h"


Field::Field(int w, int h)
{
    this->Width = w;
    this->Height = h;

    for(int i = 0; i < this->Height; i++)
    {
        this->table.push_back(vector<bool>());
        for(int j = 0; j < this->Width; j++)
        {
            this->table[this->table.size()-1].push_back(0);
        }
    }
}

void Field::printField()
{
    for (int i = 0; i < this->Height; i++)
    {
        for (int j = 0; j < this->Width; j++)
        {
            std::cout << this->table[i][j] << " ";
        }
        std::cout <<"\n";
    }
}

bool Field::isFree(int x, int y)
{
    if(this->table[y][x])
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Field::setFree(int x, int y)
{
    this->table[x][y] = false;
}

void Field::setBusy(int x, int y)
{
    this->table[x][y] = true;
}


void Field::buildSquare(int x, int y, int sizeS)
{
    if(sizeS > 0 && sizeS < min(this->Width, this->Height))
    {
        this->Squares.push_back({sizeS, x, y});
        for(int i = y; i < y+sizeS; i++)
        {
            for(int j = x; j < x+sizeS; j++)
            {
                this->setBusy(i,j);
            }
        }
    }
}

void Field::destroyLastSquare()
{
    Square S;
    S = this->Squares.back();
    this->Squares.pop_back();
    for(int i = S.y; i < S.y+S.sizeSquare; i++)
    {
        for(int j = S.x; j < S.x+S.sizeSquare; j++)
        {
            this->setFree(i,j);
        }
    }
}

Square Field::findNextFreeCell()
{
    for(int i = 0; i < this->Height; i++)
    {
        for(int j = 0; j < this->Width; j++)
        {
            if(this->isFree(j,i))
            {
                return {0, j, i};
            }
        }
    }

    return {-1, -1, -1};
}

int Field::findMaxSizeOfSquare(int x, int y, int maxSize)
{
    int newSize = 1;
    while((x + newSize < this->Width) && (y + newSize < this->Height) && (this->isFree(x + newSize, y)) && (newSize < maxSize))
    {
        newSize++;
    }

    return newSize;
}


void Field::backtracking()
{
    int maxSize = min(this->Height, this->Width) - 1;
    bool full = false;
    Square S;
    Square newSquare;
    S.sizeSquare = maxSize;
    S.x = 0;
    S.y = 0;


    do
    {
        while(!full)
        {
            newSquare = findNextFreeCell();

            if(newSquare.x == -1)
            {
                full = true;
                continue;
            }

            this->buildSquare(newSquare.x, newSquare.y, findMaxSizeOfSquare(newSquare.x,newSquare.y, maxSize));

            if(this->Squares.size()>0 && this->bestSquares.size()>0 && this->bestSquares.size() < this->Squares.size())
            {
                break;
            }
        }

        if((this->bestSquares.size() > this->Squares.size() || this->bestSquares.size() == 0) && full)
        {
            this->bestSquares = this->Squares;
            this->counter = 0;
        }

        if(this->bestSquares.size() == this->Squares.size() && full)
        {
            this->counter++;
        }

        while(this->Squares.back().sizeSquare == 1 && this->Squares.size()>1)
        {
            this->destroyLastSquare();
        }

        if(this->Squares.empty())
        {
            break;
        }

        S = this->Squares.back();
        this->destroyLastSquare();
        full = false;

        this->buildSquare(S.x, S.y, S.sizeSquare - 1);

    }
    while(!this->Squares.empty());
}
