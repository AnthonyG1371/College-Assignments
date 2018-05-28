//This is a program to run a simple text only, no input board game called "3X".

#include<iostream>
#include<stdlib.h>
using namespace std;

void display_rules();
int spindie(int, int &);
int play(int [], int &, int &, int &, int, int &, int &);
void switchplaces(int [], int &, int &);
void showstate(int [], int, int, int, int, int);
const int goagain = 1, loseturn = 2, swaploc = 3, forfour = 4, forsix = 5, backsix = 6, backeight = 7;

//Main Function
int main()
{
  int board[30] = {0};
  int die, roll, p1, p2, turn, action, pass1, pass2;

  p1 = 0, p2 = 0, pass1 = 0, pass2 = 0, action = 0;
  board[7] = goagain, board[10] = goagain, board[20] = goagain, board[4] = loseturn, board[13] = loseturn;
  board[15] = swaploc, board[29] = swaploc, board[2] = forfour;
  board[22] = forfour, board[17] = forsix, board[18] = backsix, board[24] = backeight;
  turn = 0;

  display_rules();

  while (pass1 != 3 && pass2 != 3)
  {
    if (turn == 0 || turn == 2)
      cout << "---It is Player 1's turn---" << endl;
    else if (turn == 1 || turn == 3)
      cout << "---It is Player 2's turn---" << endl;
      
    
    spindie(die, roll);
    play(board, p1, p2, turn, roll, pass1, pass2);
    //system("pause");
    cin.ignore(); 
    //system("cls");
    cout << endl;
  }

  if (pass1 == 3)
  {
    cout << "\n\n////////////////////////////////////////\n";
    cout << "The winner is player 1! Congratulations!\n";
    cout << "////////////////////////////////////////\n\n";
  }
  else if (pass2 == 3)
  {
    cout << "\n\n////////////////////////////////////////\n";
    cout << "The winner is player 2! Congratulations!\n";
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
  cout << "3X: This board game (which is completley automated by the way, so you can't \nreally do anything) is a simple race between two players to see who gets \naround the board 3 times first.\n\nOf course, like any board game, there will be spaces that affect the 2 players.\n";
  cout << "The rules are simple: Roll a six sided dice and move forward that amount of \nspaces. \nThe four types of 'action spaces' you can land on include:\n";
  cout << "-Go Again: The current player rolls again. \n-Lose a Turn: As stated, lose a turn. \n-Swap Places: Switches both player's current postions. Lap progress is not \naffected.\n";
  cout << "-Move: Moves you forward or backward a certain number of spaces.\n\nWell, if you are ready, press any key and watch the games begin!\n";
  //system("pause");
  cin.ignore(); //Pauses Screen
  //system ("cls");
}

//Function to roll the die
int spindie(int die, int &roll)
{
  die=rand()%6+1;
  cout << "The number rolled was " << die << endl;
  roll = die;
}

//Function to move the players and perform most actions
int play(int board[], int &p1, int &p2, int &turn, int roll, int &pass1, int &pass2)
{
  int swap, action;
  swap = 0, action = 0;

  if (turn == 0 || turn == 2)
  {
    p1 += roll;
      if (p1 > 29)
      {
        p1 -= 30;
        pass1++;
        cout << "-----Player 1 has now completed " << pass1 << " laps around the board!" << endl;
        if (pass1 == 3)
          return(0);
      }
    action = board[p1];
  }
  else if (turn == 1 || turn == 3)
  {
    p2 += roll;
      if (p2 > 29)
      {
        p2 -= 30;
        pass2++;
        cout << "-----Player 2 has now completed " << pass2 << " laps around the board!" << endl;
        if (pass2 == 3)
          return(0);
      }
    action = board[p2];
  }

  if (turn == 0 || turn == 2)
  {
    switch(action)
    {
      case goagain:
        turn = 0;
        showstate(board, p1, p2, pass1, pass2, turn);
        cout << "-Go again-" << endl;
        cout << "Roll again Player 1!" << endl;
        return(0);
        break;
      case loseturn:
        if (turn != 3)
        {
          showstate(board, p1, p2, pass1, pass2, turn);
          cout << "-Lose a Turn-" << endl;
          cout << "You lose a turn. P2 will now move twice." << endl;
          turn = 3;
          return(0);
        }
        else
          turn = 1;
        break;  
      case swaploc:
        switchplaces(board, p1, p2);
        break;
      case forfour:
        p1 += 4;
        cout << "-Move-" << endl;
        cout << "Move ahead 4 spaces." << endl;
        break;
      case forsix:
        p1 += 6;
        cout << "-Move-" << endl;
        cout << "Move ahead 6 spaces." << endl;
        break;
      case backsix:
        p1 -= 6;
        cout << "-Move-" << endl;
        cout << "Sorry, go back 6 spaces." << endl;
        break;
      case backeight:
        p1 -= 8;
        cout << "-Move-" << endl;
        cout << "Too bad! Go back 8 spaces." << endl;
        break;
    }
  }
  else if (turn == 1 || turn == 3)
  {
  
    switch(action)
    {
      case goagain:
        turn == 1;
        showstate(board, p1, p2, pass1, pass2, turn);
        cout << "-Go again-" << endl;
        cout << "Roll again Player 2!" << endl;
        return(0);
        break; 
      case loseturn:
        if (turn != 2)
        {
          showstate(board, p1, p2, pass1, pass2, turn);
          cout << "-Lose a Turn-" << endl;
          cout << "You lose a turn. P1 will now move twice." << endl;
          turn = 2;
          return(0);
        }
        else
          turn = 0;
        break;
      case swaploc:
        switchplaces(board, p1, p2);
        break;
      case forfour:
        p2 += 4;
        cout << "-Move-" << endl;
        cout << "Move ahead 4 spaces." << endl;
        break;
      case forsix:
        p2 += 6;
        cout << "-Move-" << endl;
        cout << "Move ahead 6 spaces." << endl;
        break;
      case backsix:
        p2 -= 6;
        cout << "-Move-" << endl;
        cout << "Sorry, go back 6 spaces." << endl;
        break;
      case backeight:
        p2 -= 8;
        cout << "-Move-" << endl;
        cout << "Too bad! Go back 8 spaces." << endl;
        break;
    }
  }

  showstate(board, p1, p2, pass1, pass2, turn);

  if (turn == 0)
    turn = 1;
  else if (turn == 1)
    turn = 0;
  else if (turn == 2)
    turn = 0;
  else if (turn == 3)
    turn = 1;
}

//Function to swap the locations of player 1 and player 2 on the board
void switchplaces(int board[], int &p1, int &p2)
{
  int swap = 0;          
  cout << "-Swap Places-" << endl;
  cout << "Player 1 was on space " << p1 << endl;
  cout << "Player 2 was on space " << p1 << endl;
                 
  swap = p1;
  p1 = p2;
  p2 = swap;
  cout << "Both players have now swapped positions on the board!" << endl;
}

//Function to print out the current location of either P1 or P2
void showstate(int board[], int p1, int p2, int pass1, int pass2, int turn)
{
  if (turn == 0 || turn == 2)
  {
    if (p1 != 0)
      cout << "Player 1 is currently on space " << p1 << " on lap " << pass1+1 << endl;
    else
      cout << "Player 1 is on the Start space on lap " << pass1+1 << endl;
  }
  else if (turn == 1 || turn == 3)
  {
    if (p1 != 0)   
      cout << "Player 2 is currently on space " << p2 << " on lap " << pass2+1 << endl;
    else
      cout << "Player 2 is on the Start space on lap " << pass2+1 << endl;
  }
}
