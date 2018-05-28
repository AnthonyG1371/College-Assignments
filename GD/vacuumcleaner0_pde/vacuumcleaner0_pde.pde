/**
 * vacuumcleaner.pde
 *
 * 
 *
 */

int min_x = 0;
int min_y = 0;
int max_x = 400;
int max_y = 200;
int grid_size = 200;

boolean dirtLeft = getRandomState();
boolean dirtRight = getRandomState();

PVector cleaner = getRandomLoc();

//cleaner state variables
int STOPPED = 0;
int RUNNING = 1;
int cleanerState = STOPPED;

void settings()
//if you have Processing 2.0 installed, this may not work; move to setup() instead.
{
size( max_x, max_y );
}


/**
 * setup()
 * this function is called once, when the sketch starts up.
 */
void setup() {
  ellipseMode( CORNER );
  cleanerState = RUNNING; 
} // end of setup()

/**
 * draw()
 * this function is called by the Processing "draw" loop,
 * i.e., every time the display window refreshes.
 */
void draw() {
  background( #ffffff );
  stroke( #000000 );
  
  line(grid_size, min_y, grid_size, max_y);
  
  stroke( #cccccc );
  fill( #cccccc );
  
  if (dirtLeft)
    rect(0, 0, grid_size-1, grid_size);
    
  if (dirtRight)
    rect(grid_size+1, 0, grid_size-1, grid_size);
//  noFill();
  
  // draw cleaner
  
  stroke( #0000ff );
  fill( #0000ff );
  
  ellipse(cleaner.x, cleaner.y*2, grid_size/2, grid_size/2 );
  
  if (cleanerState == RUNNING)
    {//fill in with agent's actions here
  }
  
} // end of draw()


/**
 * mouseClicked()
 * this function responds to "mouse click" events.
 */
void mouseClicked() {
  if ( cleanerState == STOPPED ) {
    cleanerState = RUNNING;
  }
  else {
    cleanerState = STOPPED;
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

/* getRandomState()
* this function returns a random boolean 
*/
boolean getRandomState()
{
  int x = int(random(0,2));
  switch (x)
  {
    case 0:
      return false;
    case 1:
      return true;
  }
  return false;
}

void keyPressed()
{
  if(key == 'a')
    moveLeft();
  else if(key =='d')
    moveRight();
  else if(key == 's')
    suck();
}

void moveLeft()
{
  if(cleaner.x < 200)
  {
    println("Cannot move left");
  }
  else
    cleaner.x -= grid_size;
}

void moveRight()
{
  if(cleaner.x >= 200)
  {
    println("Cannot move right");
  }
  else
    cleaner.x += grid_size;
}

void suck()
{
  if(cleaner.x < 200)
  {
    dirtLeft = false;
  }
  else if(cleaner.x >= 200)
  {
    dirtRight = false;
  }
}

void rationalize()
{
  if(cleaner.x < 200)
  {
    if(dirtLeft)
      suck();
    //check if right room is dusty  if()
  }
}