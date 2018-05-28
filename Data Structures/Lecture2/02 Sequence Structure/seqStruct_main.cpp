#include<iostream>
#include "seqStruct.h"
using namespace std;

int main()
{
    Sequence seq;
    initialize(seq);
    int element;
        
    cout << "Initial Array" << endl;
    for(int i = 0; i < seq.size; i++)
    {
        cout << seq.arr[i] << endl;
    }    

    cout << endl << "Testing Add, Get, and Remove Back" << endl;           
    add_back(seq, 1); //Add Back
    cout << back(seq) << endl; //Get Back
    remove_back(seq); //Remove Back

    cout << endl << "Testing Add, Get, and Remove Front" << endl; 
    add_front(seq, 2); //Add Front
    cout << front(seq) << endl; //Get Front
    remove_front(seq); //Remove Front
    
    cout << endl << "Testing Find for the number 2" << endl;
    cout << "Found at location " << find(seq, 2) << endl; //Find
    
    //Search
    cout << endl << "Testing if a number is found" << endl;    
    cout << "Enter a number: ";
    cin >> element;
    
    if(search(seq, element) == true)
        cout << "It was found" << endl;
    else
        cout << "Sorry, it is not in the array" << endl;
    
    //Sort   
    cout << endl << "The array will now be sorted" << endl; 
    sort(seq);
    
    cout << "Sorted Array" << endl;
    for(int i = 0; i < seq.size; i++)
    {
        cout << get(seq, i) << endl;  //Get
    }
    
    return(0);
}
