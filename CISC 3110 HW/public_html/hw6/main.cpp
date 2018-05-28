//This is a program to run a text only board game called "3X".
//This is the fourth version of the program, using classes with private members
//This version of the program is broken up into multiple pieces according to the
//classes, functions, and main

#include"gameboard.h"
#include"player.h"
#include"game.h"

#include<iostream>
#include<stdlib.h>
using namespace std;

//Main Function: Now so short, its six lines total
int main()
{
  Game playgame;
  playgame.play();
  return(0);
}
