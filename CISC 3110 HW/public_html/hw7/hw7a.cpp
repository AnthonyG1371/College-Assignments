#include<iostream>
#include"hw7a.h"
using namespace std;

TestScores::TestScores(int numscores)
{
  gradeptr = new double[numscores];
  
  for(int i = 0; i < numscores; i++)
  {
    gradeptr[i] = 0;
  }
}

void TestScores::operator=(const TestScores &rightside)
{
  numscores = rightside.numscores;
  for(int i = 0; i < numscores; i++)
    gradeptr[i] = rightside.gradeptr[i];
}

void TestScores::changenumscores(int num)
{
  numscores = num;
}

double TestScores::accessgrade(int selected)
{
  return(gradeptr[selected]);
}

void TestScores::changegrade(int selected, double newgrade)
{
  gradeptr[selected] = newgrade;
}

void TestScores::dispgrade(int numscores)
{
  for(int i = 0; i < numscores; i++)
  {
    cout << "Grade for test " << i+1 << ": " << accessgrade(i) << endl;
  }
}

double TestScores::average(int numscores)
{
  double total = 0, avg;
  
  for(int i = 0; i < numscores; i++)
  {
    total += gradeptr[i];
  }
  
  avg = total / numscores;
  
  return(avg);
}

TestScores::~TestScores()
{
  delete[] gradeptr;
}
