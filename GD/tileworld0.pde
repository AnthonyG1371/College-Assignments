/**
 * tileworld0.pde
 *
 * This program simulates a simplified version of the class TileWorld.
 * This code was written to be used as a skeleton for Assignment II for
 * CISC 3665 / Game Design.
 
 * created: 19-sep-2011/sklar
 * updated: 4-oct-2011/sklar - 
 *  corrected use of random() to which has an inclusive lower bound, but not
 *  an inclusive upper bound
 updated: Spring 2016 by D. Kletenik
 *
 */
 
 /*
 * Assignment 2 Part 1: Anthony Goh
 */

int min_x = 0;
int min_y = 0;
int max_x = 400;
int max_y = 600;
int grid_size = 10;

PVector agent = getRandomLoc();
PVector[] hole = new PVector[3];
PVector[] tile = new PVector[2];
PVector[] obstacle = new PVector[4];
PVector[] locs = new PVector[9];

boolean seperate = false;

int sensorON = 0;
int sensorOS = 0;
int sensorOE = 0;
int sensorOW = 0;
int sensorTN = 0;
int sensorTS = 0;
int sensorTE = 0;
int sensorTW = 0;
int sensorHN = 0;
int sensorHS = 0;
int sensorHE = 0;
int sensorHW = 0;


// agent state variables
final int STOPPED = 0;
final int RUNNING = 1;
int agentState = STOPPED;

//-----1.1
//SETS UP THE PROGRAM AS WELL AS THE OBJECTS IN IT
void settings()
{
  size( max_x, max_y );
  //Gets all locations for the various objects
  for(int i = 0; i < 3; i++)
  {
    hole[i] = getRandomLoc();
    locs[i] = hole[i];
  }  
  for(int i = 0; i < 2; i++)
  {
    tile[i] = getRandomLoc();
    locs[i+3] = tile[i];
  }
  for(int i = 0; i < 4; i++)
  {
    obstacle[i] = getRandomLoc();
    locs[i+5] = obstacle[i];
  }
  
  while(!seperate)
  {
    seperate = true;
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        //Added condition to prevent checking the same exact tile
        if(i == j)
        {
        }
        else if(locs[i] == locs[j])
        {
          switch(i)
          {
            case 0: case 1: case 2:
            {
              hole[i] = getRandomLoc();
              seperate = false;
              break;
            }
            case 3: case 4:
            {
              tile[i-3] = getRandomLoc();
              seperate = false;
              break;
            }
            case 5: case 6: case 7: case 8:
            {
              obstacle[i-5] = getRandomLoc();
              seperate = false;
              break;
            }
          }
        }
      }
      if(agent == locs[i])
      {
        agent = getRandomLoc();
        seperate = false;
      }
    }
  }
}

/**
 * setup()
 * this function is called once, when the sketch starts up.
 */
void setup() {
  ellipseMode( CORNER );  
  agentState = RUNNING;
} // end of setup()



/**
 * draw()
 * this function is called by the Processing "draw" loop,
 * i.e., every time the display window refreshes.
 */
void draw() {
  // draw grid for TileWorld
  background( #ffffff );
  stroke( #cccccc );
  for ( int x=min_x; x<=max_x; x+=grid_size ) {
    line( x,min_y,x,max_y );
  }
  for ( int y=min_y; y<=max_y; y+=grid_size ) {
    line( min_x,y,max_x,y );
  }
  // draw obstacle
  stroke( #cccccc );
  fill( #FF0000 ); //Red
  for(int i = 0; i < 4; i++)
  {
    rect( obstacle[i].x, obstacle[i].y, grid_size, grid_size );
  }
  // draw hole
  stroke( #cccccc );
  fill( #000000 ); //Black
  for(int i = 0; i < 3; i++)
  {
    rect( hole[i].x, hole[i].y, grid_size, grid_size );
  }
  // draw tile
  stroke( #cccccc );
  fill( #cc00cc ); //Magenta
  for(int i = 0; i < 2; i++)
  {
    rect( tile[i].x, tile[i].y, grid_size, grid_size );
  }
  noFill();
  // draw agent
  if ( agentState == RUNNING ) {
    makeRandomMove();
    delay(100); //slows down movement of agent so you can see where it's going
  }
  stroke( #0000ff );
  fill( #0000ff );
  ellipse( agent.x, agent.y, grid_size, grid_size );
} // end of draw()


/**
 * mouseClicked()
 * this function responds to "mouse click" events.
 */
void mouseClicked() {
  if ( agentState == STOPPED ) {
    agentState = RUNNING;
  }
  else {
    agentState = STOPPED;
  }
} // end of mouseClicked()


/**
 * getRandomLoc()
 * this function returns a new PVector set to a random discrete location
 * in the grid.
 */
PVector getRandomLoc() {
  return( new PVector(
  ((int)random(min_x,max_x+1)/grid_size)*grid_size,
  ((int)random(min_y,max_y+1)/grid_size)*grid_size ));
} // end of getRandomLoc()


/**
 * makeRandomMove()
 * this function causes the agent to move randomly (north, south, east or west).
 * if the agent reaches the edge of its world, it wraps around.
 */

void makeRandomMove() {
  int direction = (int)random(0,4);
  boolean badmove = true;
  perceive();
  while(badmove)
  {
    direction = (int)random(0,4);
    badmove = avoidhole(direction);
  }
  switch(direction) {
  case 0: // move north
    agent.y -= grid_size;
    if ( agent.y < min_y ) {
      agent.y = max_y - grid_size;
    }
    break;
  case 1: // move west
    agent.x -= grid_size;
    if ( agent.x < min_x ) {
      agent.x = max_x - grid_size;
    }
    break;
  case 2: // move south
    agent.y += grid_size;
    if ( agent.y > max_y ) {
      agent.y = min_y;
    }
    break;
  case 3: // move east
    agent.x += grid_size;
    if ( agent.x > max_x ) {
      agent.x = min_x;
    }
    break;
  } // end of switch
  
  checktile(direction);
  checkObstacle(direction);
  checkhole();
} // end of makeRandomMove()

//-----1.2
//CHECKS FOR TILES WITHIN A GIVEN LENGTH
//IN REALITY...IT CAN SEARCH ANYWHERE IN THAT GIVEN LENGHT IN A CROSS SHAPE ACROSS THE WHOLE BOARD
void perceive()
{
  //CHECKING TILES: 5 RANGE SIGHT, 2 TILES
  for(int i = 0; i < 5; i++)
  {
    for(int j = 0; j < 2; j++)
    {
      //AGENT IS EAST OF TILE      
      if(agent.x+(i * grid_size) == tile[j].x)
      {
        sensorTE = i;
      }
      //AGENT IS WEST OF TILE
      if(agent.x-(i * grid_size) == tile[j].x)
      {
        sensorTW = i;
      }
      //AGENT IS SOUTH OF TILE
      if(agent.y-(i * grid_size) == tile[j].y)
      {
        sensorTN = i;
      }
      //AGENT IS NORTH OF TILE
      if(agent.y+(i * grid_size) == tile[j].y)
      {
        sensorTS = i;
      }
    }
  }
  
  //CHECKING OBSTACLES: 3 RANGE SIGHT, 4 OBSTACLES
  for(int i = 0; i < 2; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      if(agent.x+(i * grid_size) == obstacle[j].x)
      {
        sensorOE = i;
      }
      if(agent.x-(i * grid_size) == obstacle[j].x)
      {
        sensorOW = i;
      }
      if(agent.y+(i * grid_size) == obstacle[j].y)
      {
        sensorOS = i;
      }
      if(agent.y-(i * grid_size) == obstacle[j].y)
      {
        sensorON = i;
      }
    }
  }
  
  //CHECKING HOLES: 2 RANGE SIGHT, 3 HOLES
  for(int i = 0; i < 1; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      if(agent.x+(i * grid_size) == obstacle[j].x)
      {
        sensorOE = i;
      }
      if(agent.x-(i * grid_size) == obstacle[j].x)
      {
        sensorOW = i;
      }
      if(agent.y+(i * grid_size) == obstacle[j].y)
      {
        sensorOS = i;
      }
      if(agent.y-(i * grid_size) == obstacle[j].y)
      {
        sensorON = i;
      }
    }
  }
}//END OF PERCEIVE...

//-----1.3, 1.6
//CHECKS FOR ALL OBSTACLE INTERACTIONS
void checkObstacle(int direction)
{
  boolean tileblocked = false;
  //BLOCKS THE AGENT FROM ACESSING THE OBSTACLE BY "BOUNCING" IT BACK
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 2; j++)
    {
      if(tile[j].x == obstacle[i].x && tile[j].y == obstacle[i].y)
      {
        switch (direction)
        {
          case 0: // north
            tile[j].y += grid_size;
            tileblocked = true;
            break;
          case 1: // west
            tile[j].x += grid_size;
            tileblocked = true;
            break;
          case 2: // south
            tile[j].y -= grid_size;
            tileblocked = true;
            break;
          case 3: // east
            tile[j].x -= grid_size;
            tileblocked = true;
            break;
        }
      }
    }
    
    //BLOCKS BOTH THE AGENT AND THE TILE(IF APPLICABLE) FROM MOVING INTO AN OBSTACLE SQUARE
    if(agent.x == obstacle[i].x && agent.y == obstacle[i].y || tileblocked)
    {
      switch(direction)
      {
        case 0: // north
          agent.y += grid_size;
          break;
        case 1: // west
          agent.x += grid_size;
          break;
        case 2: // south
          agent.y -= grid_size;
          break;
        case 3: // east
          agent.x -= grid_size;
          break;
      } // end of switch
    }
  }
}

//-----1.5
//DOES NOT PERMIT THE AGENT FROM FALLING INTO THE HOLE
boolean avoidhole(int direction)
{
  for(int i = 0; i < 3; i++)
  {
    switch(direction)
    {
      case 0:
      {
        if(agent.x == hole[i].x && agent.y-grid_size == hole[i].y)
        {
          return true;
        }
      }
      case 1:
      {
        if(agent.x-grid_size == hole[i].x && agent.y == hole[i].y)
        {
          return true;
        }
      }
      case 2:
      {
        if(agent.x == hole[i].x && agent.y+grid_size == hole[i].y)
        {
          return true;
        }
      }
      case 3:
      {
        if(agent.x+grid_size == hole[i].x && agent.y == hole[i].y)
        {
          return true;
        }
      }
    } 
  }
  return false;
}

//-----1.4, 1.6
//CHECKS IF THE AGENT FELL IN THE HOLE, AS WELL AS IF A TILE FELL IN
void checkhole()
{
  for(int i = 0; i < 3; i++)
  {
    if(agent.x == hole[i].x && agent.y == hole[i].y)
    {
      println("GAME OVER");
      noLoop();
    }
    for(int j = 0; j < 2; j++)
    {
      if(tile[j].x == hole[i].x && tile[j].y == hole[i].y)
      {
        println("You got 1 dollar");
        tile[j].x = 3000; tile[j].y = 3000;
      }
    }
  }
}

//-----1.6
//CHECKS IF THE AGENT IS IN A TILE SPACE AND MOVES THE TILE IF IT IS
//ALSO INCLUDES THE CHECK FOR WHEN A TILE IS PUSHED ON A TILE
void checktile(int direction)
{
  for(int i = 0; i < 2; i++)
  {    
    if(agent.x == tile[i].x && agent.y == tile[i].y)
    {
      switch(direction) 
      {
        case 0: // north
          tile[i].y -= grid_size;
          if ( tile[i].y < min_y ) {
              tile[i].y = max_y - grid_size;
          }
          break;
        case 1: // west
          tile[i].x -= grid_size;
          if ( tile[i].x < min_x ) {
            tile[i].x = max_x - grid_size;
          }
          break;
        case 2: // south
          tile[i].y += grid_size;
          if ( tile[i].y > max_y ) {
            tile[i].y = min_y;
          }
          break;
        case 3: // east
          tile[i].x += grid_size;
          if ( tile[i].x > max_x ) {
            tile[i].x = min_x;
          }
          break;
      } // end of switch
    }
    
    //BOUNCES BACK BOTH THE TILE AND THE AGENT IF IT TRIES TO PUSH A TILE ONTO ANOTHER TILE
    if(tile[0].x == tile[1].x && tile[0].y == tile[1].y)
    {
      switch(direction) 
      {
        case 0: // north
          agent.y += grid_size;
          tile[i].y += grid_size;
          if ( tile[i].y < min_y ) {
              tile[i].y = max_y - grid_size;
          }
          break;
        case 1: // west
          agent.x += grid_size;
          tile[i].x += grid_size;
          if ( tile[i].x < min_x ) {
            tile[i].x = max_x - grid_size;
          }
          break;
        case 2: // south
          agent.y -= grid_size;
          tile[i].y -= grid_size;
          if ( tile[i].y > max_y ) {
            tile[i].y = min_y;
          }
          break;
        case 3: // east
          agent.x -= grid_size;
          tile[i].x -= grid_size;
          if ( tile[i].x > max_x ) {
            tile[i].x = min_x;
          }
          break;
      }
    }
  }
}
//END OF PROGRAM
//...THERE ARE TOO MANY NESTED LOOPS AND REDUNDANT CODE...