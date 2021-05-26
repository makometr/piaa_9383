#include "lab1.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    int n,m;
    std::cin>>n>>m;
    int div = 1;

    if(n % 2 == 1 || m % 2 == 1)
    {
        for (int i = 2; i <= sqrt(std::min(n,m)); i++)
        {
            if (std::min(n,m) % i == 0 && std::max(n,m) % i == 0)
            {
                if(n==m)
                {
                    div *= std::max(i,n/i);
                    n /= std::max(i,n/i);
                    m /= std::max(i,m/i);
                }
                else
                {
                    div *= i;
                    n /= i;
                    m /= i;
                }
            }
        }
    }

    Field F(n,m);
    F.backtracking();

    std::cout<<F.bestSquares.size()<<"\n";
    for(int i = 0; i < F.bestSquares.size(); i++)
    {
        std::cout<<F.bestSquares[i].x*div + 1<<" "<<F.bestSquares[i].y*div + 1<<" "<<F.bestSquares[i].sizeSquare*div<<"\n";
    }

    std::cout<<"-------------------\n";
    std::cout<<"Amount of coverage variant with the minimum number of squares = "<< F.counter<<"\n";

    return 0;
}
