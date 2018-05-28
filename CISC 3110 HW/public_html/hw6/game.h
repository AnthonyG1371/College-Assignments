#include<iostream>
#include<stdlib.h>
using namespace std;

#ifndef GAME_H
#define GAME_H
#include"gameboard.h"
#include"player.h"

class Game
{
  private:
    static const int BNUM = 30;
    gameboard board[BNUM];
	int pnum;
	player players[6];
  public:
    Game(){pnum = 0;};
    void play();
	int getpnum();
	//Old Functions
	void display_rules();
    int spindie(int, int &);
    void showstate(gameboard [], player [], int);
    void switchplaces(gameboard [], player [], int, int);
    int play2(gameboard [], player [], int &, int, int &);
	//This is the "sort players" function from before
    void maxnum(int, int [], player [], int);
};

#endif
