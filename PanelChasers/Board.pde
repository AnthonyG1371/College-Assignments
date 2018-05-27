/*
    The Board Class controls the appearance of the board in the game.
    This consists of the grid itself as well as the various tiles and items
    on it, kept in an array.
*/
class Board
{
  int grid_size = 50;                        //Size of a tile on the board
  final int grid_max = 225;                  //Total number of tiles on the board
  int cooldown = 0;                          //Item respawn cooldown
  int heartCooldown = 0;                     //Heart Item respawn cooldown. Meant to be used on less common items.
  float gridArr[] = new float[grid_max];     //ARRAY OF IDS FOR EACH TILE ON THE BOARD
  PVector gridloc[] = new PVector[grid_max]; //Array of PVectors for each tile on the board
  int gamestage = 0;                         //Stage ID: Standard stage is set as default
  String stagename = "Standard";             //Stage Name: "Standard" is set as default
  int yellowCheck[] = new int[grid_max];     //Counter for yellow tiles to turn into red tiles
  PImage lightning;
  
  Board()
  {
    for(int i = 0; i < grid_max; i++)
    {
      lightning = loadImage("lightning.png");
      setBoard(i);
      gridloc[i] = new PVector((i%15)*grid_size,(i/15)*grid_size);
      yellowCheck[i] = 0;
    }
  }
  
  void draw()
  {
    if(playersleft > 1 && paused == false)
      generateItem();
    
    //Draws the board, using a database of IDs to tell
    //what the tile should contain.
    for(int i = 0; i < grid_max; i++)
    {
      //CASES TO COLOR BOARD
      switch((int)gridArr[i])
      {
        case 0: //Normal Panel
          stroke(#cccccc);
          //image(floor, gridloc[i].x, gridloc[i].y);
          fill(#ffffff);
          break;
        case 1: //Damage Panel
          yellowCheck[i]+=1;
          if(yellowCheck[i] >= 50)
          {
            gridArr[i] = 0;
            yellowCheck[i] = 0;
          }
          fill(#ff0000);
          break;
        case 2: //Warning Panel
          yellowCheck[i]+=1;
          if(yellowCheck[i] >= 40)
            gridArr[i] = 1;
          fill(#ffff00);
          break;
        case 3: //Obstacle
          fill(#999999);
          break;
        case 4: //Black Hole Tile
          image(blackHole, gridloc[i].x, gridloc[i].y);
          break;
        case 5: //Lava
          image(lava, gridloc[i].x, gridloc[i].y);
          break;
        case 6:  //Lava Item
          image(fire, gridloc[i].x, gridloc[i].y);
          break;
        case 7: //Lightning Item
          image(lightning,gridloc[i].x, gridloc[i].y);
          break;
        case 8: //Crosshair Item 
          image(crosshair,gridloc[i].x, gridloc[i].y);
          break;
        case 9: //Invisibility Item
          image(invis,gridloc[i].x, gridloc[i].y);
          break;
        case 10: //Wind Item
          image(wind,gridloc[i].x, gridloc[i].y);
          break;
        case 11: //Barrier Item
          image(barrier,gridloc[i].x, gridloc[i].y);
          break;
        case 12: //Shockwave Item
          image(quake,gridloc[i].x, gridloc[i].y);
          break;
        case 13: // Heart Item
          image(heart,gridloc[i].x, gridloc[i].y);
          break;
        default:
          break;
      }
      if(gridArr[i] < 4) //Greater than number uses Image Files rather than drawn shapes
        rect(gridloc[i].x, gridloc[i].y, grid_size, grid_size);
    }
  }

  //Checks BoardID
  int checkID(float boardID)
  {
    return (int)gridArr[(int)boardID];
  }
  
  //Generates random items at a set period of time
  //which is 3 items every 3 seconds here
  void generateItem()
  {
    cooldown++;
    heartCooldown++;
    //If in the Chaos stage, make it constantly have "lightning strikes"
    if(gamestage == 3 && gameRunning == true)
    {
      if(cooldown%5 == 0)
      gridArr[getEmpty()] = 2;
    }
    
    if(cooldown >= 180)
    {
      for(int i = 0; i < 3; i++)
        gridArr[getEmpty()] = (int)random(7,13);
      cooldown = 0;
    }
    
    //1/5 chance for a heart to spawn every 9 seconds.
    if(heartCooldown >= 900)
    {
      if((int)random(0,5) == 0) 
        gridArr[getEmpty()] = 13;
      heartCooldown = 0;
    }
  }

  //Checks if tile is empty of things besides players.
  int getEmpty()
  {
    float rand = random(0,225);
    while(gridArr[(int)rand] != 0)
    {
      rand = random(0,225);
    }
    return (int)rand;

  }
  
  //Set board when starting the game depending on the board selected.
  void setBoard(int i)
  {
    switch (gamestage)
    {
      case 0: case 3: //Standard and Chaos
        gridArr[i] = 0;
        break;
      case 1: //Spacetower
        if(floor(i/15) == 0 || floor(i/15) == 14 || i%15 == 0 || i%15 == 14)
          gridArr[i] = 4;
        else
          gridArr[i] = 0;
        break;
      case 2: //Obstacle
        if(floor(i/15) != 0 && floor(i/15) != 14 && i%15 != 0 && i%15 != 14)
        {
          if(i%2 == 0 && i%15%2 != 0)
            gridArr[i] = 3;
        }
        break;
    }
  }
}