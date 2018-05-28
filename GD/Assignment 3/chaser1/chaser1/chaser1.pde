/**
  * chaser0.pde    23-oct-2011/sklar
  revised 2016 by D. Kletenik
  
  * Processing program that demonstrates chasing. The code is a sample and is
  * intended to be modified as part of your homework assignment.
  * There are two agents: an avatar (controlled by the human player, demonstrated by a purple circle)
  and the
  * opponent (green circle), which acts like a chaser.
  * The goal is for the chaser to catch the human player.
  * See the comments below under keyReleased() for a description of the
  * controls for the avatar (human) player.
  * The homework assignment is to reverse the roles and write an evasion function
  * for the computer player (i.e., Agent.evade()), and make the human the chaser.
  */
static final int NORTH = 0;
static final int WEST  = 1;
static final int SOUTH = 2;
static final int EAST  = 3;

PFont font;
boolean running; // flag set to true while the game is running
Agent avatar; // human player chases the opponent
Agent opponent; // computer player tries to evade the human


/**
 * setup()
 */
void setup() {
  size( 500,500 );
  font = loadFont( "Helvetica-48.vlw" ); 
  textFont( font ); 
  avatar = new Agent( 500, 500, #990099 );
  opponent = new Agent( 500, 500, #009900 );
  running = true;
} // end of setup()


/**
 * draw()
 */
void draw() {
  if ( running ) {
    background( #ffffff );
    avatar.draw();
    opponent.draw();
    if ( isCaught() ) {
      avatar.stop();
      opponent.stop();
      fill( #000000 );
      textAlign( CENTER );
      text( "GOTCHA!", 250, 250 );
      running = false;
    }
    else {
      opponent.evade( avatar.getPos() );
    }
    
    stroke( #cccccc );
    fill( #FF0000 ); //Red
  }
} // end of draw()

/**
 * isCaught()
 * this function returns true if the avatar and the opponent are touching.
 */
boolean isCaught() {
  float r1 = avatar.getDiameter() / 2;
  PVector avatarCenter = new PVector( avatar.getPos().x+r1, avatar.getPos().y+r1 );
  float r2 = opponent.getDiameter() / 2;
  PVector opponentCenter = new PVector( opponent.getPos().x+r2, opponent.getPos().y+r2 );
  float d = sqrt( sq(avatarCenter.x - opponentCenter.x) + sq(avatarCenter.y - opponentCenter.y ));
  if ( d < r1 + r2 ) {
    return( true );
  }
  else {
    return( false );
  }
} // end of isCaught()

PVector getRandomLoc() {
  return( new PVector(
  ((int)random(0,500)),
  ((int)random(0,500))));
}

/**
 * keyReleased()
 * this function is called when the user releases a key.
 * the arrow keys act like giving the avatar agent a kick in the direction of the arrow.
 * in addition, the following keys are active:
 *  s or S to stop the avatar moving (set velocity to 0)
 *  r or R to reset both the avatar and the opponent (move to random positions and set velocities to 0)
 *  q or Q to quit the game
 */
void keyReleased() {
  if ( key == CODED ) {
    switch ( keyCode ) {
    case UP:
      avatar.kick( NORTH );
      break;
    case DOWN:
      avatar.kick( SOUTH );
      break;
    case LEFT:
      avatar.kick( WEST );
      break;
    case RIGHT:
      avatar.kick( EAST );
      break;
    }
  }
  else if (( key == 's' ) || ( key == 'S' )) {
    avatar.stop();
  }
  else if (( key == 'r' ) || ( key == 'R' )) {
    avatar.reset();
    opponent.reset();
    running = true;
  }
  else if (( key == 'q' ) || ( key == 'Q' )) {
    exit();
  }
} // end of keyReleased()