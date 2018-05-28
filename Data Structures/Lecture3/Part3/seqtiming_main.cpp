#include<iostream>
#include<stdlib.h>
#include"seqtiming.h"
using namespace std;

const int CAPACITY = 100000;

int main()
{
    int endindex = 0;
    int arr[CAPACITY];
    int arr2[CAPACITY];
    int size = CAPACITY;
    Timer ctimer;
   	ctimer.setflag();
    
    
    try
    {
        //TIMING ADD BACK FUNCTION
	    ctimer.start();
        for(int i = 0; i < CAPACITY; i++)
        {
            addback(arr, endindex, i);
        }
        ctimer.end();
        cout << "Time taken for the Add_Back function: " << endl;
        cout << ctimer << endl;
        
        //TIMING INSERT/SET FUNCTION
   	    ctimer.start();
        for(int i = 0; i < CAPACITY; i++)
        {
            int element = rand() % 10000;
            set(arr2, size, element, i);
        }
        ctimer.end();
        cout << "Time taken for the Insert function: " << endl;
        cout << ctimer << endl;
    }
    catch(string s)
    {
        cout << s << endl;
    }
    
/*  CODE TO PRINT OUT THE ARRAYS, BUT PRINTING OUT THE ARRAYS SHOULD TAKE THE
    SAME AMOUNT OF TIME FOR BOTH, AND IT'LL TAKE A WHILE, SO IT WAS OMITTED
    for(int i = 0; i < size; i++)
    {
        cout << arr[i] << endl;
    }
*/
    return(0);
}
