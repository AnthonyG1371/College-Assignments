#include"gameboard.h"
//#include"player.h"
//#include"game.h"

void gameboard::setaction(int actnum)
{
  switch (actnum)
  {
    case 7: case 10: case 20:
      action = goagain;
      break;
    case 4: case 13:
      action = loseturn;
      break;
    case 15: case 29:
      action = swaploc;
      break;
    case 2: case 22:
      action = forfour;
      break;
    case 17:
      action = forsix;
      break;
    case 18:
      action = backsix;
      break;
    case 24:
      action = backeight;
      break;
    default:
      action = 0;
  }
}

int gameboard::getaction()
{
  return(action);
}

void gameboard::setcolor(string tempcolor)
{
  color = tempcolor;
}

string gameboard::getcolor()
{
  return(color);
}
//#endif
