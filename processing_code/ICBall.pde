import blepdroid.*;
import android.os.Bundle;
import android.content.Context;
import java.util.UUID;
import android.view.MotionEvent;

public static UUID GAME_MODE_CHARACTERISTIC = UUID.fromString( "19B10001-E8F2-537E-4F6C-D104768A1215");
public static UUID GAME_VALUE_CHARACTERISTIC = UUID.fromString( "19B10002-E8F2-537E-4F6C-D104768A1215");

final int STATE_WAIT_FOR_CONNECTION = 10;
final int STATE_MENU = 11;
final int STATE_GAME_COLORFUL = 0;
final int STATE_GAME_BUMP = 1;
final int STATE_GAME_FIRE = 2;
final int STATE_GAME_MOTION_DETECTION = 3;
final int STATE_GAME_SIMON = 4;

int currentState = STATE_WAIT_FOR_CONNECTION;

BlepdroidDevice bdDevice = null;
Blepdroid blepdroid;


GameIcon[] icons = new GameIcon[5];
     
void setup() {
  size(displayWidth,displayHeight);
  orientation(PORTRAIT);
  
  //smooth();
  blepdroid = new Blepdroid(this);
  
 rectMode(CENTER);
    
     icons[0] = new GameIcon("rainbow_icon.jpg", 1, 1, STATE_GAME_COLORFUL);
     icons[1] = new GameIcon("motion_icon.jpg", 1, 3, STATE_GAME_MOTION_DETECTION);
     icons[2] = new GameIcon("ball_icon.jpg", 2, 1, STATE_GAME_BUMP);
     icons[3] = new GameIcon("fire_icon.jpg", 2, 3, STATE_GAME_FIRE);
     icons[4] = new GameIcon("simon_icon.jpg", 3, 2, STATE_GAME_SIMON);
     
}

boolean stateDrawn = false;
boolean scanned = false;

void draw() {
  
  switch (currentState)
  {
    case STATE_WAIT_FOR_CONNECTION:
    waitForConnection();
    break;
    case STATE_MENU:
    menu();
    break;
    case STATE_GAME_COLORFUL:
    gameColurful();
    break;
    case STATE_GAME_BUMP:
    gameBump();
    break;
    case STATE_GAME_MOTION_DETECTION:
    gameMotionDetection();
    break;
    case STATE_GAME_FIRE:
    gameFire();
    break;
    case STATE_GAME_SIMON:
    gameSimon();
    break;
  }
  
}

void waitForConnection()
{
  if (!stateDrawn)
  {
    background(255);
    imageMode(CENTER);
    PImage img = loadImage("disconnected.jpg");
     image(img,width/2,height/2);
     stateDrawn = true;
  }
  if (mousePressed && !scanned)
  {
    blepdroid.scanDevices();
    scanned = true;
  }
}


void checkBackIcon()
{
  // draw it
  imageMode(CORNER);
  image(loadImage("back_icon.jpg"),0,0);
  if (mousePressed)
  {
    if (mouseX<118 && mouseY<118)
    {
      changeState(STATE_MENU);
    }
  }
}
void changeState(int newState)
{
  print("changing state to ");
  println(newState);
  stateDrawn = false;
  currentState = newState;
  byte[] mode = new byte[1];
  mode[0] = (byte) newState;
  blepdroid.writeCharacteristic(bdDevice, GAME_MODE_CHARACTERISTIC, mode);
}

void menu()
{
  if (!stateDrawn)
  {
    background(255);
      for (int i=0; i < icons.length; i++)
        icons[i].draw();
     stateDrawn = true;
  }
  if (mousePressed)
  {
    for (int i=0; i < icons.length; i++)
    {
      if (icons[i].pressed())
      {
        changeState(icons[i].value);
      }
    }
    println("game chosen");
  }
}

void gameFire()
{
  background(0,50,255);
  checkBackIcon();
}

void gameSimon()
{
  background(0,255,255);
  checkBackIcon();
}

void gameBump()
{
  background(255,0,255);
  checkBackIcon();
}

long lastGameValue=0;
int lastChange = 0;
byte rainbowHue = 0;
void gameMotionDetection()
{
  if (gameValueChanged())
  {/*
    long newValue = getGameValue();
    if (lastGameValue != newValue)
    {
      print("==new game value");
      println(newValue);
      lastChange = millis();
    }*/
  }
   colorMode(HSB, 360, 255, 255);
 
  int speed;
  
 // if (millis()-lastChange < 1000)
  {
    fill(color(rainbowHue++, 255,255));
    speed = 400;
  }/*
  else
  {
    fill(255);
    speed = 50;
  }*/
  colorMode(RGB, 255, 255, 255);
 
  background(255,255,0);
  pushMatrix();
  translate(width/2, height/2);
  rotate(frameCount / speed);
  star(0, 0, width/4, height/4, 5);
  popMatrix();
  
  checkBackIcon();
}

int lastColor = 0;
void gameColurful()
{
  int step = 2;
   int rainbowSize = 100;
   
    background(0);
      colorMode(HSB, 360, 255, 255);
 
     for (int i=0; i < 360;i+=step)
    {
       color c = color(i, 255, 255);
      fill(c);
      stroke(c);
      //rect(i, 0, i, height);
      arc(width/2, height/2, min(width,height), min(width,height), radians(i), radians(i+step));
    }
    colorMode(RGB, 255, 255, 255);
 
 int c ;
 
 if (mouseX>width/2-rainbowSize && mouseX<width/2+rainbowSize &&
 mouseY>height/2-rainbowSize && mouseY<height/2+rainbowSize)
 {
   c=0xffffffff;
 }
 else
 {
             c = get(mouseX, mouseY);
 }
            if (c != lastColor)
            {
              lastColor = c;
               println(red(c),green(c), blue(c));
               byte[] colorArray= new byte[4];
               colorArray[0]=(byte) blue(c);
               colorArray[1]=(byte) green(c);
               colorArray[2]=(byte) red(c);
               colorArray[3]=(byte) ((c >> 24) & 0xff);
               
              blepdroid.writeCharacteristic(bdDevice, GAME_VALUE_CHARACTERISTIC, colorArray);
            }
 
 // drawRainbow
             stroke(0);
               fill(255);
               ellipseMode(CENTER);
               ellipse(width/2, height/2, rainbowSize*2,rainbowSize*2);
            
            // draw circle
              stroke(0);
               fill(0);
               ellipseMode(CENTER);
               ellipse(mouseX, mouseY, 100,100);
            
  
   checkBackIcon();
  
}

void connect()
{
  println("scanning devices...");
   
    
}

void disconenct()
{
  if (bdDevice != null)
  {
    //blepdroid.disconnectDevice(bdDevice);
  }
}



void onDeviceDisconnected(BlepdroidDevice device)
{
  changeState(STATE_WAIT_FOR_CONNECTION);
  scanned = false;
}

void onDeviceDiscovered(BlepdroidDevice device)
{
  println("discovered device " + device.name + " address: " + device.address + " rssi: " + device.rssi );
  if(device.name.equals("ICBALL")) // here's where you want to put your own device name
  {
    println("device found. connecting...");
    if(blepdroid.connectDevice(device))
    {
      bdDevice = device; // now store it for later use
    }
  }
}

void onServicesDiscovered(BlepdroidDevice device, int status)
{
  println(" onServicesDiscovered "  );
  println(" 0 means ok, anything else means bad " + status);
  
  HashMap<String, ArrayList<String>> servicesAndCharas = blepdroid.findAllServicesCharacteristics(device);
    println( servicesAndCharas.size() );
    for( String service : servicesAndCharas.keySet())
    {
      print( service + " has " );
      println( servicesAndCharas.get(service));
    }
  // read current state 
  blepdroid.readCharacteristic(bdDevice, GAME_MODE_CHARACTERISTIC);
  //blepdroid.setCharacteristicToListen(bdDevice, GAME_MODE_CHARACTERISTIC);
 // blepdroid.setCharacteristicToListen(bdDevice, GAME_VALUE_CHARACTERISTIC);
}

long getGameValue()
{
  return gameValue;
}

long gameValue = 0;
boolean gameValueRequested = false;
boolean gameValueAck = false;

boolean gameValueChanged()
{
  if (!gameValueRequested)
  {
    println("requesting value");
    blepdroid.readCharacteristic(bdDevice, GAME_VALUE_CHARACTERISTIC);
    gameValueRequested = true;
  }
  else if (gameValueAck)
  {
    gameValueAck = false;
    return true;
  }
    
  return false; 
}

void onCharacteristicRead(BlepdroidDevice device, String characteristic, byte[] data)
{
  print("char read ");
  println(characteristic);
  if (UUID.fromString(characteristic).equals(GAME_VALUE_CHARACTERISTIC))
  {
    gameValueRequested = false;
    gameValueAck = true;
    gameValue = (long) data[0];
  }
  else
  {
    //game mode
  print("current game is ");
  println(data[0]);
  changeState(data[0]);
  }
}

void onCharacteristicChanged(BlepdroidDevice device, String characteristic, byte[] data)
{
  print("characteristic changed");
  println(data[0]);
}

void onBluetoothConnection(BlepdroidDevice device, int state)
{
  println(" onBluetoothConnection " + device.name + " " + state);
  if(state == 2) // connected
  {
    blepdroid.discoverServices(device);
  }
}