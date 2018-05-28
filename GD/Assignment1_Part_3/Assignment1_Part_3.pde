int maxsize = 300;
PVector point1 = randomPoint();
PVector point2 = randomPoint();
PVector point3 = randomPoint();
PVector point4 = randomPoint();
PVector cx1 = randomPoint();
PVector cy1 = randomPoint();
PVector cx2 = randomPoint();
PVector cy2 = randomPoint();
float x1, x2, y1, y2;
int a = randomNum();
int b = randomNum();
boolean clicked = false;
boolean pressed = false;

void settings()
{
  size(maxsize,maxsize);
}

//Sets up the drawing, making sure b is not equal to a.
void setup()
{
  ellipseMode(CENTER);
  background(#ffffff);
  while(b == a)
  {
    b = randomNum();
  }
} 

//Draws the circles and "ellipses". Updates according to changes made.
//Takes many case statements to assign point variables.
void draw()
{
  if(pressed)
  {
    background(#000000);
  }
  else
    background(#ffffff);
  
  fill(#FEFF0D);
  ellipse(point1.x,point1.y,30,30);
  fill(#15FF26);
  ellipse(point2.x,point2.y,30,30);
  fill(#7E17B2);
  ellipse(point3.x,point3.y,30,30);
  fill(#FF0D0D);
  ellipse(point4.x,point4.y,30,30);

  if(clicked)
  {
    fill(#F7FF17);
  }
  else if(pressed)
    fill(#ffffff);
  else
    fill(#000000);

  switch(a)
  {
    case 1:
      x1 = point1.x;
      y1 = point1.y;
      break;
    case 2:
      x1 = point2.x;
      y1 = point2.y;
      break;
    case 3:
      x1 = point3.x;
      y1 = point3.y;
      break;
    case 4:
      x1 = point4.x;
      y1 = point4.y;
      break;
  }
  
  switch(b)
  {
    case 1:
      x2 = point1.x;
      y2 = point1.y;
      break;
    case 2:
      x2 = point2.x;
      y2 = point2.y;
      break;
    case 3:
      x2 = point3.x;
      y2 = point3.y;
      break;
    case 4:
      x2 = point4.x;
      y2 = point4.y;
      break;
  }
  
  if(pressed)
    bezier(x1, y1, cx1.x, cx1.y, cy1.x, cy1.y, x2, y2);
  else
    curve(cx1.x, cx1.y, x1, y1, x2, y2, cy1.x, cy1.y);
}

//Responds to the mouse being clicked.
void mouseClicked()
{
  if(!clicked)
    clicked = true;
  else
    clicked = false;
}

//Responds to any key pressed.
void keyPressed()
{
  if(!pressed)
    pressed = true;
  else
    pressed = false;
}

//Returns a random PVector corresponding to a point
//on the drawing.
PVector randomPoint()
{
  return( new PVector(
  ((int)random(0, maxsize)),
  ((int)random(0, maxsize))));
}

//Returns a random integer from 1 to 4.
int randomNum()
{
  return((int)random(1,4));
}