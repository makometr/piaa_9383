#include "lab1.h"

using namespace std;





int main()
{
    setlocale(LC_ALL, "Russian");
    int n,m;
    cin>>n>>m;
    int div = 1;

    if(n % 2 == 1 || m % 2 == 1)
    {
        for (int i = 2; i <= sqrt(min(n,m)); i++)
        {
            if (min(n,m) % i == 0 && max(n,m) % i == 0)
            {
                if(n==m)
                {
                    div *= max(i,n/i);
                    n /= max(i,n/i);
                    m /= max(i,m/i);
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

    cout<<F.bestSquares.size()<<"\n";
    for(int i = 0; i < F.bestSquares.size(); i++)
    {
        cout<<F.bestSquares[i].x*div + 1<<" "<<F.bestSquares[i].y*div + 1<<" "<<F.bestSquares[i].sizeSquare*div<<"\n";
    }

    cout<<"-------------------\n";
    cout<<"Количество вариантов покрытия минимальным числом квадратов = "<< F.counter<<"\n";

    return 0;
}
