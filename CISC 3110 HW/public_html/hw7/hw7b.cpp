#include<iostream>
using namespace std;

int recdivide(int, int, int);

int main()
{
  int num, denom = 0, i;  

  cout << "Enter a numerator: ";
  cin >> num;
  while (denom == 0)
  {
    cout << "Enter a denominator. DONT PUT ZERO!: ";
    cin >> denom;
	
	if(denom == 0)
	{
	  cout << "Invalid Input\n";
	}
  }
  
  cout << "Enter the number of times you want to divide: ";
  cin >> i;
  
  recdivide(num, denom, i);
  cout << "The original numerator was: " << num << endl;
  
  return(0);
}

int recdivide(int num, int denom, int i)
{
  int quotient = 0;
  
  if(i == 0 || num == 0)
    return(0);
    
  quotient = num / denom;
  recdivide(quotient, denom, i - 1);
    
  cout << "The current quotient is " << quotient << endl;
  return(quotient);
}
