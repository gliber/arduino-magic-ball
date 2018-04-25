#include "ICBall.h"



void gameColorfulPlay()
{
  uint32_t chosenColor = BLACK;
  bool colorPainted = false;

  // init
  ICBprintln(F("Colorful START"));
  //effectRainbow();
  setGameValue(BLACK);

  while(!gameChanged())
  {
    
    if (chosenColor != getGameValue())
    {
      chosenColor = getGameValue();
      ICBprint(F("new color "));
      ICBprintln(chosenColor);
      colorPainted = false;
    }
    //colorPainted = false;
    if (!colorPainted)
    {
      solidColorQuick(chosenColor);
      colorPainted = true;
    }
  
    if (chosenColor == RAINBOW)
    {
      effectRainbowSingle();
    }
  }
}

