/**
 * sample prisoner's dilemma game
 * sklar/27-nov-2011
 */

//--- declare global variables ---
int move_number;        // counts the number of moves in the game
char p1_move;           // stores the move made by player 1 (the human player)
char p2_move;           // stores the move made by player 2 (the computer player)
char p1_last_move;      // stores the previous move made by player 1
int p1_score;           // stores the score for player 1 for the current move
int p2_score;           // stores the score for player 2 for the current move
int p1_total_score;     // stores the accumulated score for player 1
int p2_total_score;     // stores the accumulated score for player 2
String statusMsg = "";  // stores a status message to display in the display window


/**
  * setup()
  * this function initializes global variables.
  * it also sets the size for the display window and initializes a font for displaying
  * text in the display window.
  */
void setup() {
  move_number = 0;
  p1_score = 0;
  p2_score = 0;
  p1_move = ' ';
  p2_move = ' ';
  p1_last_move = ' ';
  size( 400,400 );
  PFont font;
  font = loadFont( "SansSerif-48.vlw" );
} // end of setup()



/**
  * draw()
  * this function updates the display window.
  * it is called repeatedly by the Processing main loop.
  */
void draw() {
  background( #ffffff );
  fill( #cc00cc );
  text( "player 1 score: " + str(p1_score) + " total = " + str(p1_total_score), 10,  90 );
  text( "player 2 score: " + str(p2_score) + " total = " + str(p2_total_score), 10, 110 );
  fill( #00cccc );
  text( "player 1 move: " + p1_move, 10, 190 );
  text( "player 2 move: " + p2_move, 10, 210 );
  if ( statusMsg.length() > 0 ) {
    fill( #00cc00 );
    text( statusMsg, 10, 300 );
  }
} // end of draw()



/**
  * keyPressed()
  * this function is called when the user presses a key.
  * it sets the human player's move, if a valid move key is pressed.
  * the human player should enter 'C' or 'c' for a "cooperate" move,
  * and 'D' or 'd' for a "defect" move.
  */
void keyPressed() {
  switch( key ) {
  case 'c':
  case 'C':
    p1_last_move = p1_move;
    p1_move = 'C';
    statusMsg = "cooperate";
    break;
  case 'd':
  case 'D':
    p1_last_move = p1_move;
    p1_move = 'D';
    statusMsg = "defect";
    break;
  default:
    p1_move = ' ';
    statusMsg = "invalid move";
    break;
  }
  if ( p1_move != ' ' ) {
    p2_move = computer_move();
    compute_payoff();
    p1_total_score += p1_score;
    p2_total_score += p2_score;
    move_number++;
  }
} // end of keyPressed()



/**
  * computer_move()
  * this function returns the computer player's move,
  * which is either 'C' for cooperate or 'D' for defect.
  * this function uses the "tit for tat" strategy.
  */
char computer_move() {
  if ( move_number == 0 ) {
    return( 'C' );
  }
  else {
    return( p1_last_move );
  }
} // end of computer_move()



/**
  * compute_payoff()
  * this function computes the payoffs for each player, based on the moves.
  * the current payoff setting used is the classic Prisoner's Dilemma game.
  */
void compute_payoff() {
  if ( p1_move == 'D' ) {
    if ( p2_move == 'D' ) {
      // defect,defect
      p1_score = 2;
      p2_score = 2;
    }
    else { // p2_move == 'C'
      // defect,cooperate
      p1_score = 4;
      p2_score = 1;
    }
  }
  else { // p1_move == 'C'
    if ( p2_move == 'D' ) {
      // cooperate,defect
      p1_score = 1;
      p2_score = 4;
    }
    else { // p2_move == 'C'
      // cooperate,cooperate
       p1_score = 3;
       p2_score = 3;
   }
  }
} // end of compute_payoff()

