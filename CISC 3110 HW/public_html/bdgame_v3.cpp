//This is a program to run a text only board game called "3X".
//This is the third version of the program, using classes and arrays of objects to run the game

#include<iostream>
#include<stdlib.h>
using namespace std;

class gameboard
{
  public:
    int action;
    string color;
};

class player
{
  public:
    string name;
    int spaces;
    int pass;
    int skip;
    int order;
};

void display_rules();
int spindie(int, int &);
int play(gameboard [], player [], int &, int, int &);
void switchplaces(gameboard [], player [], int, int);
void showstate(gameboard [], player [], int);
void maxnum(int, int [], player [], int);
const int goagain = 1, loseturn = 2, swaploc = 3, forfour = 4, forsix = 5, backsix = 6, backeight = 7;

//Main Function
int main()
{
  gameboard board[30];  //The array of the game board's actions and colors
  int turn = 0;
  int die, roll, pnum, action;

  action = 0, pnum = 0;
  
  board[7].action = goagain, board[10].action = goagain, board[20].action = goagain;
  board[4].action = loseturn, board[13].action = loseturn;
  board[15].action = swaploc, board[29].action = swaploc;
  board[2].action = forfour, board[22].action = forfour, board[17].action = forsix;
  board[18].action = backsix, board[24].action = backeight;
  
//Assign each space on the board a color
  for(int i = 0; i < 30; i++)
  {
    if(board[i].action == goagain)
      board[i].color = "Yellow";
    else if(board[i].action == loseturn)
      board[i].color = "Red";
    else if(board[i].action == swaploc)
      board[i].color = "Green";
    else if(board[i].action == forfour || board[i].action == forsix)
      board[i].color = "Cyan";
    else if(board[i].action == backsix || board[i].action == backeight)
      board[i].color = "Brown";
    else
      board[i].color = "blue";
  }
  
  turn = 0;

  display_rules();

//Get the number of players
  while(pnum == 0)
  {
    cout << "How many players will be playing? ";
    cin >> pnum;
    
    if(pnum > 6 || pnum < 2)
    {
      cout << "Invalid Number. Please enter a number from 2 to 6\n";
//      system("pause");
//      system("cls");
      cin.ignore();
      pnum = 0;
    }
  }
  
//Set players class to zero and get the player's names
  player players[pnum];  //Declares an array of players
  int max[pnum];

  for(int i = 0; i < pnum; i++)
  {
    cout << "What is your name player " << i+1 << "? ";
    cin >> players[i].name;
    players[i].spaces = 0;
    players[i].pass = 0;
    players[i].skip = 0;
    max[i] = 0;
  }

//  system("cls");
  
//Roll Dice to determine play order
  for(int i = 0; i < pnum; i++)
  {
    spindie(die, roll);
    players[i].order = roll;
    max[i] = roll;
  }

  maxnum(roll, max, players, pnum);
  cout << "Shuffling complete" << endl;
  cout << "The Player Order is:" << endl;
  for(int i = 0; i < pnum; i++)
  {
    cout << "Player " << i+1 << ": " << players[i].name << endl;
  }
//  system("pause");
  cin.ignore(); 
//  system("cls");
  cout << endl;
  
//Call the functions in a loop until the end of the program
  while (players[turn].pass != 3)
  {
    cout << "---It is " << players[turn].name << "'s turn---" << endl;
    if (players[turn].spaces != 0)
      cout << players[turn].name << " is currently on space " << players[turn].spaces << endl;
    else
      cout << players[turn].name << " is on the Start space" << endl;
    
    spindie(die, roll);
    play(board, players, turn, roll, pnum);

//    system("pause");
    cin.ignore(); 
//    system("cls");
    cout << endl;
  }

  if (players[turn].pass == 3)
  {
    cout << "\n\n////////////////////////////////////////\n";
    cout << "The winner is " << players[turn].name << "! Congratulations!\n";
    cout << "////////////////////////////////////////\n\n";

  }

  
  cout << endl;
//  system("pause");
  cin.ignore(); 

  return(0);
}


//Function to display the rules of the game
void display_rules()
{
  cout << "3X: This board game is a simple race between up to 6 players to see who gets \naround the board 3 times first.\n\nOf course, like any board game, there will be spaces that affect the 2 players.\n";
  cout << "The rules are simple: Roll a six sided dice and move forward that amount of \nspaces. The spaces are now color coded, with blue being the default color. \nThe four types of colored 'action spaces' you can land on include:\n\n";
  cout << "Yellow\n-Go Again: The current player rolls again. \n\nRed\n-Lose a Turn: As stated, lose a turn. \n\nGreen\n-Swap Places: Switches two player's current postions at your choice. Lap \nprogress is not affected.\n\n";
  cout << "Cyan/Brown\n-Move: Moves you forward or backward a certain number of spaces.\n\nNOTE: The order of the players will be shuffled before we start. \n\nWell, if you are ready, press any key and watch the games begin!\n";
//  system("pause");
  cin.ignore(); //Pauses Screen
//  system ("cls");
}

//Function to roll the die
int spindie(int die, int &roll)
{
  die=rand()%6+1;
  cout << "The number rolled was " << die << endl;
  roll = die;
}

//Function to move the players and perform most actions
int play(gameboard board[], player players[], int &turn, int roll, int &pnum)
{
  int swap, action;
  swap = 0, action = 0;

//Skip turn processing
      if(players[turn].skip == 1)
      {
        players[turn].skip = 0;
        cout << "Sorry, but your turn was skipped this time!" << endl;
        showstate(board, players, turn);

        //checks to see if one cycle of turns are done when turn is skipped
        if(turn < pnum-1)
          turn +=1;
        else if (turn == pnum-1)
          turn = 0;
          
        return(0);
      }
      
//Player moves forward. Also checks if a lap has completed and if the current player has won    
      players[turn].spaces += roll;
//      system("pause");
      cin.ignore();
      if (players[turn].spaces > 29)
      {
        players[turn].spaces -= 30;
        players[turn].pass++;
        cout << "-----" << players[turn].name << " has now completed " << players[turn].pass << " laps around the board!" << endl;
        if (players[turn].pass == 3)
          return(0);
      }
      action = players[turn].spaces;
      cout << "\nYou landed on a " << board[action].color << " space." << endl;
    
//Action spaces
    switch(board[action].action)
    {
      case goagain:
        showstate(board, players, turn);
        cout << "-Go again-" << endl;
        cout << "Roll again " << players[turn].name << "!" << endl;
        return(0);
        break;
      case loseturn:
        if (players[turn].skip != 1)
        {
          showstate(board, players, turn);
          cout << "-Lose a Turn-" << endl;
          cout << "You lose a turn. Wait out the next round please." << endl;
          players[turn].skip = 1;
        }
        break;  
      case swaploc:
        switchplaces(board, players, turn, pnum);
        break;
      case forfour:
        players[turn].spaces += 4;
        cout << "-Move-" << endl;
        cout << "Move ahead 4 spaces." << endl;
        break;
      case forsix:
        players[turn].spaces += 6;
        cout << "-Move-" << endl;
        cout << "Move ahead 6 spaces." << endl;
        break;
      case backsix:
        players[turn].spaces -= 6;
        cout << "-Move-" << endl;
        cout << "Sorry, go back 6 spaces." << endl;
        break;
      case backeight:
        players[turn].spaces -= 8;
        cout << "-Move-" << endl;
        cout << "Too bad! Go back 8 spaces." << endl;
        break;
    }

  showstate(board, players, turn);

//Next Player's turn
  if(turn < pnum-1)
    turn +=1;
  else if (turn == pnum-1)
    turn = 0;
}

//Function to swap the locations of any player on the board
void switchplaces(gameboard board[], player players[], int turn, int pnum)
{
  int swap = 0, x = -1;
  cout << "-Swap Places-" << endl;
  cout << "You are on space " << players[turn].spaces << endl;

  while(x == -1)
  {
    cout << "Who do you want to swap positions with? Enter 0 to cancel" << endl;
    for(int i = 0; i < pnum; i++)
    {
      cout << "Player " << i+1 << ": " << players[i].name << "\t---On space " << players[i].spaces << endl;
    }
    cin >> x;
    
    if(x > pnum || x < 0)
    {
      cout << "Invalid Input" << endl;
//      system("pause");
      cin.ignore();
//      system("cls");
      x = -1;
    }
    else if( x == 0)
      return;
    
    if(x == turn+1)
    {
      cout << "You can't swap with yourself!" << endl;
//      system("pause");
      cin.ignore();
//      system("cls");
      x = -1;
    } 
  }
      
  cout << players[turn].name << " was on space " << players[turn].spaces << endl;
  cout << players[x-1].name << " was on space " << players[x-1].spaces << endl;
                 
  swap = players[turn].spaces;
  players[turn].spaces = players[x-1].spaces;
  players[x-1].spaces = swap;
  cout << "Both players have now swapped positions on the board!" << endl;
}

//Function to print out the current location of either P1 or P2
void showstate(gameboard board[], player players[], int turn)
{
    if (players[turn].spaces != 0)
      cout << players[turn].name << " is now on space " << players[turn].spaces << " on lap " << players[turn].pass+1 << endl << endl;
    else
      cout << players[turn].name << " is on the Start space on lap " << players[turn].pass+1 << endl << endl;
}

//Function to determine max number by bubblesort
void maxnum(int roll, int max[], player players[], int pnum)
{
  int swap = 0, swapped = 1;
  string swapname; 
  
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
      
        swapname = players[i].name;
        players[i] = players[i+1];
        players[i+1].name = swapname;
        
        swapped = 1;
      }
    }
  }
  cout << endl;
//  system("cls");
}
