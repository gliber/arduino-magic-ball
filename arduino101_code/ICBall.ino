
// based on CurieBLE\LED examples 

#include <Adafruit_NeoPixel.h>
#include "CurieIMU.h"
#include <CurieBLE.h>
#include "ICBall.h"

#define GAME_COLORFUL   0
#define GAME_BUMP       1
#define GAME_FIRE       2
#define GAME_MOVEMENT   3
#define GAME_SIMON      4
#define GAME_MENU       11

#define DEFAULT_GAME GAME_MENU

BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService bleService("19B10000-E8F2-537E-4F6C-D104768A1215"); // BLE Service


BLEUnsignedCharCharacteristic gameCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1215", BLERead | BLEWrite);
BLEUnsignedLongCharacteristic valueCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1215", BLERead | BLEWrite | BLENotify);


bool connectionState = false;


void setup() {
  effectsInitLeds();
 
  // init serial communication
  Serial.begin(9600); // initialize Serial communication
  delay(2000); // wait for the serial port to open
  
  // init IMU
  CurieIMU.begin();
  
  // Set the accelerometer range to 8G
  CurieIMU.setAccelerometerRange(8);

  ICBprintln(F("IMU initialized."));
  
    // set advertised local name and service UUID:
  blePeripheral.setLocalName("ICBALL");
  blePeripheral.setAdvertisedServiceUuid(bleService.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(bleService);
  blePeripheral.addAttribute(gameCharacteristic);
  blePeripheral.addAttribute(valueCharacteristic);

  // set the initial value for the characeristic:
  gameCharacteristic.setValue(DEFAULT_GAME);
  valueCharacteristic.setValue(0);
  
  // begin advertising BLE service:
  blePeripheral.begin();

  ICBprintln(F("BLE initialized."));

  ICBprintln(F("LEDs initialized."));

  ICBprint(F("Default game is "));
  ICBprintln(DEFAULT_GAME);
  
//  
  
}  


void loop() {
  //testLeds(50);
  //effectIn();
  
  //effectRainbow();
  startGame(getCurrentGame());
}

bool gameChanged()
{
  BLECentral central = blePeripheral.central();

  // check connection status in this context
  // if a central is connected to peripheral:
  if (central && central.connected()) 
  {
    if (!connectionState)
    {
      ICBprint(F("Connected to central: "));
      // print the central's MAC address:
      ICBprintln(central.address());
      connectionState = true;
      effectFlash(colorRGB(0,50,0),2);
    }
  }
  else
  {
    // we are not conncted now
    if (connectionState)
    {
      connectionState = false;
      effectFlash(colorRGB(50,0,0),2);
      //currentGame = DEFAULT_GAME;
      // when the central disconnects, print it out:
      ICBprint(F("Disconnected from central: "));
      ICBprintln(central.address());
    }
  }
  
  // return if game was changed
  return gameCharacteristic.written();
}

bool gameValueChanged()
{
  return valueCharacteristic.written();
}

int getCurrentGame()
{
  return gameCharacteristic.value();
}

uint32_t getGameValue()
{
  return valueCharacteristic.value();
}

void setGameValue(uint32_t value)
{
  valueCharacteristic.setValue(value);
}


void startGame(int game)
{
  ICBprint(F("Starting game "));
  ICBprintln(game);

  switch (game)
  {
   case GAME_COLORFUL:
    gameColorfulPlay();
   break;
   case GAME_BUMP:
     gameBumpPlay();
     break;
   case GAME_FIRE:
     gameFirePlay();
     break;
   case GAME_MOVEMENT:
     gameMovementDetectionPlay();
     break;
   case GAME_SIMON:
     gameSimonPlay();
     break;
   case GAME_MENU:
     effectBlink();
     while(getCurrentGame()==GAME_MENU)
     {
      gameChanged();
     }
     break;
  }
}

// IMU globabls 



float getAccelerometerNormal()
{  
  // read accelerometer measurements from device, scaled to the configured range
  float accelX, accelY, accelZ;   //scaled accelerometer values
  CurieIMU.readAccelerometerScaled(accelX, accelY, accelZ);
  return accelX*accelX + accelZ*accelZ + accelY*accelY;
}

void getAcceleromter(float& accelX, float& accelY, float& accelZ)
{
  CurieIMU.readAccelerometerScaled(accelX, accelY, accelZ);
}




