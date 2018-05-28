#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "maze.h"
using namespace std;

//Main simply calls functions
int main()
{
    cout << "Starting Maze Program" << endl;
    cout << "S is Start, F is Finish, and P is Player Location" << endl;
    getrows();
    getcols();
    Maze mazegame = load("maze.txt");
    mazegame.print(mazegame);
    mazegame.solve();
    
    return(0);
}
