#include <Adafruit_NeoPixel.h>

#define LEDS_COUNT   64
#define PIXEL_PIN  6
#define NUM_LEDS_PER_STRIP  8
#define NUM_STRIPS      8

#define NUM_TOTAL_LEDS     (NUM_LEDS_PER_STRIP * NUM_STRIPS)


byte positionTranslation[64] = {
3, 2, 1, 0,
32,33,34,35,

4, 5, 6, 7,
63,62,61,60,

11,10,9,8,
56,57,58,59,

12,13,14,15,
55,54,53,52,

19,18,17,16,
48,49,50,51,

20,21,22,23,
47,46,45,44,

27,26,25,24,
40,41,42,43,

28,29,30,31,
39,38,37,36,
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);


void effectsInitLeds()
{
  strip.begin();
  // turn off all LEDs
  solidColorQuick(BLACK);
}

uint32_t stripColors[NUM_STRIPS*NUM_LEDS_PER_STRIP];

void setPixelColor(int pixel, uint32_t color)
{
  stripColors[pixel] = color;
}

int maxPowerUsed;
void effectShow()
{
  int powerUsed = 0;
  for(uint16_t i=0; i<NUM_TOTAL_LEDS;i++)
  {
    uint32_t color = stripColors[i];
    uint32_t b = (color & 0xff);
    uint32_t g =  ((color >> 8) & 0xff);
    uint32_t r = ((color >> 16) & 0xff);
    uint32_t sum = r+g+b;
    powerUsed += sum;
    if (sum > 255)
    {
      r = r *255 / sum;
      g = g*255/sum;
      b = b*255/sum;
      color = b + (g << 8) + (r << 16);
    }
    strip.setPixelColor(positionTranslation[i], color);
  }
  if (powerUsed > maxPowerUsed)
  {
    maxPowerUsed = powerUsed;
    ICBprint("max power ");
    ICBprintln(maxPowerUsed);
  }
  strip.show();
}
  
void solidColorQuick(uint32_t c) 
{
  solidColor(c,0);
}

// Fill the dots one after the other with a color
void solidColor(uint32_t c, uint16_t duration) {
  for(uint16_t i=0; i<NUM_LEDS_PER_STRIP; i++) {
    for(uint16_t j=0; j<NUM_STRIPS; j++) {
      uint16_t pixel = j*NUM_LEDS_PER_STRIP+i;
      setPixelColor(pixel, c);
    }
    if (duration != 0)
    {
      effectShow();
    }
    delay(duration/NUM_LEDS_PER_STRIP);
  }
  if (duration == 0)
  {
    effectShow();
  }
}


// Fill the dots one after the other with a color
void testLeds(uint32_t c) {
  for(uint16_t i=0; i<NUM_STRIPS; i++) {
    for(uint16_t j=0; j<NUM_LEDS_PER_STRIP; j++) {
      uint16_t pixel = i*NUM_LEDS_PER_STRIP+j;
      strip.setPixelColor(positionTranslation[pixel], c);
      strip.show();
      delay(1000);
    }
  }
}



void effectRow(uint8_t rowNumber, uint32_t c) {
  for(uint16_t j=0; j<NUM_STRIPS; j++) 
  {
    uint16_t pixel = j*NUM_LEDS_PER_STRIP+rowNumber;
    setPixelColor(pixel, c);
  }
  effectShow();
}


void effectQuarter(uint8_t columnNumber, uint32_t c) {
  for (int i=0 /*NUM_LEDS_PER_STRIP/4*/; i < NUM_LEDS_PER_STRIP; i++){
    uint16_t pixel = columnNumber*NUM_LEDS_PER_STRIP + i;
    setPixelColor(pixel, c);
  }
  effectShow();
}

void effectLines(uint32_t c, uint8_t numLines) {
  for(uint16_t i=0; i<NUM_LEDS_PER_STRIP; i++) {
    for(uint16_t j=0; j<NUM_STRIPS; j++) {
      uint16_t pixel = j*NUM_LEDS_PER_STRIP+i;
    
    if (i < numLines)
    {
      setPixelColor(pixel, c);
    }
    else
    {
      setPixelColor(pixel, strip.Color(0,0,0));
    }
  }
    
  }
  effectShow();
}



// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    setPixelColor(i, c);
    effectShow();
    delay(wait);
  }
}
//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        setPixelColor(i+q, c);    //turn every third pixel on
      }
      effectShow();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      effectShow();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    effectShow();
    delay(wait);
  }
}


int rainbowStatus = 0;

void effectRainbow()
{
  for (int i = 0; i < 360; i += 5)
  {
    rainbowStatus = i;
    effectRainbowSingle();
    //delay(1000);
  }
}


void effectRainbowSingle()
{
  for(int i=0; i<NUM_LEDS_PER_STRIP;i++)
  {
    effectRow(i,colorHue(rainbowStatus + (360/NUM_LEDS_PER_STRIP)*i));
  }
  rainbowStatus += 5;
  if (rainbowStatus > 360)
  {
    rainbowStatus = rainbowStatus % 360;
  }
}

void effectFlash(uint32_t color, int count)
{
  for (int i=0; i < count; i++)
  {
    solidColorQuick(color);
    delay(100);
    solidColorQuick(BLACK);
    delay(100);
  }
}

void effectBlink()
{
  uint32_t color = colorRGB(0,0,50);
  solidColorQuick(BLACK);
  for (int j=0;j<2;j++)
  {
    for (int i=0;i<NUM_LEDS_PER_STRIP;i++)
    {
      effectRow(i,color);
      delay(20);
      effectRow(i,BLACK);
    }
    for (int i=NUM_LEDS_PER_STRIP-1;i>=0;i--)
    {
      effectRow(i,color);
      delay(20);
      effectRow(i,BLACK);
    }
  }

}

