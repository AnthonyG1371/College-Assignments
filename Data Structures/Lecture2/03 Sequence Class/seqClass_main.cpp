#include<iostream>
#include "seqClass.h"
using namespace std;

int main()
{
    Sequence seq(5);
    int element;
    
    cout << "Initial Array" << endl;
    for(int i = 0; i < seq.getsize(); i++)
    {
        cout << seq.get(i) << endl;
    }
    
    cout << endl << "Testing Add, Get, and Remove Back" << endl;    
    try
    {
        seq.add_back(1); //Add Back
    }
    catch (string s) 
    {
        cout << "Exception: " << s << endl;
    }
    cout << seq.back() << endl; //Get Back
    try
    {
        seq.remove_back(); //Remove Back
    }
    catch (string s)
    {
        cout << "Exception: " << s << endl;
    }

    cout << endl << "Testing Add, Get, and Remove Front" << endl;  
    try
    {
        seq.add_front(2); //Add Front
    }
    catch (string s) 
    {
        cout << "Exception: " << s << endl;
    }
    cout << seq.front() << endl; //Get Front
    try
    {
        seq.remove_front(); //Remove Front
    }
    catch (string s) 
    {
        cout << "Exception: " << s << endl;
    }
    
    cout << endl << "Testing Find for the number 2" << endl;
    cout << "Found at location " << seq.find(2) << endl; //Find
    
    //Search
    cout << endl << "Testing if a number is found" << endl;
    cout << "Enter a number: ";
    cin >> element;
    
    if(seq.search(element) == true)
        cout << "It was found" << endl;
    else
        cout << "Sorry, it is not in the array" << endl;
    
    //Sort    
    cout << endl << "The array will now be sorted" << endl;
    seq.sort();
    
    cout << "Sorted Array" << endl;
    for(int i = 0; i < seq.getsize(); i++)
    {
        cout << seq.get(i) << endl;  //Get
    }
    
    return(0);
}
