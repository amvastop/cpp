#include<iostream>
#include <ctime>
using namespace std;
int main()
{
    int n, m;
    int sum_rand = 0;
    int index = 0;
    const int UPPER_BOUND = 11;

    setlocale( LC_ALL, "rus" );
    srand( time(0) );
    cout << "введите два числа: \n 1) введите максимальное число \n 2)делитель" << endl;
    cin >> n >> m;
    while ( n > sum_rand )
    {
         
        sum_rand += rand() % UPPER_BOUND;
        if ( sum_rand % m == 0 )
        {
            cout << "номер попытки:" << index << endl;
        }
         else
        {
            sum_rand = 0;
            index++;
        }
    }
    cout << "конечная сумма= " << sum_rand;
    return 0;
    
}