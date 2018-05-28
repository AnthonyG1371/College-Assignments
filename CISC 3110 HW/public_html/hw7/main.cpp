#include<iostream>
#include"hw7a.h"
using namespace std;

int main()
{
  int numscores = 0;
  double score;
  cout << "How many test scores are there? ";
  cin >> numscores;
  
  if(numscores < 1)
  {
    cout << "Then there are no test scores. Ending Program" << endl;
    return(0);
  }
  
  TestScores grades(numscores);
  grades.changenumscores(numscores);
  
  cout << "Please enter grades for each test score" << endl;
  for(int i = 0; i < numscores; i++)
  {
    cout << "Test " << i+1 << ": ";
    cin >> score;
    grades.changegrade(i, score);
  }
 
  grades.dispgrade(numscores);
  
  cout << "The average is " << grades.average(numscores) << endl << endl;
  
  //Object Overload/Copy section
  TestScores grades2(numscores);
  grades2 = grades;

  cout << "Displaying a copy of the test scores" << endl;
  grades2.dispgrade(numscores);
  cout << "The average is " << grades2.average(numscores) << endl << endl;
  
  return(0);
}
