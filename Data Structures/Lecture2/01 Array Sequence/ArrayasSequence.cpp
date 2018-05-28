#include<iostream>
#include "arrayseq.h"
using namespace std;

//Get Function
int get(int arr[], int &size, int element)
{
    if(element < 0  || element > size)
    {
        cout << "Element not found" << endl;
        return 0;
    }
    return arr[element];
}

//Set Function
void set(int arr[], int &size, int element, int index)
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
int find(int arr[], int &size, int element)
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
bool search(int arr [], int &size, int element)
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
void add_back(int arr[], int &size, int index)
{
//     size++;
     arr[size++] = index;
/*     for(int i = 0; i < size; i++)
     {
         cout << arr[i] << endl;
     }*/
}

//Remove from Back: Removes last element in array
void remove_back(int arr[], int &size)
{
     size--;
}

//Add to Front: Inserts an input to the front of an array and increases the array's size
void add_front(int arr[], int &size, int element)
{
     size++;
     
     for(int i = size; i > 0; i--)
     {
         arr[i] = arr[i-1];
     }
     
     arr[0] = element;
}

//Remove from Front: Removes first element in array
void remove_front(int arr[], int &size)
{
     for(int i = 0; i < size; i++)
     {
         arr[i] = arr[i+1];
     }
     size--;
}

//First Query: Returns first element in array
int front(const int arr[], int size)
{
    return arr[0];
}

//Last Query: Returns last element in array
int back(const int arr[], int size)
{
    return arr[size - 1];
}

//Sort by Bubblesort
void sort(int arr[], int &size)
{
    for(int last = size-1; last > 0; last--)
    {
		for (int i = 0; i < last; i++)
			if (arr[i] > arr[i+1])
				swap(arr[i], arr[i+1]);
	}
}
