{\rtf1\ansi\ansicpg1251\cocoartf2580
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww25400\viewh12940\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include <vector>\
#include <algorithm>\
#include <iostream>\
\
\
class Square\
\{\
\
private:\
    int side=0;\
    int x=0;\
    int y=0;\
public:\
    Square()=default;\
    Square(int s, int x, int y): side(s), x(x), y(y)\{\}\
    ~Square() = default;\
    int GetX()\
    \{\
    return this->x;\
    \}\
    int GetY()\
    \{\
    return this->y;\
    \}\
    int GetSide()\
    \{\
    return this->side;\
    \}\
\};\
\
\
class Processor\
\{\
\
public: \
    int FindNextSide(int** array, int array_size, int x, int y);\
    void SquareSetting(int** array, int array_size, int x, int y, int square_side, int flag);\
    bool IsArrayFull(int** array, int array_size, int& x, int& y, std::vector<Square>& data, int data_size);\
    void PopBackData(int** array, int array_size, std::vector<Square>& data, int& data_size, int& flag);\
    void PrintData(std::vector<Square> data);\
\};\
\
int Processor::FindNextSide(int** array, int array_size, int x, int y)\
\{\
    int right_side = 1, down_side = 1;\
    int i = x, j = y;\
    int max_side = array_size-1;\
    \
    while (right_side <= max_side && j+right_side<array_size && array[i][j+right_side]!=1 )\
        right_side++;\
\
    while (down_side <= max_side && i+down_side<array_size && array[i+down_side][j]!=1 )\
        down_side++;\
    int side=std::min(right_side, down_side);\
    return side;\
\}\
\
void Processor::SquareSetting(int** array, int array_size, int x, int y, int square_side, int flag)\
\{\
    for (int i = x; i < x + square_side; i++)\
    \{\
        for (int j = y; j < y + square_side;j++)\
            array[i][j]=flag;\
    \}\
\}\
\
bool Processor::IsArrayFull(int** array, int array_size, int& x, int& y, std::vector<Square>& data, int data_size)\
\{\
for (int i=0;i<array_size;i++)\
\{\
        for (int j=0;j<array_size;j++)\
        \{\
            if (array[i][j]==0)\
            \{\
                x = i;\
                y = j;\
                return true;\
            \}\
        \}\
    \}\
    return false;\
\}\
\
void Processor::PopBackData(int** array, int array_size, std::vector<Square>& data, int& data_size, int& flag)\
\{\
   while (true)\
   \{\
       if (data_size<=3)\
       \{\
           flag=1;\
           break;\
        \} \
        else\
        \{\
            Square square = data[data_size-1];\
            if (data[data_size-1].GetSide()>=2)\
            \{\
                data.pop_back();\
                data_size-=1;\
                this->SquareSetting(array, array_size, square.GetX(), square.GetY(), square.GetSide(), 0);\
                this->SquareSetting(array, array_size, square.GetX(), square.GetY(), square.GetSide()-1, 1);\
                data.push_back(Square(square.GetSide()-1, square.GetX(), square.GetY()));\
                data_size+=1;\
                break;\
            \}\
            else\
            \{\
                data.pop_back();\
                data_size-=1;\
                this->SquareSetting(array, array_size, square.GetX(), square.GetY(), square.GetSide(), 0);\
                continue;\
            \}\
        \}\
    \}\
\}\
\
void Processor::PrintData(std::vector<Square> data)\
\{\
    for (int i=0;i<data.size();i++)\
        std::cout<<data[i].GetX()<<' '<<data[i].GetY()<<' '<<data[i].GetSide()<<"\\n";\
\}\
\
int main()\
\{\
    std::vector <Square> result;\
    std::vector <Square> actual;\
    Processor processor;\
    int n;\
    std::cin>>n;\
    int desired_side = n*n;\
\
    if (n%2==0)\
    \{\
        desired_side = 4;\
        result.push_back(Square(n/2, 0, 0));\
        result.push_back(Square(n/2, 0, n/2));\
        result.push_back(Square(n/2, n/2, 0));\
        result.push_back(Square(n/2, n/2, n/2));\
    \}\
    else\
    \{\
\
        int** array = new int*[n];\
        for (int i=0; i<n; i++) array[i]= new int[n];\
\
        for (int i=0;i<n;i++)\
        \{\
            for (int j=0;j<n;j++) \
                array[i][j]=0;\
        \}\
\
        if (n%3==0)\
        \{\
            actual.push_back(Square(n*2/3, 0, 0));\
            actual.push_back(Square(n/3, 0, n*2/3));\
            actual.push_back(Square(n/3, n*2/3,0));\
\
            processor.SquareSetting(array, n, 0, 0, n*2/3, 1);\
            processor.SquareSetting(array, n, 0, n*2/3, n/3, 1);\
            processor.SquareSetting(array, n, n*2/3, 0, n/3, 1);\
\
        \}\
        else\
        \{\
            actual.push_back(Square(n/2 + 1, 0, 0));\
            actual.push_back(Square(n/2, 0, n/2+1));\
            actual.push_back(Square(n/2, n/2+1,0));\
\
            processor.SquareSetting(array, n, 0, 0, n/2+1, 1);\
            processor.SquareSetting(array, n, 0, n/2+1, n/2, 1);\
            processor.SquareSetting(array, n, n/2+1, 0, n/2, 1);\
        \}\
\
        int actual_x = 0;\
        int actual_y = 0;\
        int actual_max_side = 3;\
        int new_square_side = 0;\
        int flag=0;\
\
        while (!actual.empty() && flag!=1)\
        \{\
\
            if (n>11 && actual_max_side>=n)\
                processor.PopBackData(array, n, actual, actual_max_side, flag);\
\
            if (actual_max_side>=desired_side)\
                processor.PopBackData(array, n, actual, actual_max_side, flag);\
            \
            if (processor.IsArrayFull(array, n, actual_x, actual_y, actual, actual_max_side))\
            \{\
                int new_side = processor.FindNextSide(array, n, actual_x, actual_y);\
                actual.push_back(Square(new_side, actual_x, actual_y));\
                actual_max_side+=1;\
                processor.SquareSetting(array, n, actual_x, actual_y, new_side, 1);\
            \}\
            else\
            \{\
                result = actual;\
                desired_side = actual_max_side;\
                processor.PopBackData(array, n, actual, actual_max_side, flag);\
            \}\
        \}\
        for (int i=0; i<n; i++)\
            delete [] array[i];\
        delete [] array;\
    \}\
\
    std::cout << desired_side << std::endl;\
    processor.PrintData(result);\
\
    return 0;\
\}}