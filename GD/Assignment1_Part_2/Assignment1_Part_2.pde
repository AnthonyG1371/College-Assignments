PImage img;  // Declare a variable of type PImage
boolean clickvar = false;
boolean pressed = false;
boolean average = false;

void setup() 
{
  size(1032, 570);
  // Make a new instance of a PImage by loading an image file
  img = loadImage("cake.jpg");
}

void draw() 
{
  background(0);
  
  // Draw the image to the screen at coordinate (0,0)
  // or draw the averaged image if the average flag is true
  if(!average)
    image(img,0,0);
  else
    recolor();
}

//If the mouse is clicked, toggle between the averaged and original picture
void mouseClicked()
{
  if(!average)
  {
    average = true;
  }
  else
  {
    average = false;
  }
}

//Takes action depending on the key pressed.
//Options include 'A' for averaged, 'O' for original,
//and 'R','G','B', and 'Y' for colored tints.
void keyPressed()
{
  switch(key)
  {
    case 'a': case 'A':
    {
      average = true;
      break;
    }
    case 'b': case 'B':
    {
      tint(#0006FF);
      average = false;
      break;
    }
    case 'g': case 'G':
    {
      tint(#0BFF00);
      average = false;
      break;
    }
    case 'r': case 'R':
    {
      tint(#FF0000);
      average = false;
      break;
    }
    case 'y': case 'Y':
    {
      tint(#E9FF00);
      average = false;
      break;
    }
    
    case 'o': case 'O':
    {
      noTint();
      average = false;
      break;
    }
  }
}

//Calculates the total rgb values of the picture, then averages all the values
//together to recolor the picture.
void recolor() 
{
  int rtotal = 0, gtotal = 0, btotal = 0;
  
  loadPixels(); 
  img.loadPixels(); 
  for (int y = 0; y < height; y++) 
  {
    for (int x = 0; x < width; x++) 
    {
      int loc = x + y*width;
      
      // The functions red(), green(), and blue() pull out the 3 color components from a pixel.
      float r = red(img.pixels[loc]);
      float g = green(img.pixels[loc]);
      float b = blue(img.pixels[loc]);
      
      // Image Processing would go here
      // If we were to change the RGB values, we would do it here, 
      // before setting the pixel in the display window.
      
      rtotal += r;
      gtotal += g;
      btotal += b;       
    }
  }
  
  rtotal = rtotal/4000;
  gtotal = gtotal/4000;
  btotal = btotal/4000;
  
  for (int y = 0; y < height; y++) 
  {
    for (int x = 0; x < width; x++) 
    {
      int loc = x + y*width;
      
      // Set the display pixel to the image pixel
      pixels[loc] =  color(rtotal,gtotal,btotal);          
    }
  }
  
  updatePixels();
}