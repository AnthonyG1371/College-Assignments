#include <iostream>
#include "clock.h"
using namespace std;

int main() 
{
	cout << "Clock ticks per second: " << CLOCKS_PER_SEC << endl;
	
	Timer ctimer;
	ctimer.setflag();
	ctimer.start();
	
	//JUST TRIES THE PROVIDED LOOP AND PRINTS THE TIME.
	cout << "Processing a loop. Please wait..." << endl;
	
    try
    {
	    for (int i = 0; i < 1000; i++)
		    for (int j = 0; j < 1000000; j++)
			    i / 17;
	    ctimer.end();

    cout << "Time to process a certain For Loop: " << ctimer << endl;

    }
    catch(string s)
    {
        cout << s << endl;
    }

	return 0;
}
