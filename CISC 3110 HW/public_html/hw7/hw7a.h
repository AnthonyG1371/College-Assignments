#ifndef HW7A_H
#define HW7A_H
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

#endif
