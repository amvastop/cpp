#include <iostream>
#include <utility>
#include <ctime>
#include <queue> 
#include <algorithm>
#include <cmath>
#include <windows.h>
#include <conio.h>
using namespace std;
enum Comand
{
    FIRSTTEAM,
    SECONDTEAM,
};
class Footballer
{
    private:
        int strength;
        pair<int, int>  coordinates;
        bool haveaball = false;
        bool isplaing = true;
        int energy;
        const int UPPERBOUND = 100;
        const int LOWERBOUND = 1;
    public:

     
        Footballer()
        {
            strength = rand() % (UPPERBOUND - LOWERBOUND) + LOWERBOUND;
            energy = rand() % (UPPERBOUND - LOWERBOUND) + LOWERBOUND;
        }
        bool takeAwayBall(int strengthseconplayer)
        {
            if(isplaing)
            {
                int i = rand() % (UPPERBOUND - LOWERBOUND) + LOWERBOUND;
                if(i <= (50 + (strength - strengthseconplayer) / 2))
                {
                    haveaball = true;
                    return true;
                }
            }
            return false;
        }
        void move(const int UPPERBOUNDWIDTH, const int LOWERBOUNDWIDTH, const int HEIGHT)
        {
            if(isplaing)
            {
                coordinates = make_pair(rand() % (UPPERBOUNDWIDTH - LOWERBOUNDWIDTH ) + LOWERBOUNDWIDTH, rand() % (HEIGHT ));
            }
        }
        void setCoordinates(int x, int y)
        {
            coordinates = make_pair(x, y);
        }

        pair<int, int> getcoordinates()
        {
            return coordinates;
        }
        bool setEnergy(int N)
        {
            
            if (!isplaing && N < 0)
                return true;
            energy += N;
            isplaing = energy ? true : false ;
            if (!energy && haveaball)
            {
                haveaball = false;
                throw -1;
            }
            
            return isplaing ;
        }
        bool isPlaying()
        {
           return isplaing ; 
        }
        bool takeBall()
        {
            if (isplaing)
            {
                haveaball = true;
                return true;
            }
            return false;
        }
        int getStrength()
        {
            return strength;
        }
        void loseBall()
        {
            haveaball = false;
        }
        bool haveball()
        {
            return haveaball;
        }
};


class Match
{
    private:
        const int numberofplayers = 11;
        Footballer* firstteam = new Footballer[numberofplayers];
        Footballer* secondteam = new Footballer[numberofplayers];
        queue<pair<int, vector<Footballer*>>>  timeoutplayers;
        const int WIDTH = 50;
        const int HEIGHT = 30;
        const int TIMEOUT = 10;
        const int TIMEOFROUND = 5;
        int goalfirstteam = 0;
        int goalsecondteam = 0;
        bool firstteamtimeout = false;
        bool secondteamtimeout = false;
        bool noonehavebool = false;
        Footballer* plaerhaveboll;
        vector<Footballer*> gropoftimeoutplayer;
        int teamhevaboll;
        bool matchstarted = false;
    public:
        void moveTeam (Footballer* team, const int UPPERBOUNDWIDTH, const int LOWERBOUNDWIDTH = 0)
        {
            if (!matchstarted)
                team[numberofplayers - 1].setCoordinates(LOWERBOUNDWIDTH ? UPPERBOUNDWIDTH - 1 : LOWERBOUNDWIDTH, HEIGHT / 2  );
            for(int i = 0; i < numberofplayers - 1; i++)
            {
                team[i].move(UPPERBOUNDWIDTH, LOWERBOUNDWIDTH, HEIGHT );
            }


        }
        bool giveBall(int comand)
        {
            Footballer* team = comand ? secondteam : firstteam;
            int i = rand() % (numberofplayers - 1);
            if(!team[i].takeBall())
                return false;
            plaerhaveboll = &team[i];
            teamhevaboll = comand;
            return true;

        }
        void show()
        {
            for (int i = 0; i < WIDTH * 2 + 1; i++)
                cout << "_";
            cout<< endl;
            for (int i = 0; i < HEIGHT; i++)
            {
                for (int j = 0; j < WIDTH ; j++)
                {
                    cout << "|" ;
                    int players = 0;
                    bool playeroffirstteam = false;
                    bool playerofsecondteam = false;
                    for(int k = 0; k < numberofplayers; k++)
                    {
                        
                        if(firstteam[k].getcoordinates() == make_pair(j, i))
                        {
                            players++;
                            playeroffirstteam = true;
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | COMMON_LVB_UNDERSCORE);// красная команда
                            if(firstteam[k].haveball())
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x14 | COMMON_LVB_UNDERSCORE);
                            
                        }
                        if(secondteam[k].getcoordinates() == make_pair(j, i))
                        {
                            players++;
                            playerofsecondteam = true;
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2 | COMMON_LVB_UNDERSCORE);//зеленая команда
                            if(secondteam[k].haveball())
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x14 | COMMON_LVB_UNDERSCORE);
                        }
                        if (playeroffirstteam && playerofsecondteam)
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5 | COMMON_LVB_UNDERSCORE);

                    }
                    cout << players;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8 | COMMON_LVB_UNDERSCORE);  
                }
                cout << '|';
                cout<< endl;
            }
            cout << endl;
            
        }
        void randBall()
        {
            
            bool flagoftakingball;
            do
            {
                if(rand() % 2)
                {
                    flagoftakingball = giveBall(FIRSTTEAM);
                }  
                else
                {
                    flagoftakingball = giveBall(SECONDTEAM);
                }
            }
            while(!flagoftakingball);
            noonehavebool = false;
        }
       
        Match()
        {
            moveTeam(firstteam, WIDTH / 2);
            moveTeam(secondteam, WIDTH, WIDTH / 2 + 1);
            matchstarted = true;
            cout << firstteam[numberofplayers - 1].getcoordinates().first << firstteam[numberofplayers - 1].getcoordinates().second ;
            randBall();
            
        }
        void exitTimeOut()
        {

            int n = gropoftimeoutplayer.size() ;
            if(!timeoutplayers.empty())
            {
                timeoutplayers.front().first -= TIMEOFROUND;
                if(!timeoutplayers.front().first)
                {   
                     for_each(timeoutplayers.front().second.begin(), timeoutplayers.front().second.end(), [] (Footballer* plaer) {plaer->setEnergy(20);});
                    timeoutplayers.pop();
                }
                if(!gropoftimeoutplayer.size())
                    return;
                timeoutplayers.push(make_pair(TIMEOUT - timeoutplayers.front().first, gropoftimeoutplayer));
            }   
            else
            {
                if(gropoftimeoutplayer.size())
                    timeoutplayers.push(make_pair(TIMEOUT, gropoftimeoutplayer));
            }
            gropoftimeoutplayer.clear();
        }
        void takingBoll()
        {
            Footballer* team = teamhevaboll ? firstteam : secondteam;
            pair<int, int>  coordinates = plaerhaveboll->getcoordinates();
            for(int i = 0; i < numberofplayers - 1; i++)
            {
                pair<int, int>  coordinatessecond = team[i].getcoordinates();
                if(coordinates == coordinatessecond)
                    if(team[i].takeAwayBall(plaerhaveboll->getStrength()))
                    {
                        plaerhaveboll->loseBall();
                        plaerhaveboll = &team[i];
                        teamhevaboll = teamhevaboll ? FIRSTTEAM : SECONDTEAM;
                        return;
                    }
            }
        }
        void kickOnGoal()
        {
            Footballer* team = teamhevaboll ? firstteam : secondteam;
            pair<int, int>  coordinates = plaerhaveboll->getcoordinates();
            pair<int, int>  coordinatesgoalkeeper = team[10].getcoordinates();
            double d = sqrt(pow((coordinates.first) - (coordinatesgoalkeeper.first), 2) + pow((coordinates.second) - (coordinatesgoalkeeper.second), 2));
            if (d <= 5)
            {
                if(!team[numberofplayers - 1].takeAwayBall(plaerhaveboll->getStrength()))
                {
                    if (teamhevaboll)
                        goalsecondteam++;
                    else
                        goalfirstteam++;
                    cout << goalfirstteam << " : " << goalsecondteam << endl;
                    
                }
                plaerhaveboll->loseBall();
                bool flagoftakingball;
                if(firstteamtimeout || secondteamtimeout)
                    randBall();
                else
                {
                    do
                     flagoftakingball = giveBall(teamhevaboll ? FIRSTTEAM : SECONDTEAM);
                    while(!flagoftakingball);
                }
                
                team[numberofplayers - 1].loseBall();
                return;
            }

        }
        void fatigue(int comand)
        {
            Footballer* team = comand ? secondteam : firstteam;
            for(int i = 0; i < numberofplayers - 1; i++)
            {
                try
                {
                    if(!team[i].setEnergy(-1))
                        gropoftimeoutplayer.push_back(&team[i]);
                }
                catch(int)
                {
                    gropoftimeoutplayer.push_back(&team[i]);
                    noonehavebool = true;
                }
            }
        }
        void checkPlayers()
        {
            int nuberoftimoutplaers = 0;
            for(int i = 0; i < numberofplayers - 1; i++)
                if (!firstteam[i].isPlaying())
                    nuberoftimoutplaers++;
            firstteamtimeout = nuberoftimoutplaers == (numberofplayers - 1) ? true : false;
            nuberoftimoutplaers = 0;
            for(int i = 0; i < numberofplayers - 1; i++)
                if (!secondteam[i].isPlaying())
                    nuberoftimoutplaers++;
            secondteamtimeout = nuberoftimoutplaers == (numberofplayers - 1) ? true : false;
            if(firstteamtimeout && secondteamtimeout && !timeoutplayers.empty() )
            {
                timeoutplayers.front().first = 5;
                exitTimeOut();
                checkPlayers();
            }

            
        }

        void play()
        {
            int step = 0;
            while(step != 60)
            {
                
                for(int i = 0; i < TIMEOFROUND; i++)
                {
                    step++;
                    //  for (int i = 0; i < numberofplayers-1; i++ )
                    //  {
                    //      cout << i+1 << ")\t" << firstteam[i].energy<< "\t" << firstteam[i].haveaball<< "\t" << firstteam[i].getcoordinates().first<< "\t" << firstteam[i].getcoordinates().second << "\t|\t"
                    //      << secondteam[i].energy<< "\t" << secondteam[i].haveaball<< "\t" << secondteam[i].getcoordinates().first<< "\t" << secondteam[i].getcoordinates().second << endl;
                    // }
                    cout << endl;
                    moveTeam(firstteam, WIDTH);
                    moveTeam(secondteam, WIDTH);
                    show();
                    takingBoll();
                    kickOnGoal();

                }
                
                fatigue(FIRSTTEAM);
                fatigue(SECONDTEAM);
                exitTimeOut();
                checkPlayers();
                if(noonehavebool)
                    randBall();
            }
            cout << step;
        }

        ~Match()
        {
            delete[] firstteam;
            delete[] secondteam;
        }

};
int main()
{
    srand(time( 0 ));
    unsigned int start_time = clock();
    Match m;
    m.play();
    unsigned int end_time = clock(); // конечное время
    cout << "время матча: "<< (end_time - start_time)/1000.0 << " секунд"<< endl;
    return 0;
}
