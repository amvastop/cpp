#include<iostream>
#include <ctime>
using namespace std;


struct ComplexNumber
{
    double realnumber;
    double imaginarynumber;
};

int sumArray(int*, const int);
ComplexNumber sumArray(ComplexNumber*, const int);

int main()
{
    int n;
    cout << " введтите количество чисисел которое хотите ввести: ";
    cin >> n;
    ComplexNumber* numbers = new ComplexNumber[n];
    cout << " Введите  чиса или число " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> numbers[i].realnumber >> numbers[i].imaginarynumber; 
    }
    ComplexNumber number = sumArray(numbers, n);
    cout << "Ответ: " << number.realnumber << " " <<number.imaginarynumber << "*i" << endl;
    int* intarray = new int[n];
    cout << "Введите элементы массива" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> intarray[i];
    }
    int sum = sumArray(intarray, n);
    cout << "Ответ:" << sum;
    delete[] numbers;
    delete[] intarray;



}
int sumArray(int* array, const int N)
{
    int sum = 0;
    for(int i = 0; i < N; i++)
    {
        sum += array[i];
    }
    return sum;
}
ComplexNumber sumArray(ComplexNumber* numbers, const int N)
{
    ComplexNumber number;
    for(int i = 0; i<N; i++)
    {
        number.realnumber += numbers[i].realnumber;
        number.imaginarynumber += numbers[i].imaginarynumber;
    }
    return number;
}
ComplexNumber sumNumber(ComplexNumber* firstnumber, ComplexNumber* secondnumber)
{
    ComplexNumber number;
    number.imaginarynumber = firstnumber->imaginarynumber + secondnumber->imaginarynumber;
    number.realnumber = firstnumber->realnumber + secondnumber->realnumber;
    return number;
}