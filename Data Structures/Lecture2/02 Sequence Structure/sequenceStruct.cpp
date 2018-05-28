#include<iostream>
#include "seqStruct.h"
using namespace std;

void initialize(Sequence &seq) 
{
    seq.size = 5;
    seq.arr[0] = 0;
    seq.arr[1] = 4;
    seq.arr[2] = 1;
    seq.arr[3] = 3;
    seq.arr[4] = 2;
}

//Get Function
int get(Sequence &seq, int element)
{
    if(element < 0  || element > seq.size)
    {
        cout << "Element not found" << endl;
        return 0;
    }
    return seq.arr[element];
}

//Set Function
void set(Sequence &seq, int element, int index)
{
     if(seq.size < 0 || element > seq.size)
     {
         cout << "Set at that point is impossible" << endl;
     }
     else
     {
         seq.arr[index] = element;
     }
}

//Find Function: Value at Location
int find(Sequence &seq, int element)
{
    int position = -1;
    
    for(int i = 0; i < seq.size; i++)
    {
        if(seq.arr[i] == element)
        {
           position = i;
           return position;
        }
    }
    
    cout << "Not found" << endl;
}

//Search Function: Found or Not
bool search(Sequence &seq, int element)
{
     bool found = false;
     
     for(int i = 0; i < seq.size; i++)
     {
         if(seq.arr[i] == element)
             found = true;
     }
     
     return found;
}

//Add to Back: Adds an element to the back of the array
void add_back(Sequence &seq, int index)
{
     seq.arr[seq.size++] = index;
}

//Remove from Back: Removes last element in array
void remove_back(Sequence &seq)
{
     seq.size--;
}

//Add to Front: Inserts an input to the front of an array and increases the array's size
void add_front(Sequence &seq, int element)
{
     seq.size++;
     
     for(int i = seq.size; i > 0; i--)
     {
         seq.arr[i] = seq.arr[i-1];
     }

     seq.arr[0] = element;
}

//Remove from Front: Removes first element in array
void remove_front(Sequence &seq)
{
     for(int i = 0; i < seq.size; i++)
     {
         seq.arr[i] = seq.arr[i+1];
     }
     seq.size--;
}

//First Query: Returns first element in array
int front(const Sequence &seq)
{
    return seq.arr[0];
}

//Last Query: Returns last element in array
int back(const Sequence &seq)
{
    return seq.arr[seq.size - 1];
}

//Sort by Bubblesort
void sort(Sequence &seq)
{
    for(int last = seq.size-1; last > 0; last--)
    {
		for (int i = 0; i < last; i++)
			if (seq.arr[i] > seq.arr[i+1])
				swap(seq.arr[i], seq.arr[i+1]);
	}
}
