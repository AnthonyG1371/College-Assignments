#include<iostream>
using namespace std;

class TestScores
{
  private:
    double* gradeptr;
    int numscores;
  public:
    TestScores(int);
	void operator=(const TestScores &);
	void changenumscores(int);
	double accessgrade(int);
	void changegrade(int, double);
	void dispgrade(int);
	double average(int);
	~TestScores();
};

int main()
{
  int numscores = 0;
  double score;
  cout << "How many test scores are there? ";
  cin >> numscores;
  
  if(numscores < 1)
  {
    cout << "Then there are no test scores. Ending Program" << endl;
    system("pause");
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
  
  system("pause");
  return(0);
}

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
