//This is a program to run a text only board game called "3X".
//This is the fourth version of the program, using classes with private members
//This version of the program is broken up into multiple pieces according to the
//classes, functions, and main

#include<iostream>
#include<stdlib.h>
using namespace std;

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

const int goagain = 1, loseturn = 2, swaploc = 3, forfour = 4, forsix = 5, backsix = 6, backeight = 7;

//Main Function: Now so short, its six lines total
int main()
{
  Game playgame;
  playgame.play();
  return(0);
}

//Function to initiate and run the game. This was originally MAIN
void Game::play()
{
  int turn = 0;
  int die, roll, action;
  string tempname;

  action = 0;
  
  for(int i = 0; i < 30; i++)
  {
    board[i].setaction(i);
  }
  
//Assign each space on the board a color
  for(int i = 0; i < 30; i++)
  {
    if(board[i].getaction() == goagain)
      board[i].setcolor("Yellow");
    else if(board[i].getaction() == loseturn)
      board[i].setcolor("Red");
    else if(board[i].getaction() == swaploc)
      board[i].setcolor("Green");
    else if(board[i].getaction() == forfour || board[i].getaction() == forsix)
      board[i].setcolor("Cyan");
    else if(board[i].getaction() == backsix || board[i].getaction() == backeight)
      board[i].setcolor("Brown");
    else
      board[i].setcolor("Blue");
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
  player players[pnum];  //Redeclares an object array of players. All parameters are set to default
  int max[pnum];

  for(int i = 0; i < pnum; i++)
  {
    cout << "What is your name player " << i+1 << "? ";
	cin >> tempname;
	players[i].setname(tempname);
//    The following three lines would be useful if there wasn't a default
//    players[i].setspaces(0);
//    players[i].setpass(0);
//    players[i].setskip(0);
    max[i] = 0;
  }

//  system("cls");
  
//Roll Dice to determine play order
  for(int i = 0; i < pnum; i++)
  {
    spindie(die, roll);
    max[i] = roll;
  }

  maxnum(roll, max, players, pnum);
  cout << "Shuffling complete" << endl;
  cout << "The Player Order is:" << endl;
  for(int i = 0; i < pnum; i++)
  {
    cout << "Player " << i+1 << ": " << players[i].getname() << endl;
  }
//  system("pause");
  cin.ignore(); 
//  system("cls");
  cout << endl;
  
//Call the functions in a loop until the end of the program
  while (players[turn].getpass() != 3)
  {
    cout << "---It is " << players[turn].getname() << "'s turn---" << endl;
    if (players[turn].getspaces() != 0)
      cout << players[turn].getname() << " is currently on space " << players[turn].getspaces() << endl;
    else
      cout << players[turn].getname() << " is on the Start space" << endl;
    
    spindie(die, roll);
    play2(board, players, turn, roll, pnum);

//    system("pause");
    cin.ignore(); 
//    system("cls");
    cout << endl;
  }

  if (players[turn].getpass() == 3)
  {
    cout << "\n\n////////////////////////////////////////\n";
    cout << "The winner is " << players[turn].getname() << "! Congratulations!\n";
    cout << "////////////////////////////////////////\n\n";

  }

  
  cout << endl;
//  system("pause");
  cin.ignore(); 
}


//Function to display the rules of the game
void Game::display_rules()
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
int Game::spindie(int die, int &roll)
{
  die=rand()%6+1;
  cout << "The number rolled was " << die << endl;
  roll = die;
}

//Function to move the players and perform most actions
int Game::play2(gameboard board[], player players[], int &turn, int roll, int &pnum)
{
  int swap, action;
  swap = 0, action = 0;

//Skip turn processing
      if(players[turn].getskip() == 1)
      {
        players[turn].setskip(0);
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
      players[turn].addspaces(roll);
//      system("pause");
      cin.ignore();
      if (players[turn].getspaces() > 29)
      {
        players[turn].addspaces(-30);
        players[turn].setpass(1);
        cout << "-----" << players[turn].getname() << " has now completed " << players[turn].getpass() << " laps around the board!" << endl;
        if (players[turn].getpass() == 3)
          return(0);
      }
      action = players[turn].getspaces();
      cout << "\nYou landed on a " << board[action].getcolor() << " space." << endl;
    
//Action spaces
    switch(board[action].getaction())
    {
      case goagain:
        showstate(board, players, turn);
        cout << "-Go again-" << endl;
        cout << "Roll again " << players[turn].getname() << "!" << endl;
        return(0);
        break;
      case loseturn:
        if (players[turn].getskip() != 1)
        {
          showstate(board, players, turn);
          cout << "-Lose a Turn-" << endl;
          cout << "You lose a turn. Wait out the next round please." << endl;
          players[turn].setskip(1);
        }
        break;  
      case swaploc:
        switchplaces(board, players, turn, pnum);
        break;
      case forfour:
        players[turn].addspaces(4);
        cout << "-Move-" << endl;
        cout << "Move ahead 4 spaces." << endl;
        break;
      case forsix:
        players[turn].addspaces(6);
        cout << "-Move-" << endl;
        cout << "Move ahead 6 spaces." << endl;
        break;
      case backsix:
        players[turn].addspaces(-6);
        cout << "-Move-" << endl;
        cout << "Sorry, go back 6 spaces." << endl;
        break;
      case backeight:
        players[turn].addspaces(-8);
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
void Game::switchplaces(gameboard board[], player players[], int turn, int pnum)
{
  int swap = 0, x = -1;
  cout << "-Swap Places-" << endl;
  cout << "You are on space " << players[turn].getspaces() << endl;

  while(x == -1)
  {
    cout << "Who do you want to swap positions with? Enter 0 to cancel" << endl;
    for(int i = 0; i < pnum; i++)
    {
      cout << "Player " << i+1 << ": " << players[i].getname() << "\t---On space " << players[i].getspaces() << endl;
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
      
  cout << players[turn].getname() << " was on space " << players[turn].getspaces() << endl;
  cout << players[x-1].getname() << " was on space " << players[x-1].getspaces() << endl;
                 
  swap = players[turn].getspaces();
//  players[turn].spaces = players[x-1].spaces;
  players[turn].setspaces(players[x-1].getspaces());
  players[x-1].setspaces(swap);
  cout << "Both players have now swapped positions on the board!" << endl;
}

//Function to print out the current location of either P1 or P2
void Game::showstate(gameboard board[], player players[], int turn)
{
    if (players[turn].getspaces() != 0)
      cout << players[turn].getname() << " is now on space " << players[turn].getspaces() << " on lap " << players[turn].getpass()+1 << endl << endl;
    else
      cout << players[turn].getname() << " is on the Start space on lap " << players[turn].getpass()+1 << endl << endl;
}

//Function to determine max number by bubblesort
void Game::maxnum(int roll, int max[], player players[], int pnum)
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
      
        swapname = players[i].getname();
        players[i] = players[i+1];
        players[i+1].setname(swapname);
        
        swapped = 1;
      }
    }
  }
  cout << endl;
//  system("cls");
}

//New Class Functions
int Game::getpnum()
{
  return(pnum);
}

void gameboard::setaction(int actnum)
{
  switch (actnum)
  {
    case 7: case 10: case 20:
      action = goagain;
      break;
    case 4: case 13:
      action = loseturn;
      break;
    case 15: case 29:
      action = swaploc;
      break;
    case 2: case 22:
      action = forfour;
      break;
    case 17:
      action = forsix;
      break;
    case 18:
      action = backsix;
      break;
    case 24:
      action = backeight;
      break;
    default:
      action = 0;
  }
}

int gameboard::getaction()
{
  return(action);
}

void gameboard::setcolor(string tempcolor)
{
  color = tempcolor;
}

string gameboard::getcolor()
{
  return(color);
}

player::player()
{
  name = "";
  spaces = 0;
  pass = 0;
  skip = 0;
  order = 0;
}
