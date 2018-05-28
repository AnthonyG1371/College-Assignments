#include<iostream>
#include<stdlib.h>
#include <queue>
#include "sorttiming.h"
using namespace std;

const int SIZE1 = 100, SIZE2 = 10000, SIZE3 = 100000;

int main()
{
    int size;
    Timer ctimer;
	ctimer.setflag();

    for(int loops = 0; loops < 3; loops++)
    {
        if(loops == 0)
        {
            size = SIZE1;
        }
        else if(loops == 1)
            size = SIZE2;
        else
            size = SIZE3;
        
        int arr1[size];

        cout << "Timing Bubble Sort of size " << size << endl;
        ctimer.start();
    
        for (int i = 0; i < size; i++)
	        arr1[i] = rand();
    
        sort(arr1, size);
    
//    for (int i = 0; i < size; i++)
//	    cout << "Index " << i << ": " << arr1[i] << endl;
    
        ctimer.end();
        cout << "Time Taken for BubbleSort: " << ctimer << endl << endl;
    
        //PRIORITY QUEUE

    	int *arr2 = new int[size];

        for (int i = 0; i < size; i++)
	        arr2[i] = rand();

    	priority_queue<int> pq;
	
        cout << "Timing Priority Queue Sort of size " << size << endl;
        ctimer.start();
	
	    for (int i = 0; i < size; i++)
		    pq.push(arr2[i]);
	
	    for (int i = size-1; i >= 0; i--) 
        {
		    arr2[i] = pq.top();
		    pq.pop();
        }

//	for (int i = 0; i < size; i++) 
//	    cout << "Index " << i << ": " << arr4[i] << endl;
    
        ctimer.end();
        cout << "Time Taken for Priority Queue Sort: " << ctimer << endl;
    
        cout << endl;
    }
    
    return(0);
}
