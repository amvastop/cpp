#include <iostream>
#include <vector>
#include <algorithm>
#include  <functional>
#include <numeric>

using namespace std;
class dividers
{
    private:
        vector<int> mydeviders;
        int* number;

    public:
        dividers(int num) : number(new int{num}) 
        {
            if (num <= 0)
            {
                cout << " не натуральное число " << endl;
                abort();
            }
            for(int i = 1; i <= num; i++) if(num % i == 0) mydeviders.push_back(i);
            
        }
        
        double avaregDividers()
        {
            return accumulate(mydeviders.begin(), mydeviders.end(), (double) 0) / mydeviders.size();
        }
        ~dividers()
        {
            delete number;
            mydeviders.clear();

        }


    friend int findingGCFByBind(dividers& firs, dividers& second);
    friend int findingGCFByLambdaFunctions(dividers& first, dividers& second);
};
bool pred(int i, int* const number)
{
    return (*number % i == 0);
}

int findingGCFByLambdaFunctions(dividers& first, dividers& second)  // нахождение наибольшего общего делителя через лямда функции
{
    if (*(first.number) >= *(second.number)) 
        return *(find_if(second.mydeviders.rbegin(), second.mydeviders.rend(), [&first] (int& el) {return *(first.number) % el == 0;} ));
    else
        return *(find_if(first.mydeviders.rbegin(), first.mydeviders.rend(), [&second] (int& el) {return *(second.number) % el == 0;} ));

}

int findingGCFByBind(dividers& first, dividers& second) // нахождение наибольшего общего делителя через bind 
{
    if (*(first.number) >= *(second.number)) 
       return *(find_if(second.mydeviders.rbegin(), second.mydeviders.rend(), bind(pred, placeholders::_1, first.number)));
    else 
        return *(find_if(first.mydeviders.rbegin(), first.mydeviders.rend(), bind(pred, placeholders::_1, second.number)));
    
}
int main()
{
    dividers a(0);
    dividers b(25);
    cout << findingGCFByBind(b, a) << endl;
    cout << b.avaregDividers();
    return 0;
}