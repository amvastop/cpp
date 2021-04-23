#include<iostream>
#include <ctime>
using namespace std;


class  Monster
{ 
    public:
        int health;
        const int UPPER_BOUND = 11;
        Monster()
        {
            srand( time(0) );
            health = rand() % UPPER_BOUND;

        }
        int takingDamage(double damage)
        {
           return health -= damage;
            
        }


};



class Pistol
{
    public: 
        double damage;
        double attackspeed;


        Pistol (double damage, double attackspeed ) : damage(damage), attackspeed(attackspeed) {}


        void attack()
        {
            
            cout << "урон пистолетом : " << damage << endl;
           
        }
        void calculatingDamagePerMinute()
        {
            double time = 60;
            double demageperminute = (damage * time) / attackspeed;
            cout << "урон пистолетом в минуту " << demageperminute << endl;
        }

        void attackEnemy(Monster& monster)
        {
            
            if (monster.takingDamage(damage) <= 0)
            {
                cout << "монстр умер" << endl;

            }
            else
            {
                cout << "здоровье монстра :" << monster.health << endl;
            }

        }




};

class Sword
{
    public: 
        double damage;
        double attackspeed;


        Sword (double damage, double attackspeed ) : damage(damage), attackspeed(attackspeed) {}


        void attack()
        {
            cout << "урон мечем: " << damage << endl;
            
        }

        void calculatingDamagePerMinute()
        {
            double time = 60;
            double demageperminute = (damage * time) / attackspeed;
            cout << "урон пистолетом в минуту " << demageperminute << endl;
        }
        void attackEnemy(Monster& monster)
        {
            if (monster.takingDamage(damage) <= 0)
            {
                cout << "монстр умер" << endl;

            }
            else
            {
                cout << "здоровье монстра :" << monster.health << endl;
            }
        }




};

int main()
{
    
    Pistol arraypistols[3] = { Pistol(3, 3), Pistol(2,5), Pistol(1, 2) };
    Sword arraysword[3] = { Sword(5, 3), Sword(6, 5), Sword(1, 2) };
    Monster monster;

    for (int i = 0; i < 3; i++ )
    {
        arraypistols[i].attackEnemy(monster);
        arraysword[i].attackEnemy(monster);
    }
    return 0;
}
