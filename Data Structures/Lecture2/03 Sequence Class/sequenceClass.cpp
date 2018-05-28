#include<iostream>
#include<sstream>
#include "seqClass.h"
using namespace std;

int Sequence::getsize()
{
    return size;
}

//Get Function
int Sequence::get(int element)
{
    if(element < 0  || element > size)
    {
        cout << "Element not found" << endl;
        return 0;
    }
    return arr[element];
}

//Set Function
void Sequence::set(int element, int index)
{
     if(size < 0 || element > size)
     {
         cout << "Set at that point is impossible" << endl;
     }
     else
     {
         arr[index] = element;
     }
}

//Find Function: Value at Location
int Sequence::find(int element)
{
    int position = -1;
    
    for(int i = 0; i < size; i++)
    {
        if(arr[i] == element)
        {
           position = i;
           return position;
        }
    }
    
    cout << "Not found" << endl;
}

//Search Function: Found or Not
bool Sequence::search(int element)
{
     bool found = false;
     
     for(int i = 0; i < size; i++)
     {
         if(arr[i] == element)
             found = true;
     }
     
     return found;
}

//Add to Back: Adds an element to the back of the array
void Sequence::add_back(int index)
{
    if (size >= CAPACITY) {
		ostringstream oss;
		oss << "Overflow error. Array is at max capacity(" << CAPACITY << ")" ;
		throw oss.str();
	}
     
     arr[size++] = index;
}

//Remove from Back: Removes last element in array
void Sequence::remove_back()
{
    if (size == 0) {
		ostringstream oss;
		oss << "Error. Array cannot be shrunk. To less than 0";
		throw oss.str();
	}
     
     size--;
}

//Add to Front: Inserts an input to the front of an array and increases the array's size
void Sequence::add_front(int element)
{
    if (size >= CAPACITY) {
		ostringstream oss;
		oss << "Overflow error. Array is at max capacity(" << CAPACITY << ")" ;
		throw oss.str();
	}
     
     size++;
     
     for(int i = size; i > 0; i--)
     {
         arr[i] = arr[i-1];
     }

     arr[0] = element;
}

//Remove from Front: Removes first element in array
void Sequence::remove_front()
{
    if (size == 0) {
		ostringstream oss;
		oss << "Error. Array cannot be shrunk. To less than 0";
		throw oss.str();
	}     
     
     for(int i = 0; i < size; i++)
     {
         arr[i] = arr[i+1];
     }
     size--;
}

//First Query: Returns first element in array
int Sequence::front()
{
    return arr[0];
}

//Last Query: Returns last element in array
int Sequence::back()
{
    return arr[size - 1];
}

//Sort by Bubblesort
void Sequence::sort()
{
    for(int last = size-1; last > 0; last--)
    {
		for (int i = 0; i < last; i++)
			if (arr[i] > arr[i+1])
				swap(arr[i], arr[i+1]);
	}
}
