#include<iostream>
#include<fstream>
using namespace std;

ifstream infile;

int main()
{
    int input = -1, size, totalval = 0, totalinput = 0;
    int lvalues = 0;
    double average;
    int *arr = new int[10];
    size = 10;
    
   	infile.open("n_10000.input");
    
    if (infile.fail()) {
	 cout << "\nError. File not found" << endl;
	}

    while(!infile.eof())
    {
        infile >> input;
        totalval += input;
        totalinput++;
        
        if(totalinput == size)
        {
            int *arrtemp = new int[size*2];
            for (int i = 0; i < size; i++)
	            arrtemp[i] = arr[i];
            delete[] arr;
            arr = arrtemp;
            size = size * 2;
            cout << "Array size is now " << size << endl;
            cerr << "Array size is now " << size << endl;
        }
    
        arr[totalinput] = input;
    }
    
    average = totalval / totalinput;
    
    for(int i = 0; i < size; i++)
    {
        if(arr[i] < average)
        {
            lvalues++;
        }
    }
    cout << "Total Value: " << totalval << endl;
    cout << "Total Inputs: " << totalinput << endl;
    cout << "Average: " << average << endl;
    cout << "Number of Values less than the average: " << lvalues << endl;
    
   	infile.close();
    
    return(0);
}
