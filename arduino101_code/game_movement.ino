#include "ICBall.h"


#define DETECTION_EFFECT_PERIOD 5000
#define DETECTION_THRESHOLD_NORMAL   1.5

unsigned long lastMovementDetection = 0;


void gameMovementDetectionPlay()
{
  int count=0;
  solidColorQuick(BLACK);

setGameValue(count++);

  while (!gameChanged())
  {
    unsigned long current = millis();
    if (lastMovementDetection > 0) 
    {
      if (current - lastMovementDetection > DETECTION_EFFECT_PERIOD)
      {
        lastMovementDetection = 0;
        solidColorQuick(BLACK);
      }
    }
    else if (getAccelerometerNormal() > DETECTION_THRESHOLD_NORMAL)
    {
      lastMovementDetection = current;
      setGameValue(count++);
      ICBprintln(F("MOVEMENT detected"));
    }
    if (lastMovementDetection > 0)
    {
      effectRainbowSingle();
      delay(15);  
    }
  }
}

