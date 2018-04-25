#include "ICBall.h"

#define STATE_STATIC 0
#define STATE_BUMP 1

#define BUMP_DELAY 500


void gameBumpPlay()
{
  int state = STATE_STATIC;
  unsigned long lastBump = 0;
  unsigned int bumps = 0;

  // init
  solidColorQuick(BLACK);
  bumps = 0;
  setGameValue(bumps);

  while (!gameChanged())
  {
    unsigned long current = millis();
    float accelNormal = getAccelerometerNormal();
    if (state == STATE_STATIC)
    {
      if (accelNormal > 20)
      {
        ICBprint(F("BUMP "));
        ICBprint(accelNormal);
        ICBprint(F("  counter "));
        ICBprintln(bumps);
        state = STATE_BUMP;
        solidColorQuick(colorRandom());
        tone(ICBALL_BUZZER, (bumps&1) ?NOTE_C2 : NOTE_C3, 250);
        bumps++;
        setGameValue(bumps);
        lastBump = current;
      }
    }
    else
    {
      if (current - lastBump > BUMP_DELAY)
      {
        ICBprintln("STATIC");
        state = STATE_STATIC;
        solidColorQuick(BLACK);    // Black/off
        lastBump = current;      
      }
    } 
  }
}

