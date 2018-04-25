#include "ICBall.h"


#define FIRE_EVENTS_DELAY  1000
#define FIRE_MAX_VALUE 300
#define FIRE_STEP_DOWN  5
#define FIRE_DETECTION_NORMAL  2


void gameFirePlay()
{
  unsigned long lastFireEvent = 0;
  int lastTone = 0;
  int fireStatus = 0;

  while (!gameChanged())
 {
    unsigned long current = millis();
    float accelNormal = getAccelerometerNormal();

     if (millis()-lastTone>3000-map(fireStatus,0,FIRE_MAX_VALUE,0,3000))
     {
     tone(ICBALL_BUZZER, NOTE_C3,100);
     lastTone=millis();
     }
     
    if (accelNormal > FIRE_DETECTION_NORMAL)
    {
      fireStatus += accelNormal/2;
      lastFireEvent = current;
      ICBprint(F("FIRE UP "));
      ICBprint(accelNormal);
      ICBprint(" stat=");
      ICBprintln(fireStatus);
    }
    else
    {
      //if ((lastFireEvent > 0) && (current - lastFireEvent > FIRE_EVENTS_DELAY))
      {
        if (fireStatus > 0)
        {
          ICBprint(F("FIRE DOWN "));
          ICBprintln(fireStatus);
        }
        fireStatus -= FIRE_STEP_DOWN;
      }
    }
    if (fireStatus < 0) 
    {
      fireStatus=0;
    }
    if (fireStatus > FIRE_MAX_VALUE) 
    {
      fireStatus = FIRE_MAX_VALUE;
    }
  
    delay(50);
  
    int redValue = fireStatus;
    if (redValue > 255)
    {
      redValue = 255;
    }
    solidColorQuick(colorRGB((redValue/LED_POWER_SAVE_FACTOR), 0, (255-redValue)/LED_POWER_SAVE_FACTOR));
  
    setGameValue(fireStatus);
 }
}

