#include <iostream>
#include <ctime>
#include "bubble_sort.h"

using namespace std;

void swap(int &a, int &b);
void sort(int [], int);
void sort(double [], int);
void sort(string [], int);
void sort(char *, int);

int main() 
{
	int n;
	
//int
	cout << "Enter the number of elements in the array: " ;
	cin >> n;

	int *a = new int[n];

    cout << "Enter in the elements, all integers please." << endl;
	for (int i = 0; i < n; i++)
		cin >> a[i];
    
	sort(a, n);
	
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	
	cout << endl;

//double
	cout << "Enter the number of elements in the double array: " ;
	cin >> n;

	double *d = new double[n];

    cout << "Enter in the elements, all doubles please." << endl;
	for (int i = 0; i < n; i++)
		cin >> d[i];
		
	sort(d, n);
	
	for (int i = 0; i < n; i++)
		cout << d[i] << " ";
	
	cout << endl;
	
//string
	cout << "Enter the number of elements in the string array: " ;
	cin >> n;

	string *s = new string[n];

    cout << "Enter in the elements, all strings please." << endl;
	for (int i = 0; i < n; i++)
		cin >> s[i];
		
	sort(s, n);
	
	for (int i = 0; i < n; i++)
		cout << s[i] << " ";

    cout << endl;
	
//char
	cout << "Enter the number of elements in the char array: " ;
	cin >> n;

	char *c = new char[n];

    cout << "Enter in the elements, all char please." << endl;
	for (int i = 0; i < n; i++)
		cin >> c[i];
		
	sort(c, n);
	
	for (int i = 0; i < n; i++)
		cout << c[i] << " ";
	
	cout << endl;
		
    system("pause");
	return 0;
}

//Functions
//Swap
void swap(int &a, int &b) 
{
	int t = a;
	a = b;
	b = t;
}

//Sorts
void sort(int arr[], int n)
{
	for (int last = n-1; last > 0; last--)
    {
		for (int i = 0; i < last; i++)
			if (arr[i] > arr[i+1])
				swap(arr[i], arr[i+1]);
	}
}

void sort(double darr[], int n)
{
	for(int last = n-1; last > 0; last--)
    {
		for(int i = 0; i < last; i++)
			if (darr[i] > darr[i+1])
				swap(darr[i], darr[i+1]);
	}
}

void sort(string sarr[], int n)
{
	for(int last = n-1; last > 0; last--)
    {
		for(int i = 0; i < last; i++)
			if (sarr[i] > sarr[i+1])
				swap(sarr[i], sarr[i+1]);
	}
}

void sort (char *carr, int n)
{
    for(int last = n-1; last > 0; last--)
    {
		for(int i = 0; i < last; i++)
			if (carr[i] > carr[i+1])
				swap(carr[i], carr[i+1]);
	}
}
