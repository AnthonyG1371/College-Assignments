/**
  * Agent.pde    23-oct-2011/sklar
  */
class Agent {

  PVector pos; // current (x,y) position of agent
  PVector vel; // current velocity of agent
  PVector acc; // current acceleration of agent
  int d = 30;  // diameter of the agent
  int max_x, max_y; // maximum x and y values for the agent (i.e., size of the arena)
  color mycolor; // the color for drawing the agent

  /**
   * agent constructor
   */
  Agent( int x0, int y0, int c0 ) {
    max_x = x0;
    max_y = y0;
    mycolor = color( c0 );
    ellipseMode( CORNER );
    pos = new PVector( random(max_x-d), random(max_y-d) );
    vel = new PVector( 0, 0 );
    acc = new PVector( 0.5, 0.5 );
  } // end of agent constructor

  /**
   * reset()
   * resets the agent's position (to random) and velocity (to 0)
   */
  void reset() {
    pos.set( random( max_x-d ), random( max_y-d ), 0 );
    vel.set( 0, 0, 0 );
  } // end of reset()

  /**
   * getPos()
   * returns the agent's current (x,y) position
   */
  PVector getPos() {
    return( pos );
  } // end of getPos()

  /**
   * getDiameter()
   * returns the diameter of the agent
   */
  int getDiameter() {
    return( d );
  } // end of getDiameter()

  /**
   * draw()
   * this function draws the agent
   */
  void draw() {
    noFill();
    stroke( mycolor );
    strokeWeight( 3 );
    ellipse( pos.x, pos.y, d, d );
    //Rewritten to loop the player and agent around the field
    if ( pos.x+vel.x < 0 ) pos.x = max_x-d;
    if ( pos.x+vel.x > max_x - d) pos.x = 0;
    if ( pos.y+vel.y < 0 ) pos.y = max_y-d;
    if ( pos.y+vel.y > max_y - d) pos.y = 0;
    pos.x += vel.x;
    pos.y += vel.y;
  } // end of draw()

  /**
   * kick()
   * adjusts the agent's velocity, as if it received a kick in the direction specified
   * by the "direction" argument
   */
  void kick( int direction ) {
    switch( direction ) {
    case NORTH:
      vel.y -= acc.y;
      break;
    case SOUTH:
      vel.y += acc.y;
      break;
    case WEST:
      vel.x -= acc.x;
      break;
    case EAST:
      vel.x += acc.x;
      break;
    } // end switch
  } // end of kick()

  /**
   * stop()
   */
  void stop() {
    vel.x = 0;
    vel.y = 0;
  } // end of stop()

  /**
   * chase()
   * this function implements the "line of sight" algorithm from 
   * ch 2 of AI for Game Developers by Bourg and Sleemann (2004)
   */
  void chase( PVector opponent ) {
    // calculate "difference" vector between this agent and the opponent
    PVector diff = pos.sub( opponent,pos );
    // compute the distance between this agent and the opponent (magnitude of difference vector)
    float d = diff.mag();
    if ( d > 0 ) {
      // normalize difference vector
      diff.normalize();
      // adjust x and y velocity according to the difference vector
      vel = opponent.sub( diff, vel );
    }
  } // end of chase()
  
  /**
   * evade()
   * Uses a modified version of chase() as its base.
   * Mostly a reversed chase(), further details explained below.
   */
   void evade( PVector opponent ) {
    boolean keepdist = false;
    boolean keepevade = false;
    double diffmag;
    //** YOU NEED TO WRITE THIS CODE! **
    
    // calculate "difference" vector between this agent and the opponent
    PVector diff = pos.sub( opponent,pos );
    // compute the distance between this agent and the opponent (magnitude of difference vector)
    float d = diff.mag();
    // Now checks two flags to depending on the position/reigon of ther computer controlled agent.
    // Either 1: 300<x.   2: 200<x<300   3: x<200
    if ( d > 0 ) {
      if(diff.mag() > 300)
      {
        keepdist = true;
        keepevade = false;
      }
      else if(diff.mag() < 200)
      {
        keepevade = true;
        keepdist = false;
      }
      else
      {
        keepevade = false;
        keepdist = false;
      }
      // normalize difference vector (sets it to 1)
      diff.normalize();
      // adjust x and y velocity according to the difference vector
      
      /* If greater than 300 pixels away, the agent comes closer to the player.
       * If less that 200 pixels away, the agent runs away from the player.
       * Between those two values, the agent does whatever action it was doing last.
       * This can result in the agent simply not moving  at first if initialized between 200 and 300 pixels away.
       * This is to keep the agent at an optimal distance from the player within this field.
       */
      if(keepdist)
      {
        vel = opponent.sub( diff, vel );
      }
      if(keepevade)
      {
          vel = opponent.sub( diff, vel );
          vel.x *= -0.5;
          vel.y *= -0.5;
      }
    }
   } // end of evade()
   
   //Randomly sets a velocity for the CPU agent between -2 and 2.
   //Used as a crude obstacle avoiding strategy.
   void travelRandom()
   {
     float xspeed = random(-2,2);
     float yspeed = random(-2,2);
     
     vel.x = xspeed;
     vel.y = yspeed;
   }
} // end of agent class