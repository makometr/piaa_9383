#include "Table.hpp"

using namespace std;

int main() {
    int side;
    if(cin >> side && side >= 2)
    {
        Table a(side);
        a.running();
    }
    cout << "Wrong input!\n";
}
