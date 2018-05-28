#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
#include "sorttiming.h"
using namespace std;

//BUBBLESORT
void sort(int arr[], int n)
{
	for (int last = n-1; last > 0; last--)
    {
		for (int i = 0; i < last; i++)
			if (arr[i] > arr[i+1])
				swap(arr[i], arr[i+1]);
	}
}

//SWAP
void swap(int &a, int &b) 
{
	int t = a;
	a = b;
	b = t;
}

//TIMER CODE
const int 
	SECONDS_PER_MINUTE = 60,
	MINUTES_PER_HOUR = 60;

int Timer::ticks(clock_t t) 	{return t % CLOCKS_PER_SEC;}
int Timer::seconds(clock_t t) 	{return t / CLOCKS_PER_SEC % SECONDS_PER_MINUTE;}
int Timer::minutes(clock_t t) 	{return t / CLOCKS_PER_SEC / SECONDS_PER_MINUTE % MINUTES_PER_HOUR;}
int Timer::hours(clock_t t) 	{return t / CLOCKS_PER_SEC / SECONDS_PER_MINUTE / MINUTES_PER_HOUR;}

void Timer::start()
{
    if(startflag)
    {
        ostringstream oss;
        oss << "Error: Cannot start a stopwatch that is running";
        throw oss.str();
    }
    stime = 0;
    etime = 0;
    startflag = true;
}

void Timer::end()
{
    if(!startflag)
    {
        ostringstream oss;
        oss << "Error: Cannot stop a stopwatch that wasn't started";
        throw oss.str();
    }
    etime = clock() - etime;
    startflag = false;
}

clock_t Timer::getstime()
{
    if(startflag)
    {
        ostringstream oss;
        oss << "Error: Cannot retrieve values while the stopwatch is running";
        throw oss.str();
    }
    return(stime);        
}

clock_t Timer::getetime()
{
    if(startflag)
    {
        ostringstream oss;
        oss << "Error: Cannot retrieve values while the stopwatch is running";
        throw oss.str();
    }
    return(etime);
}

void Timer::setflag()
{
    startflag = false;
}

string Timer::setstring(clock_t t) 
{
	ostringstream oss;
	oss << setfill('0') << setw(2) << hours(t) << ":" << setw(2) << minutes(t) << ":" << setw(2) << seconds(t) << ":" << setw(2) << ticks(t);
	return oss.str();
}
