#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include "maze.h"
using namespace std;
ifstream rowfile, colfile;
int rowtotal, coltotal;
stack<Location> locstack;
stack<Location> junction;
stack<int> junctpathcount;

//Reads in the file one character at a time and converts them to integers
//as ID for the various data in the maze. See print() for more details.
Maze load(string filename)
{
    int line, rownum = 0, colnum = 0, locid;
    char locchar;
    Location *start = new Location(0,0);
    Location *finish = new Location(0,0);
    
    fstream infile("maze.txt", fstream::in);
    if(infile.fail())
    {
        cout << "Error: File not found." << endl;
    }
    vector<vector<int> > mazearr(rowtotal, vector<int>(coltotal));

    while (infile >> noskipws >> locchar) 
    {
        if(!isspace(locchar))
        {
            locid = locchar - '0';
            mazearr.at(rownum).at(colnum) = locid;
            if(locid == 2){start = new Location(rownum, colnum);}
            if(locid == 3){finish = new Location(rownum, colnum);}
            colnum++;
        }
        else
        {
            rownum++;
            colnum = 0;
        }
    }
 
    infile.close();
    
    //Declares a maze class to be used
    Maze maze(mazearr, *start, *finish);    
    return maze;
}


//Probably a better way to implement...
//Reads the file once and checks for the amount of "whitespace" it has,
//which should be the line breaks in our maze document.
int getrows()
{
    int line = 0;
    char ch; int a;
    rowtotal++;
    fstream infile("maze.txt", fstream::in);
    while(infile >> noskipws >> ch) 
    {
        if(isspace(ch))
            rowtotal++;
    }
    return rowtotal;
}

//Reads in the file until the first "whitespace" linebreak to detrmine
//the number of columns it has.
int getcols()
{
    int line = 0;
    char ch; int a;
    fstream infile("maze.txt", fstream::in);
    while(infile >> noskipws >> ch) 
    {
        if(!isspace(ch))
            coltotal++;
        else
            return coltotal;
    }
}

//Constructor. Mainly declares variables.
Maze::Maze(vector<vector<int> > inputarr, const Location &startpos, const Location &endpos)
{
    vector<vector<bool> > temp(rowtotal, vector<bool>(coltotal));
                          
    //Initalizes the maze array and the traversed boolean array    
    mazearr = inputarr;
    traversed = temp;
    for(int i = 0; i < rowtotal; i++)
    {
       for(int j = 0; j < coltotal; j++)
       {
         traversed[i][j] = false;
       }
       cout << endl;
    }
    
    //Inititalizes strart, finish, and current locations
    //Also initalizes a junction stack
    start = startpos;
    finish = endpos;
    currentloc = startpos;
    junction.push(startpos);
    traversed.at(start.x).at(start.y) = true;
}

//Main function of the program.
//It calls isPath and then move or backtrack until the maze is complete
//or it is incomplete.
bool Maze::solve()
{
    locstack.push(NULL);
    prevloc = currentloc;
    
    while(currentloc != finish)
    {
        if(!isPath(currentloc))
        {
            backtrack(currentloc);
        }
        else
        {
            move(currentloc);
        }
        
        //Checks if you made it to the goal
        if(currentloc == finish)
        {
            cout << "You have reached the GOAL. Congratulations!"<< endl;
            mazearr.at(prevloc.x).at(prevloc.y) = 0;
            mazearr.at(finish.x).at(finish.y) = 7;
            printmaze(); 
            return true;
        }
        
        //Changes the ID of the locations of the maze to move player's
        //displayed location
        mazearr.at(currentloc.x).at(currentloc.y) = 7;
        
        if(mazearr.at(prevloc.x).at(prevloc.y) == 2)
            mazearr.at(prevloc.x).at(prevloc.y) = 2;
        else
            mazearr.at(prevloc.x).at(prevloc.y) = 0;
            
        printmaze();
    }
} 	    

bool Maze::isPath(const Location &current)
{    
     bool nextloc = false;
     int pathcount = 0;

    //Checks if all cardinal positions from current is valid(0 and not previous movement)
    //then checks if they make up a junction. Movement "forward" is allowed if any one of the directions
    //is valid, else they can only backtrack.
    
    //There's definetly a better way to do this rather than repeating it four times...
         
    Location *newpos = new Location(currentloc.x+1, currentloc.y);
    if(!traversed.at(currentloc.x+1).at(currentloc.y) && (mazearr.at(currentloc.x+1).at(currentloc.y) == 0 || mazearr.at(currentloc.x+1).at(currentloc.y) == 3))
    {
        locstack.pop();
        locstack.push(*newpos);
        nextloc = true;
        pathcount++;
    }
         
    newpos = new Location(currentloc.x-1, currentloc.y);
    if(!traversed.at(currentloc.x-1).at(currentloc.y) && (mazearr.at(currentloc.x-1).at(currentloc.y) == 0 || mazearr.at(currentloc.x-1).at(currentloc.y) == 3))
    {
        locstack.pop();
        locstack.push(*newpos);
        nextloc = true;
        pathcount++;
    }
         
    newpos = new Location(currentloc.x, currentloc.y+1);
    if(!traversed.at(currentloc.x).at(currentloc.y+1) && mazearr.at(currentloc.x).at(currentloc.y+1) == 0 || mazearr.at(currentloc.x).at(currentloc.y+1) == 3)
    {
        locstack.pop();
        locstack.push(*newpos);
        nextloc = true;
        pathcount++;
    }
         
    newpos = new Location(currentloc.x, current.y-1);
    if(!traversed.at(currentloc.x).at(currentloc.y-1) && mazearr.at(currentloc.x).at(currentloc.y-1) == 0 || mazearr.at(currentloc.x).at(currentloc.y-1) == 3)
    {
        locstack.pop();
        locstack.push(*newpos);
        nextloc = true;
        pathcount++;
    }
    
    //Checks if this junction has 3 exits. If so, save the junction twice, so it
    //can be returned to twice to try all 3 paths. If it has 2 exits instead,
    //just keep the junction recorded once.
    if(pathcount >= 3){junction.push(currentloc);}
    if(pathcount >= 2){junction.push(currentloc);}
    
    //Returns true if there is a valid exit point.
    if(nextloc){return true;}
    
    //Returns false if it's a dead end.
    return false;
}

//Moves forwards with a trailing previous Location object turning the accessed
//locations TRUE
void Maze::move(Location &current)
{
     traversed.at(prevloc.x).at(prevloc.y) = true;
     prevloc = currentloc;
     currentloc = locstack.top();
     locstack.push(currentloc);
     traversed.at(currentloc.x).at(currentloc.y) = true;
}

//Simply "warp" back to the previous valid junction.
//This is done because that is the only possible path from the dead end point
//and was already crossed before. Also prints if maze is unsolvable.
void Maze::backtrack(Location &current)
{
    mazearr.at(currentloc.x).at(currentloc.y) = 0;
    if(currentloc == junction.top())
    {
        junction.pop();
    }
    else
    {
        if(!junction.top())
        {
            cout << "Unsolvable Maze: GAME OVER" << endl;
//            exit(1);
        }
        cout << "Dead End: Returning to previous junction" << endl;
        prevloc = currentloc;
        currentloc = junction.top();
        traversed.at(prevloc.x).at(prevloc.y) = true;
        junction.pop();
    }
}

//This function simply calls the printmaze() function to print the maze
//This is becuase it makes it easier to call from main()
void Maze::print(Maze mazegame)
{
     printmaze();
}

//Function to print the maze through a vector of vector of integers
//The switch statement represents each possible value for the representation
//of the maze. 
//P is Player Location.
//* is a valid path.
//" " is a wall/invalid path.
//S and F are Start and Finish respectively
//+, -, and | are part of the maze border.
//X is an invalid text file input
void Maze::printmaze()
{
    for(int i = 0; i < rowtotal; i++)
    {
       for(int j = 0; j < coltotal; j++)
       {
         switch(mazearr.at(i).at(j))
         {
             case 7:
                 cout << "P";
                 break;
             case 0:
                 cout << "*";
                 break;
             case 1:
                 cout << " ";
                 break;
             case 2:
                 cout << "S";
                 break;
             case 3:
                 cout << "F";
                 break;
             case 4:
                 cout << "+";
                 break;
             case 5:
                 cout << "-";
                 break;
             case 6:
                 cout << "|";
                 break;
             default:
                 cout << "X";
         }
       }
       cout << endl;
    }
}
