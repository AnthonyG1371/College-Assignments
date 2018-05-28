#include<iostream>
#include "arrayseq.h"
using namespace std;

int main()
{
    int arr[] = {0,4,1,3,2};
    int size = 5;
    int element;
    
    cout << "Initial Array" << endl;
    for(int i = 0; i < size; i++)
    {
        cout << arr[i] << endl;
    }
    
    cout << endl << "Testing Add, Get, and Remove Back" << endl;    
    add_back(arr, size, 1); //Add Back
    cout << back(arr, size) << endl; //Get Back
    remove_back(arr, size); //Remove Back

    cout << endl << "Testing Add, Get, and Remove Front" << endl;  
    add_front(arr, size, 2); //Add Front
    cout << front(arr, size) << endl; //Get Front
    remove_front(arr, size); //Remove Front
    
    cout << endl << "Testing Find for the number 2" << endl;
    cout << "Found at location " << find(arr, size, 2) << endl; //Find
    
    //Search
    cout << endl << "Testing if a number is found" << endl;
    cout << "Enter a number: ";
    cin >> element;
    
    if(search(arr, size, element) == true)
        cout << "It was found" << endl;
    else
        cout << "Sorry, it is not in the array" << endl;
    
    //Sort    
    cout << endl << "The array will now be sorted" << endl;
    sort(arr, size);
    
    cout << "Sorted Array" << endl;
    for(int i = 0; i < size; i++)
    {
        cout << get(arr, size, i) << endl;  //Get
    }

    return(0);
}
