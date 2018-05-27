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

  void draw()
  {
    stroke( #0000ff );
    fill( #0000ff );
    textSize(20);
    textAlign(LEFT);
    drawchar();
    textAlign(CENTER);

    boardID = ((position.y/50)*15)+(position.x/50);
  }

  //Function to get a new position
  //Named "getNewAgent" initially and the name was never changed.
  void getNewAgent()
  {
    position.set(((int)random(0, max_x+1)/grid_size)*grid_size, 
      ((int)random(0, max_y+1)/grid_size)*grid_size);
  }

  //Function to initialize characters in specific locations
  PVector placeAgent()
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
  void drawchar()
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
  boolean dealdmg() 
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
  void checkDmgState()
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
  void move(int dir) //dir = direction, i = agent ID
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
  void randomMove()
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
  void checkItem()
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
  void chaseItem()
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
  void avoidDanger()
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
  boolean checkName()
  {
    if (name != "Bomberman")
      return true;
    return false;
  }

  //Checks for danger tiles (yellow), as well as blackholes, lava,
  //and obstacles.
  boolean checkTile(int checknum)
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
  void force()
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
  void setPrevPos()
  {
    prevPosition = position;
  }
  
  boolean checkPrevPos()
  {
    if(prevPosition == position)
      return true;
    return false;
  }
}