#ifndef SEQTIMING_H
#define SEQTIMING_H
#include<string>
#include<ctime>
using namespace std;

void addback(int [], int &, int);
void set(int [], int &, int, int);

class Timer
{    
    friend ostream &operator <<(ostream &os, Timer t) 
    {
        os << t.setstring(t.getetime());
        return os;
	}
     
    public:
        int ticks(clock_t t);
        int seconds(clock_t t);
        int minutes(clock_t t);
        int hours(clock_t t);   
           
        void start();
        void end();
        clock_t getstime();
        clock_t getetime();
        void setflag();
        string setstring(clock_t t);
    
    private:
        clock_t stime;
        clock_t etime;  
        bool startflag;
};

#endif
