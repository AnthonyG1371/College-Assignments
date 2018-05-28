#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <vector>
using namespace std;

struct Location
{
	friend std::ostream &operator <<(std::ostream &os, const Location &location) 
    {
		os << "(" << location.x << ", " << location.y << ")";
		return os;
	}
	bool operator ==(const Location &rhs) const {return x == rhs.x && y == rhs.y;}
	bool operator !=(const Location &rhs) const {return !(*this == rhs);}
	operator bool() const {return x >= 0;}
	Location(int x=-1, int y=-1) : x(x), y(y) {} //constructor
	int x, y;
};

class Maze;

int getrows();
int getcols();
Maze load(string filename);

//Most of the .h file was based on the code on the course website.
//Added a getrows/getcols and load functions.
//Added location to record previous location and an 2d array of vectors to
//check for valid locations
class Maze 
{
	friend std::ostream &operator <<(std::ostream &os, const Maze &maze);
	friend Maze load(string filename, int rowtotal, int coltotal);

    public:
        Maze(vector<vector<int> > inputarr, const Location &start, const Location &finish);
        void print(Maze mazegame);
        void printmaze();
        bool solve();
    //void run();
    private:
 	    bool isPath(const Location &location);
 	    void move(Location &location);
 	    void backtrack(Location &location);
	    Location start, finish;
	    Location currentloc, prevloc;
     
	    vector<vector<int> > mazearr;
	    vector<vector<bool> > traversed;
};

#endif
