#include <iostream>
#include <ctime>
#include <vector>
enum TowerStatus
{
    RUIN,
    NOTRUIN,
};
enum AttackOptions
{
    ATTACKTILLEXTINCTION = 1,
    RANDOMATTACK,
};

using namespace std;


class Tower
{
    private:
    int durability = 1000;
    int dameg;
    TowerStatus status = NOTRUIN;
    void generatDameg()
        {
            const int UPPER_BOUND = 126;
            const int LOWER_BOUND = 75;
            dameg = rand() % (UPPER_BOUND - LOWER_BOUND) + LOWER_BOUND;
        }

    public:
    int attack()
    {
        generatDameg();
        return dameg;
    }


    void getDameg(int dragondameg)
    {
        durability -= dragondameg;
        if (durability <= 0)
        {
            status = RUIN;
        }
    }
    TowerStatus getStatus()
    {
        return status;
    }
    int getDurability()
    {
        return durability;
    }


};


class Castle
{
    private:
    const int numberoftowers = 10;
    Tower* towers;
    int alldragondameg = 0;
    int alltowerdameg = 0;

    public:

    Castle()
    {
        towers = new Tower[numberoftowers];
    }
    void infoCastle()
    {
        for(int i = 0; i < numberoftowers; i++)
        {
            if(isTowerAlive(i))
            {
                cout << i + 1 << ") прочность башни: " << towers[i].getDurability() << endl;
            }
        }
    }
    bool isTowerAlive(int index)
    {
        if(towers[index].getStatus() == NOTRUIN)
        {
            return true;
        }
        return false;

    }
    bool isAlive()
    {
        for(int i = 0; i < numberoftowers; i++)
        {
            if(isTowerAlive(i))
            {
                return true;
            }
        }
        return false;
    }
    int defense(int index)
    {
        int dameg = 0;
        for( int i = -3; i < 4; i++ )
        {
            int twindex = (index  + i > -1 && index + i < numberoftowers) ? index + i : abs(numberoftowers - abs(index + i));
            if (isTowerAlive(twindex))
            {
                dameg += towers[twindex].attack();
            }
        }
        alltowerdameg += dameg;
        return dameg;
    }
    void getDameg(int index, int* dameg)
    {
        for (int i = -1; i < 2; i++)
        {
            int twindex = (index  + i > -1 && index + i < numberoftowers) ? index + i : abs(numberoftowers - abs(index + i));
            if (isTowerAlive(twindex))
            {
                towers[twindex].getDameg(dameg[i + 1]);
                alldragondameg += dameg[i + 1];
            }
        }

    }
    int getAllDragonDameg()
    {
        return alldragondameg;
    }
    int getAllTowerDameg()
    {
        return alltowerdameg;
    }
    ~Castle()
    {
        delete[] towers;
    }
};
class Dragon
{
    private:
        int health = 3000;
        const int NUMBEROFHEAD = 3;
        int* dameg = new int[NUMBEROFHEAD];

        void generatDameg()
        {
            const int UPPER_BOUND = 1001;
            const int LOWER_BOUND = 334;
            for (int i = 0; i < NUMBEROFHEAD; i++) dameg[i] = rand() % (UPPER_BOUND - LOWER_BOUND) + LOWER_BOUND;

        }
    public:
        bool isAlive()
        {
            if (health <= 0)
            {
                return false;
            }
            return true;
            
        }
        int generatTwindex(const int UPPER_BOUND)
        {
            
            return rand() %UPPER_BOUND;

        }
        void getDameg(int damegtower)
        {
            health -= damegtower;
        } 
        int* attack()
        {
            generatDameg();
            return dameg;
            
        }
        int getHelth()
        {
            return health;
        }
        ~Dragon()
        {
            delete[] dameg;
        }
};

class BattleGround
{
    private:
        Dragon* dragon;
        Castle* castle;
        int twindex;
        void info()
        {
            if(!dragon->isAlive())
            {
                castle->infoCastle();
            }
            else
            {
                cout << " здоровьё дракона: " << dragon->getHelth() << endl;
            }
            cout << " урон полуеный замком " << castle->getAllDragonDameg() << " урон нанасеный дракону равен " << castle->getAllTowerDameg() << endl;
            
        }

    public:
        BattleGround()
        {
            dragon = new Dragon;
            castle = new Castle;
        }
        void generatTwindex()
        {
            do
            {
                twindex = dragon->generatTwindex(10);
                
            } while (!castle->isTowerAlive(twindex));
        }
        void battle(int variant)
        {
            generatTwindex();
            while (dragon->isAlive())
            {
                int* dragondameg = dragon->attack();
                castle->getDameg(twindex, dragondameg);
                if (castle->isAlive())
                {
                    int castledameg = castle->defense(twindex);
                    dragon->getDameg(castledameg);
                    if( variant == ATTACKTILLEXTINCTION )
                    {
                        if (!castle->isTowerAlive(twindex))
                        {
                            generatTwindex();
                        }
                    }
                    else
                        generatTwindex();
                }
                else
                    break;
            }
            info();

        }
        ~BattleGround()
        {
            delete dragon;
            delete castle;
        }

};






int main()
{
    srand( time(0) );
    int N;
    cout << "выберете тип атака \n 1.атаковать пока башня не будет уничтожина \n 2.атаковать случайным образом \n ";
    cin >> N;
    BattleGround* b = new BattleGround ();
    b->battle(N);
    delete b;

    
    return 0;
} 