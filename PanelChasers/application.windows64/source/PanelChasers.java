import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.sound.*; 
import gifAnimation.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class PanelChasers extends PApplet {

/*
     CISC 
     Game Design Term Project
 	Panel Chasers by Anthony Goh
 
   Gif Animation External Library from:
     https://github.com/01010101/GifAnimation
   Processing Sound External Library Used
   
   Credits for music to Hudson Soft Co. Ltd for "Green Greens" music from Bomberman 64.
     Original Name: Unknown, but used in the Green Greens world of that game.
   Credits for music to Capcom Co. Ltd for "bn6-boss" music from Megaman Battle Network 6
     Original Name: "A Surge of Power"
 */



SoundFile greenGarden;
SoundFile bn6Boss;
boolean played;                //Checks to see if music was played in a screen
Gif lava;
Gif blackHole;

//Global Variables
boolean debug = true;          //Enables debug commands
int debugitem = 0;             //Panel to be placed

int min_x = 0;                 //Minimum gameboard width
int min_y = 0;                 //Minimum gameboard height
int max_x = 700;               //Max gameboard width-NOT SCREEN WIDTH
int max_y = 700;               //Max gameboard height-NOT SCREEN HEIGHT
int grid_size = 50;            //Size of a single panel/tile on the game board.
int manualScreen = 0;          //Which page of the manual you are looking at.
int gamescreen = 0;            //The screens in the game. Includes Title Screen, Manual, and the game board itself.
int menuButton = 0;            //Controls the menubuttons of the first main screen
int menuButton2 = 0;           //Controls the menu of the second main screen
int gridArr[] = new int[225];  //The array for the grid...
int startDelay = 0;            //Delay to start the game with a "Ready..." "GO!" signal
boolean gameRunning = false;   
boolean paused = false;
int placedArr[] = new int[4];

String difficulty = "Normal";

PImage sky;
PImage diamond;
PImage larrow;
PImage rarrow;
PImage start;
PImage startLit;
PImage manual;
PImage manualLit;
PImage bomberman;
PImage bombermanBarr;
PImage human;
PImage humanBarr;
PImage dummy, dummy2, dummy3;
PImage dummyBarr, dummyBarr2, dummyBarr3;
PImage sword;
PImage invis;
PImage fire;
PImage wind;
PImage crosshair;
PImage barrier;
PImage heart;
PImage quake;
PImage floor;

int numplayers = 2;            //Hardcoded number of players
int playersleft;
Agent players[] = new Agent[5]; //Array of players class. Allows up to 4 players. Only 2 are used now.
//Despite having 5 slots, only 4 are used. Bad design choice from the start.
Board board;                   //A board class, used for the undelying board.

public void settings()
{
  size( max_x+grid_size, max_y+grid_size+150);
  board = new Board();
}

public void setup()
{
  greenGarden = new SoundFile(this, "greengarden.mp3");
  bn6Boss = new SoundFile(this, "bn6-boss.mp3");
  lava = new Gif(this, "lava.gif");
  lava.loop();
  blackHole = new Gif(this, "black_hole.gif");
  blackHole.loop();
  sky = loadImage("clouds.jpg");
  floor = loadImage("bluetile.png");
  diamond = loadImage("diamond.png");
  larrow = loadImage("arrow-left.png");
  rarrow = loadImage("arrow-right.png");
  start = loadImage("start.png");
  startLit = loadImage("startLit.png");
  manual = loadImage("manual.png");
  manualLit = loadImage("manualLit.png");
  bomberman = loadImage("bomberman.png");
  bombermanBarr =loadImage("barr-bomb.png");
  human = loadImage("human.png");
  humanBarr = loadImage("human-barr.png");
  dummy = loadImage("dummy.png");
  dummy2 = loadImage("dummy2.png");
  dummy3 = loadImage("dummy3.png");
  dummyBarr = loadImage("dummy-barr.png");
  dummyBarr2 = loadImage("dummy-barr2.png");
  dummyBarr3 = loadImage("dummy-barr3.png");
  sword = loadImage("sword.png");
  invis = loadImage("invis.png");
  wind = loadImage("wind.png");
  fire = loadImage("fireball.png");
  crosshair = loadImage("crosshair.png");
  barrier = loadImage("barrier.png");
  heart = loadImage("heart.png");
  quake = loadImage("quake.png");
  players[1] = new Agent(max_x, max_y, "Human");
  players[2] = new Agent(max_x, max_y, "Player2");
  players[3] = new Agent(max_x, max_y, "Player3");
  players[4] = new Agent(max_x, max_y, "Player4");
  for(int i = 0; i < 4; i++)
    placedArr[i] = 0;
  ellipseMode(CORNER);
}

public void draw()
{
  //PLAY MUSIC
  if(gamescreen != 2 && played == false)
  {
    bn6Boss.stop();
    greenGarden.loop();
    played = true;
  }
  if(gamescreen == 2 && played == false)
  {
    greenGarden.stop();
    bn6Boss.loop();
    played = true;
  }
  
  background( 0xffffffff );
  //Draws Main Menu 1
  if (gamescreen == 0)
  {
    fill(0xff000000);
    textSize(70);
    textAlign(CENTER);
    drawButtons();
    text("Panel Chasers", 350, 200);
  } 
  else if (gamescreen == 1)
  {
    drawmanual();
  } 
  else if (gamescreen == 3)
  {
    drawMenu();
  } 
  //Draws gamescreen in play
  else if (gamescreen == 2)
  {
    fill(0xff000000);
    rect(0, max_y+50, max_x+50, 10);
    noFill();
    board.draw();
    for (int i = 1; i <= numplayers; i++) //i = 1 up to and including 4
    {
      if (players[i] != null)
      {
        players[i].checkDmgState();
        players[i].draw();
        noTint();
        int tileID = board.checkID(players[i].boardID);
        //Starts the game with a "Ready?" "GO!" message.
        if (!gameRunning)
        {
          textSize(100);
          startDelay++;
          if (startDelay < 150)
            text("Ready?", 350, 350);
          else if (startDelay < 200 && startDelay >= 150)
            text("GO!", 350, 350);
          else
            gameRunning = true;
        }

        if (players[1] != null)
        {
          if (players[1].forcedMove == true)
            players[1].force();
        }

        if(paused)
        {
          textSize(100);
          text("Paused",350,350);
          textSize(30);
          text("Press Backspace to return to menu", 350,450);
        }
        
        //Controls the CPU characters calling multiple functions in the Agent class
        //Should have been placed in its own seperate function.
        if (i > 1 && playersleft >= 2 && gameRunning == true && paused == false)
        {
          if(players[i].chasing == false)
            players[i].checkItem();
          players[i].moveDelay++;
          //Difficulty only really affects the speed drastically
          //Might be a little TOO fast on hard.
          if(difficulty == "Normal")
            players[i].moveDelay += (int)random(0, 6);
          if(difficulty == "Hard")
            players[i].moveDelay += (int)random(3, 9);
          //AI Movement statements depending on the circumstances
          if (players[i].moveDelay >= 60)
          {
            players[i].setPrevPos();
            
            if (players[i].forcedMove == true)
              players[i].force();
            else if (players[i].boardID == 2)
              players[i].avoidDanger();
            else if (players[i].chasing)
              players[i].chaseItem();
            else
              players[i].randomMove();
              
            //Moves randomly if it's stuck
            if(players[i].checkPrevPos())
              players[i].randomMove();
            players[i].moveDelay = 0;
          }
        }
        tileHappens(tileID, i); //Calls the function to activate tiles.
        if (playersleft <= 1)
        {
          textSize(100);
          text("Player " + i + " wins!", 350, 350);
          gameRunning = false;
        }
      }
    }
  }
}

//Key Pressed event, mainly used for movement and menu interactions
public void keyPressed()
{
  //Debug commands
  if(debug == true)
  {
    switch(key)
    {
      case 's':
        board.gridArr[(int)players[1].boardID+15] = debugitem;
        break;
      case 'd':
        if(debugitem < 13)
          debugitem++;
        break;
      case 'a':
        if(debugitem > 0)
          debugitem++;
        break;
      case 'r':
        for(int i = 0; i <= numplayers; i++)
        {
          if(players[i] != null)
            players[i].getNewAgent();
        }
    }
  }
  //END OF DEBUG COMMANDS
  
  //MAIN MENU 1
  if (players[1] != null)
  {
    switch(key)
    {
    case 10: //ENTER
      if (gamescreen == 0)
      {
        switch(menuButton)
        {
        case 0:
          gamescreen = 3;
          break;
        case 1:
          gamescreen = 1;
          break;
        }
      }
      break;
    }
    
    if(gamescreen == 0)
    {
      switch(keyCode)
      {
      case UP:
        menuButton = 0;
        break;
      case DOWN:
        menuButton = 1;
        break;
      }
    }
    //END OF MENU 1
    
    //MANUAL SCREEN
    if(gamescreen == 1)
    {
      if(key == 8)
        gamescreen = 0;
    }
    
    //MAIN MENU 2
    if(gamescreen == 3)
    {
      if(key == 8) //BACKSPACE
        gamescreen = 0;
      
      switch(menuButton2)
      {
        case 0:
          switch(keyCode)
          {
            case LEFT:
              if(numplayers > 2)
                numplayers--;
              break;
            case RIGHT:
              if(numplayers < 4)
                numplayers++;
              break;
            case DOWN:
              menuButton2 = 1;
          }
          break;
        case 1:
          switch(keyCode)
          {
            case UP:
              menuButton2 = 0;
              break;
            case DOWN:
              menuButton2 = 2;
              break;
            case LEFT:
              if(difficulty == "Hard")
                difficulty = "Normal";
              else if(difficulty == "Normal")
                difficulty = "Easy";
              break;
            case RIGHT:
              if(difficulty == "Easy")
                difficulty = "Normal";
              else if(difficulty == "Normal")
                difficulty = "Hard";
              break;
          }
          break;
        case 2:
          switch(keyCode)
          {
            case UP:
              menuButton2 = 1;
              break;
            case DOWN:
              menuButton2 = 10;
              break;
            case LEFT:
              if(board.gamestage > 0)
                board.gamestage--;
              break;
            case RIGHT:
              if(board.gamestage < 3)
                board.gamestage++;
              break;
          }
          break;
        case 10:
          if(keyCode == UP)
            menuButton2 = 2;
          if(key == 10) //ENTER
          {
            playersleft = numplayers;
            for(int i = 0; i < 225; i++)
              board.setBoard(i);
            gamescreen = 2;
            played = false;
          }
          break;
      }
    }
    //END OF MENU2
    
    //PAUSE BUTTON
    if(numplayers > 1 && gamescreen == 2 && key == 32) //SPACEBAR
    {
      if(paused == false)
        paused = true;
      else
        paused = false;
    }
    //QUIT WHEN PAUSED
    if(gamescreen == 2 && paused == true)
    {
      if(key == 8) //BACKSPACE
      {
        gamescreen = 3;
        played = false;
      }
    }

    //GAME CONTROLS FOR PLAYER 1
    if (numplayers > 1 && gameRunning == true && players[1].forcedMove == false && paused == false)
    {
      switch(keyCode)
      {
      case UP:
        {
          players[1].move(0);
          break;
        }
      case DOWN:
        {
          players[1].move(1);
          break;
        }
      case LEFT:
        {
          players[1].move(2);
          break;
        }
      case RIGHT:
        {
          players[1].move(3);
          break;
        }
      }
    }
  }
}

//The Function that handles what happens when a character moves over a specific
//type of tile. Handled in a large case statement.
//They all correspond to the identical case statement in the Board Class
//Im hindsight, this might have been better implemented in the agent class.
public void tileHappens(int tileID, int i)
{
  switch(tileID)
  {
    case 1: //Red Tile
      if (players[i].dealdmg())
      {
        players[i] = null;
        playersleft--;
      }
      break;
    case 4: //Black Hole
      players[i] = null;
      playersleft--;
      break;
    case 5: //Lava
      if (players[i].dealdmg())
      {
        players[i] = null;
        playersleft--;
      }
      break;
    case 6: //Fireball
      board.gridArr[(int)players[i].boardID] = 0;
      for (int k = 0; k< 5; k++)
      {
        float rand;
        rand = random(0, 225);
        if (board.gridArr[(int)rand] == 0)
          board.gridArr[(int)rand] = 5;
      }
      break;
    case 7: //Lightning
      board.gridArr[(int)players[i].boardID] = 0;
      for (int k = 0; k< 20; k++)
      {
        float rand;
        rand = random(0, 225);
        if (board.gridArr[(int)rand] == 0)
          board.gridArr[(int)rand] = 2;
      }
      break;
    case 8: //HUGE CASE STATEMENT REGARDING THE "Energy Laser" PATH
      board.gridArr[(int)players[i].boardID] = 0;
      int x = (int)players[i].boardID; 
      int y = (int)players[i].boardID;
      while (floor(y/15) > 0)
      {
        y -= 15;
        if (board.gridArr[y] == 0)
          board.gridArr[y] = 2;
      }
      y = ((int)players[i].boardID);
      while (floor(y/15) < 14)
      {
        y += 15;
        if (board.gridArr[y] == 0)
          board.gridArr[y] = 2;
      }
      while (x%15 > 0)
      {
        x -= 1;
        if (board.gridArr[x] == 0)
          board.gridArr[x] = 2;
      }
      x = ((int)players[i].boardID);
      while (x%15 < 14)
      {
        x += 1;
        if (board.gridArr[x] == 0)
          board.gridArr[x] = 2;
      }
      break;
    case 9: //Invisibility
      board.gridArr[(int)players[i].boardID] = 0;
      players[i].invisible = true;
      break;
    case 10: //Wind
      board.gridArr[(int)players[i].boardID] = 0;
      int obtained = i;
      int rand = (int)random(0, 4);
      for (int k = 1; k <= numplayers; k++)
      {
        if (k != obtained && players[k] != null)
        {
          players[k].forcedMove = true;
          players[k].forcedDir = rand;
        }
      }
      break;
    case 11: //Barrier
      board.gridArr[(int)players[i].boardID] = 0;
      players[i].barrier = true;
      break;
    case 12: //Shockwave
      board.gridArr[(int)players[i].boardID] = 0;
      for (int j = -3; j <= 3; j++)
      {
        for (int k = -3; k <= 3; k++)
        {
          if (j == 0 && k == 0)
          {} 
          //CHECK IF LESS THAN 0 OR GREATER THAN 225
          else if ((int)players[i].boardID + j + (15*k) < 0 
            || (int)players[i].boardID + j + (15*k) > 224)
          {} 
          //CHECK IF PAST LEFT BOUNDARY
          else if (((int)players[i].boardID + j + (15*k))%15 >= 12 && (int)players[i].boardID % 15 < 3)
          {} 
          //CHECK IF PAST RIGHT BOUNDARY
          else if (((int)players[i].boardID + j + (15*k))%15 <= 2 && (int)players[i].boardID % 15 > 11)
          {} 
          else if (board.gridArr[(int)players[i].boardID + j + (15*k)] == 0)
          {
            board.gridArr[(int)players[i].boardID + j + (15*k)] = 2;
          }
        }
      }
      break;
    case 13: //Heart
      board.gridArr[(int)players[i].boardID] = 0;
      if(players[i].HP < 3)
        players[i].HP++;
      break;
  }
}

//DRAWS MAIN MENU 1
public void drawButtons()
{
  imageMode(CENTER);
  switch(menuButton)
  {
  case 0:
    image(diamond, 150, 300);
    image(startLit, 350, 300);
    image(manual, 350, 400);
    break;
  case 1:
    image(diamond, 150, 400);
    image(start, 350, 300);
    image(manualLit, 350, 400);
    break;
  }

  imageMode(CORNER);
}

//DRAWS MANUAL
//Incomplete Function. Was going to include manual in-game instead of in an external document
//Still fully functional with page 1 only.
public void drawmanual()
{
  switch(manualScreen)
  {
    case 0:
      textAlign(CENTER);
      textSize(70);
      text("Manual", 350, 100);
      textSize(50);
      textAlign(LEFT);
      text("Controls:", 50, 200);
      textSize(30);
      text("Movement: The four arrow keys", 100, 250);
      text("Pause: Spacebar", 100, 300);
      text("Go Back/Quit: Backspace", 100,350);
      textAlign(CENTER);
      text("That's all there is!", 350, 500);
      text("Refer to the Word Document", 350, 600);
      text("for the complete manual",350,650);
      break;
  }
}

//DRAWS MAIN MENU 2
public void drawMenu()
{
  stroke(0xff000000);
  fill(0xff000000);
  textAlign(LEFT);
  textSize(50);
  text("Number of Players: ", 50, 100);
  text(numplayers, 600, 100);
  text("'Difficulty': ", 50, 200);
  text(difficulty, 400, 200);
  text("Stage: ", 50, 300);
  text(board.stagename, 400, 300);
  textAlign(CENTER);
  text("Start Game!", 350, 400);
  switch(menuButton2)
  {
    case 0:
      if(numplayers != 2)
        image(larrow, 530, 55);
      if(numplayers != 4)
        image(rarrow, 650, 55);
      break;
    case 1:
      if(difficulty != "Easy")
        image(larrow, 335, 160);
      if(difficulty != "Hard")
        image(rarrow, 600, 160);
      break;
    case 2:
      if(board.gamestage > 0)
        image(larrow, 335, 260);
      if(board.gamestage < 3)
        image(rarrow, 680, 260);
      switch(board.gamestage)
      {
        case 0:
          board.stagename = "Standard";
          break;
        case 1:
          board.stagename = "Spacetower";
          break;
        case 2:
          board.stagename = "Obstacle";
          break;
        case 3:
          board.stagename = "Chaos";
          break;
      }
      break;
    case 10:
      image(rarrow, 150, 360);
      image(larrow, 500, 360);
      break;
  } 
}
class Agent
{
  int max_x, max_y;     //Max area of the board-NOT THE SCREEN
  int grid_size = 50;   //Size of a tile on the board
  PVector position;     //PVector of a character's position
  PVector prevPosition; //PVector of a character's previous position

  String name;          //Name of the character
  boolean chasing;      //Is the CPU character chasing an item?
  int chaseID;          //The ID of the location where the CPU agent is trying to move to. 0 to 225
  boolean forcedMove;   //Is the character being forced to move?
  int forcedDir;        //The direction a character is being forced to move: 0 to 4
  int forcedTiles = 0;  //Counter for number of tiles a character has been forced to move.
  int HP = 3;           //Total HP of a character
  int dmgstate = 0;     //Is the character damaged (will trigger flashing/invincibility while not zero)
  int inviscount = 0;   //Count for invisibility item. Seperate from dmgstate.
  int moveDelay = 0;    //Delay for CPU character movement
  float boardID;        //A float of the tile number you are on, from 0 to 224. 
                        //     VERY IMPORTANT, USED IN MANY OF THE FUCNTIONS.
                        //     Had to be a float to be able to convert from a PVector position.
  int tempID;           //A temporary ID. Not used much if at all.

  boolean invisible = false; //Is the character invisible?
  boolean barrier = false;   //Does the character have a barrier?

  Agent(int x, int y, String n)
  {
    name = n;
    max_x = x;
    max_y = y;
    forcedMove = false;
    position = placeAgent();
    prevPosition = null;
    boardID = ((position.y/50)*15)+(position.x/50); //Divide by y columns, then add x rows.
  }

  public void draw()
  {
    stroke( 0xff0000ff );
    fill( 0xff0000ff );
    textSize(20);
    textAlign(LEFT);
    drawchar();
    textAlign(CENTER);

    boardID = ((position.y/50)*15)+(position.x/50);
  }

  //Function to get a new position
  //Named "getNewAgent" initially and the name was never changed.
  public void getNewAgent()
  {
    position.set(((int)random(0, max_x+1)/grid_size)*grid_size, 
      ((int)random(0, max_y+1)/grid_size)*grid_size);
  }

  //Function to initialize characters in specific locations
  public PVector placeAgent()
  {
    int x = (int)random(0,4);
    while(placedArr[x] != 0)
      x = (int)random(0,4);
    if(placedArr[x] == 0)
      placedArr[x] = 1;
    switch(x)
    {
      case 0:
        return new PVector(100,100);
      case 1:
        return new PVector(600,100);
      case 2:
        return new PVector(100,600);
      case 3:
        return new PVector(600,600);
    }
    return new PVector(350,350);
  }
  
  //Draws the characters in the game
  //Includes check for the barrier status
  public void drawchar()
  {
    switch(name)
    {
    case "Human":
      text( name + "'s HP: " + HP, grid_size, max_y + (grid_size*2));
      if (barrier == true)
        image(humanBarr, position.x, position.y);
      else
        image(human, position.x, position.y);
      break;
    case "Player2":
      text(name + "'s HP: " + HP, grid_size, max_y + (grid_size*3));
      if (barrier == true)
        image(dummyBarr, position.x+5, position.y+5);
      else
        image(dummy, position.x+5, position.y+5);
      break;
    case "Player3":
      text(name + "'s HP: " + HP, grid_size + (max_x/2), max_y + (grid_size*2));
      if (barrier == true)
        image(dummyBarr2, position.x+5, position.y+5);
      else
        image(dummy2, position.x+5, position.y+5);
      break;
    case "Player4":
      text(name + "'s HP: " + HP, grid_size + (max_x/2), max_y + (grid_size*3));
      if (barrier == true)
        image(dummyBarr3, position.x+5, position.y+5);
      else
        image(dummy3, position.x+5, position.y+5);
      break;
    }
  }

  //Function to deal 1 point of damage to a character, then give them temporary invincibility.
  public boolean dealdmg() 
  {
    if (dmgstate == 0 && barrier == false)
    {
      HP-=1;
      if (HP == 0)
      {
        return true;
      }
      dmgstate = 1;
    }
    if (barrier == true)
    {
      dmgstate = 1;
      barrier = false;
    }
    return false;
  }

  //Causes "flashing" of a player that was damaged. Shows that they are mostly invincible for the
  //time being. Also used to check for invisibility.
  public void checkDmgState()
  {
    if (dmgstate == 0)
    {} 
    else if (dmgstate < 101 || invisible == true)
    {
      dmgstate+=1;
      if (dmgstate %10 == 0)
        tint(255, 255, 255, 25);
      else
        noTint();
    } 
    else
    {
      dmgstate = 0;
    }

    if (invisible == true)
    {
      if(dmgstate == 0)
        dmgstate = 1;
      if (dmgstate >= 300)
      {
/*        inviscount++;
      if (inviscount >= 10)
      {
        inviscount = 0;*/
        dmgstate = 0;
        invisible = false;
      }
    }
  }

  //Movement Function. Used for both the player and CPU agents.
  //Includes checks for danger tiles and obstacles
  //All characters cannot move through obstacles unless invisible
  //through the invisiblity item.
  //CPU agents will not willingly move into lava, blackholes, and danger tiles
  //though is notoriously bad at avoiding the latter, which helps
  //the player in winning the game.
  public void move(int dir) //dir = direction, i = agent ID
  {
    switch(dir)
    {
    case 0: //UP
      {
        if (boardID>=15)
        {
          if (board.gridArr[(int)boardID-15] != 3 || invisible == true)
          {
            if (checkName() && checkTile((int)board.gridArr[(int)boardID-15]) && forcedMove == false)
              //This and all others below check for conditions where the agent should NOT move.
              //It mainly checks "danger tiles" so the agent won't just walk into them.
            {
            } else
              position.y -= grid_size;
          }
        }
        break;
      }
    case 1: //DOWN
      {
        if (boardID < 210)
        {
          if (board.gridArr[(int)boardID+15] != 3 || invisible == true)
          {
            if (checkName() && checkTile((int)board.gridArr[(int)boardID+15]) && forcedMove == false)
            {
            } else
              position.y += grid_size;
          }
        }
        break;
      }
    case 2: //LEFT
      {
        if (boardID %15 != 0)
        {
          if (board.gridArr[(int)boardID-1] != 3 || invisible == true)
          {
            if (checkName() && checkTile((int)board.gridArr[(int)boardID-1]) && forcedMove == false)
            {
            } else
              position.x -= grid_size;
          }
        }
        break;
      }
    case 3: //RIGHT
      {
        if (boardID%15 != 14)
        {
          if (board.gridArr[(int)boardID+1] != 3 || invisible == true)
          {
            if (checkName() && checkTile((int)board.gridArr[(int)boardID+1]) && forcedMove == false)
            {
            } else
              position.x += grid_size;
          }
        }
        break;
      }
    }
  }

  //Randomly moves an agent.
  public void randomMove()
  {
    moveDelay++;
    if (moveDelay >= 50)
    {
      move((int)random(0, 4));
      moveDelay = 0;
    }
  }

  //Checks if there is an item in a 5 tile radius around the agent, starting with the top left
  // to the bottom right
  public void checkItem()
  {
    for (int i = -5; i < 6; i++)
    {
      for (int j = -5; j < 6; j++)
      {
        tempID = (int)boardID;
        tempID += i;
        tempID += j*15;
        ;
        if (tempID < 0 || tempID > 224)
          tempID = (int)boardID;
        if (board.gridArr[tempID] >= 6)
        {
          chasing = true;
          chaseID = tempID;
        }
      }
    }
  }

  //Attempts to chase an item if one was detected.
  public void chaseItem()
  {
    if (chaseID < boardID && floor(chaseID/15) < floor(boardID/15) )
      move(0);
    else if (chaseID > boardID && floor(chaseID/15) > floor(boardID/15))
      move(1);
    if (chaseID < boardID && chaseID%15 < boardID%15)
      move(2);
    else if (chaseID > boardID && chaseID%15 > boardID%15)
      move(3);
    if (chaseID == boardID || board.gridArr[chaseID] == 0)
      chasing = false;
  }

  //Checks for a yellow danger tile below a CPU character
  //and tells it to move away if on one.
  public void avoidDanger()
  {
    if (board.gridArr[(int)boardID] == 2)
    {
      int rand = (int)random(0, 3);
      switch (rand)
      {
      case 0:
        if (gridArr[(int)boardID] >=15)
        {
          if (gridArr[(int)boardID]-15 == 0)
            position.y -= grid_size;
        } 
        break;
      case 1:
        if (gridArr[(int)boardID] <= 210)
        {
          if (gridArr[(int)boardID]+15 == 0)
            position.y += grid_size;
        } 
        break;
      case 2:
        if (gridArr[(int)boardID] % 15 != 0)
        {
          if (gridArr[(int)boardID]-1 == 0)
            position.x -= grid_size;
        }
        break;
      case 3:
        if (gridArr[(int)boardID] % 15 != 14)
        {
          if (gridArr[(int)boardID]+1 == 0)
            position.x += grid_size;
        }
        break;
      }
    }
  }

  //IF NOT P1
  public boolean checkName()
  {
    if (name != "Bomberman")
      return true;
    return false;
  }

  //Checks for danger tiles (yellow), as well as blackholes, lava,
  //and obstacles.
  public boolean checkTile(int checknum)
  {
    switch(checknum)
    {
    case 3:
      return false;
    case 2: case 4: case 5:
      if (checknum == 2 && name == "Human")
        return false;
      return true;
    }
    return false;
  }

  //Forces movement. Used for the Wind Item
  public void force()
  {
    forcedTiles++;
    if (forcedTiles >= 3)
    {
      forcedMove = false;
      forcedTiles = 0;
    }
    move(forcedDir);
  }
  
  //Sets previous position to current position.
  public void setPrevPos()
  {
    prevPosition = position;
  }
  
  public boolean checkPrevPos()
  {
    if(prevPosition == position)
      return true;
    return false;
  }
}
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
  
  public void draw()
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
          stroke(0xffcccccc);
          //image(floor, gridloc[i].x, gridloc[i].y);
          fill(0xffffffff);
          break;
        case 1: //Damage Panel
          yellowCheck[i]+=1;
          if(yellowCheck[i] >= 50)
          {
            gridArr[i] = 0;
            yellowCheck[i] = 0;
          }
          fill(0xffff0000);
          break;
        case 2: //Warning Panel
          yellowCheck[i]+=1;
          if(yellowCheck[i] >= 40)
            gridArr[i] = 1;
          fill(0xffffff00);
          break;
        case 3: //Obstacle
          fill(0xff999999);
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
  public int checkID(float boardID)
  {
    return (int)gridArr[(int)boardID];
  }
  
  //Generates random items at a set period of time
  //which is 3 items every 3 seconds here
  public void generateItem()
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
  public int getEmpty()
  {
    float rand = random(0,225);
    while(gridArr[(int)rand] != 0)
    {
      rand = random(0,225);
    }
    return (int)rand;

  }
  
  //Set board when starting the game depending on the board selected.
  public void setBoard(int i)
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
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "PanelChasers" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
