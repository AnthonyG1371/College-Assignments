//There is only one function in the .cpp for this class.
//The rest of its functions are in the class itself

#include<iostream>
#include<stdlib.h>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class player
{
  private:
    string name;
    int spaces;
    int pass;
    int skip;
    int order;
  public:
    player();
    void setname(string tempname){name = tempname;}
    void setspaces(int move){spaces = move;}
    void addspaces(int move){spaces += move;}
    void setpass(int plus){pass += plus;}
    void setskip(int set){skip = set;}
    string getname(){return(name);}
	int getspaces(){return(spaces);}
	int getpass(){return(pass);}
	int getskip(){return(skip);}
};

#endif
