#include<iostream>
#include<stdlib.h>
using namespace std;

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

const int goagain = 1, loseturn = 2, swaploc = 3, forfour = 4, forsix = 5, backsix = 6, backeight = 7;

class gameboard
{
  private:
    int action;
    string color;
  public:
    void setaction(int);
    int getaction();
    void setcolor(string);
    string getcolor();
};

#endif
