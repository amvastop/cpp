#include <iostream>
#include <ctime>
#include <string>
using namespace std;
enum Typeofwepon
{
    SWORD,
    PISTOL,
};

class Wepon
{
    private:
        Typeofwepon item;
        double damage;
        double attackspeed;
    
    public:
        Wepon (double damage, double attackspeed, Typeofwepon item ) : 
            damage(damage), 
            attackspeed(attackspeed), 
            item(item)
        {}

        double damagePerSecond()
        {
            double time = 60;
            return (damage * time) / attackspeed;
        }

        void check()
        {
            cout << " урон: " << damage << " скорость атаки: " << attackspeed << endl;
        }
        
        Typeofwepon getItem()
        {
            return item;
        }    
};

class Pistol : public Wepon
{
    public: 
        Pistol (double damage, double attackspeed, Typeofwepon item) :
            Wepon(damage, attackspeed, item) 
        {}

        void attack()
        {
            check();
            cout << " pu pu pu" << endl;
        }

};

class Sword : public Wepon
{
    public: 
        
        Sword (double damage, double attackspeed, Typeofwepon item ) :
            Wepon(damage, attackspeed, item) 
        {}

        void attack()
        {
            check();
            cout << " dzn dzn " << endl;
        }
};

class Shop 
{
    private:
        int numberofwepon;
        Wepon** wepons;
        Wepon* creatWepon()
        {
            const double UPPER_BOUND = 20;
            const double LOWER_BOUND = 2; 
            if( (double)(rand()) / RAND_MAX * UPPER_BOUND > 10)
            {
                return new Sword((double)(rand()) / RAND_MAX * UPPER_BOUND + LOWER_BOUND, (double)(rand()) / RAND_MAX * UPPER_BOUND + LOWER_BOUND, SWORD );
            }
            else
            {
                return new Pistol((double)(rand()) / RAND_MAX * UPPER_BOUND + LOWER_BOUND, (double)(rand()) / RAND_MAX * UPPER_BOUND + LOWER_BOUND, PISTOL );
            }


        } 
    public:

        Shop (int numberofwepon ) : numberofwepon(numberofwepon)
        {
            wepons = new Wepon* [numberofwepon];
            
            for (int i = 0; i < numberofwepon; i++)
            {
                wepons[i] = creatWepon();
            }
        }
        void takeWepons(const int PROBABILITY)
        { 
            const int UPPER_BOUND = 1001;
            for(int i = 0; i < numberofwepon; i++)
            {

                if(wepons[i]->getItem() == SWORD)
                {
                    ((Sword*) wepons[i])->attack();
                }
                else
                {
                    ((Pistol*) wepons[i])->attack();
                }
                cout << " скорость атаки:" << wepons[i]->damagePerSecond() << endl;
                cout << "--------------" <<endl;                
                if (rand() % UPPER_BOUND < PROBABILITY)
                {
                    cout << "мне понравилось  оружие с номером: " << i << endl;
                    break;

                }
            }
              
        }

        ~Shop()
        {
            for(int i = 0; i < numberofwepon; i++)
            {
                delete wepons[i];
            }
            delete[] wepons;
        }

};

int main()
{
    int N;
    srand( time(0) );
    cin >> N;
    Shop* s = new Shop(N);
    const int PROBABILITY = 5;
    s->takeWepons(PROBABILITY);
    delete s;
    return 0;
}