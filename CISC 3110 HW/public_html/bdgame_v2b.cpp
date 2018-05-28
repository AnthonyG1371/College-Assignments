//This is a program to run a text only board game called "3X".
//This is the second version B of the program, using vectors to allocate players

#include<iostream>
#include<stdlib.h>
#include<vector>
using namespace std;

void display_rules();
int spindie(int, int &);
int play(int [], int[][2], int &, int, vector<int> &, int &, vector<int> &, int []);
void switchplaces(int [], int[][2], int, int, vector<int> &);
void showstate(int [], int[][2], vector<int> &, int, vector<int> &);
void maxnum(int, int [], int[][2], int);
const int goagain = 1, loseturn = 2, swaploc = 3, forfour = 4, forsix = 5, backsix = 6, backeight = 7;

//Main Function
int main()
{
  int board[30] = {0};
  int die, roll, pnum, turn, action;

  action = 0, pnum = 0;
  board[7] = goagain, board[10] = goagain, board[20] = goagain, board[4] = loseturn, board[13] = loseturn;
  board[15] = swaploc, board[29] = swaploc, board[2] = forfour;
  board[22] = forfour, board[17] = forsix, board[18] = backsix, board[24] = backeight;

  turn = 0;

  while(pnum == 0)
  {
    cout << "How many players will be playing? ";
    cin >> pnum;
    
    if(pnum > 6 || pnum < 2)
    {
      cout << "Invalid Number. Please enter a number from 2 to 6\n";
      system("pause");
      //cin.ignore(); 
      system("cls");
      pnum = 0;
    }
  }
  
//Declare and default to zero the dynamic arrays
  vector<int> pass(pnum);
  vector<int> spaces(pnum);
  int players[pnum][2];
  int max[pnum];
  for(int i = 0; i < pnum; i++)
  {
    players[i][0] = i+1;
    spaces[i] = 0;
    pass[i] = 0;
    max[i] = 0;
  }
  system("cls");

  display_rules();
  int skip[pnum];
  
//Roll Dice to determine play order
  for(int i = 0; i < pnum; i++)
  {
    spindie(die, roll);
    players[i][1] = roll;
    max[i] = roll;
  }

  maxnum(roll, max, players, pnum);
  cout << "The Player Order is:" << endl;
  for(int i = 0; i < pnum; i++)
  {
//          cout << "Max[i] " << max[i] << endl;
    cout << "Player " << players[i][0] << endl;
  }
  system("pause");
  //cin.ignore(); 
  system("cls");
  
//Call the functions in a loop until the end of the program
  while (pass[turn] != 3)
  {
    cout << "---It is Player " << players[turn][0] << "'s turn---" << endl;
    cout << "Player " << turn+1 << " is currently on space " << spaces[turn] << endl;
    
    spindie(die, roll);
    play(board, players, turn, roll, pass, pnum, spaces, skip);

    system("pause");
    //cin.ignore(); 
    system("cls");
    cout << endl;
  }

  if (pass[turn] == 3)
  {
    cout << "\n\n////////////////////////////////////////\n";
    cout << "The winner is player " << players[turn][0] << "! Congratulations!\n";
    cout << "////////////////////////////////////////\n\n";
  }

  
  cout << endl;
  //system("pause");
  cin.ignore(); 

  return(0);
}


//Function to display the rules of the game
void display_rules()
{
  cout << "3X: This board game (which is completley automated by the way, so you can't \nreally do anything) is a simple race between up to 6 players to see who gets \naround the board 3 times first.\n\nOf course, like any board game, there will be spaces that affect the 2 players.\n";
  cout << "The rules are simple: Roll a six sided dice and move forward that amount of \nspaces. \nThe four types of 'action spaces' you can land on include:\n";
  cout << "-Go Again: The current player rolls again. \n-Lose a Turn: As stated, lose a turn. \n-Swap Places: Switches two player's current postions at your choice. Lap progress is not \naffected.\n";
  cout << "-Move: Moves you forward or backward a certain number of spaces.\n\nWell, if you are ready, press any key and watch the games begin!\n";
  system("pause");
  cin.ignore(); //Pauses Screen
  system ("cls");
}

//Function to roll the die
int spindie(int die, int &roll)
{
  die=rand()%6+1;
  cout << "The number rolled was " << die << endl;
  roll = die;
}

//Function to move the players and perform most actions
int play(int board[], int players[][2], int &turn, int roll, vector<int> &pass, int &pnum, vector<int> &spaces, int skip[])
{
  int swap, action;
  swap = 0, action = 0;

//Skip turn process
      if(skip[turn] == 1)
      {
        skip[turn] = 0;
        cout << "Sorry, but your turn was skipped this time!" << endl;
        
        if(turn < pnum-1)
          turn +=1;
        else if (turn == pnum-1)
          turn = 0;
          
        return(0);
      }
      
//Player moves forward      
      spaces[turn] += roll;
      system("pause");
      if (spaces[turn] > 29)
      {
        spaces[turn] -= 30;
        pass[turn]++;
        cout << "-----Player " << players[turn][0] << " has now completed " << pass[turn] << " laps around the board!" << endl;
        if (pass[turn] == 3)
          return(0);
      }
      action = board[spaces[turn]];
    
//Action spaces
    switch(action)
    {
      case goagain:
        //turn = 0;
        showstate(board, players, pass, turn, spaces);
        cout << "-Go again-" << endl;
        cout << "Roll again Player " << players[turn][0] << "!" << endl;
        return(0);
        break;
      case loseturn:
        if (skip[turn] != 1)
        {
          showstate(board, players, pass, turn, spaces);
          cout << "-Lose a Turn-" << endl;
          cout << "You lose a turn. Wait out the next round please." << endl;
          skip[turn] = 1;
        }
        break;  
      case swaploc:
        switchplaces(board, players, turn, pnum, spaces);
        break;
      case forfour:
        spaces[turn] += 4;
        cout << "-Move-" << endl;
        cout << "Move ahead 4 spaces." << endl;
        break;
      case forsix:
        spaces[turn] += 6;
        cout << "-Move-" << endl;
        cout << "Move ahead 6 spaces." << endl;
        break;
      case backsix:
        spaces[turn] -= 6;
        cout << "-Move-" << endl;
        cout << "Sorry, go back 6 spaces." << endl;
        break;
      case backeight:
        spaces[turn] -= 8;
        cout << "-Move-" << endl;
        cout << "Too bad! Go back 8 spaces." << endl;
        break;
    }

  showstate(board, players, pass, turn, spaces);

//Next Player's turn
  if(turn < pnum-1)
    turn +=1;
  else if (turn == pnum-1)
    turn = 0;
}

//Function to swap the locations of any player on the board
void switchplaces(int board[], int players[][2], int turn, int pnum, vector<int> &spaces)
{
  int swap = 0, x = -1;
  cout << "-Swap Places-" << endl;

  while(x == -1)
  {
    cout << "Who do you want to swap positions with? Enter 0 to cancel: ";
       cin >> x;
    if(x > pnum || x < 0)
    {
      cout << "Invalid Input" << endl;
      x = -1;
    }
    else if( x == 0)
      return;
    
    if(x == turn+1)
    {
      cout << "You can't swap with yourself!" << endl;
      x = -1;
    } 
  }
      
  cout << "Player " << players[turn][0] << " was on space " << spaces[turn] << endl;
  cout << "Player " << players[x-1][0] << " was on space " << spaces[x-1] << endl;
                 
  swap = spaces[turn];
  spaces[turn] = spaces[x-1];
  spaces[x-1] = swap;
  cout << "Both players have now swapped positions on the board!" << endl;
}

//Function to print out the current location of either P1 or P2
void showstate(int board[], int players[][2], vector<int> &pass, int turn, vector<int> &spaces)
{
    if (spaces[turn] != 0)
      cout << "--Player " << players[turn][0] << " is now on space " << spaces[turn] << " on lap " << pass[turn]+1 << endl;
    else
      cout << "--Player " << players[turn][0] << " is on the Start space on lap " << pass[turn]+1 << endl;
}

//Function to determine max number by bubblesort and 2d array
void maxnum(int roll, int max[], int players[][2], int pnum)
{
  int swap = 0, swapped = 1;   
  
  while(swapped == 1)   
  {    
    swapped = 0;
    for(int i = 0; i < pnum-1; i++)
    {
      if(max[i] < max[i+1])
      {
        swap = max[i];
        max[i] = max[i+1];
        max[i+1] = swap;
      
        swap = players[i][0];
        players[i][0] = players[i+1][0];
        players[i+1][0] = swap;
        
        swapped = 1;
      }
    }
  }
  cout << endl;
  system("pause");
}
