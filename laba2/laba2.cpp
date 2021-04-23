#include<iostream>
#include <ctime>
using namespace std;
void sumMatrix(double**, double**,double**, const int);
void print(double**, const int);



int main()
{
    int N;
    const int UPPER_BOUND = 10;

    setlocale(LC_ALL, "rus");
    srand( time(0) );
    cout << "введите размер массива" << endl;
    cin >> N;
    //sum_rand += rand() % UPPER_BOUND;
    double** A = new double* [N];
    double** B = new double* [N];
    double** C = new double* [N];
    for (int i; i<N; i++)
    {
        A[i] = new double [N];
        B[i] = new double [N];
        C[i] = new double [N];
    }

    for (int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++ )
        {
            A[i][j] = (double)(rand()) / RAND_MAX * UPPER_BOUND;
            B[i][j] = (double)(rand()) / RAND_MAX * UPPER_BOUND;
        }

    }
    sumMatrix(A, B, C, N);
    print(A, N);
    print(B, N);
    print(C, N);


    for(int i = 0; i < N; i++)
    {
        delete [] A[i];
        delete [] B[i];
        delete [] C[i];
    }
    delete [] A;
    delete [] B;
    delete [] C;


   return 0;
}

void sumMatrix(double** A, double** B, double** C, const int SIZE)
{ 
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

}

void print(double** Arry, const int SIZE)
{ 
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        { 
            cout << Arry[i][j] << '\t';

        }
        cout << endl;

    }
    cout << endl;

}