



extern Adafruit_NeoPixel strip;

uint32_t colorRGB(int r, int g, int b)
{
  return strip.Color(r,g,b);
}

//http://www.kasperkamperman.com/blog/arduino/arduino-programming-hsb-to-rgb/


uint32_t colorHSB(int hue, int sat, int val) { 
  /* convert hue, saturation and brightness ( HSB/HSV ) to RGB
     The dim_curve is used only on brightness/value and on saturation (inverted).
     This looks the most natural.      
  */
 
  //val = 255;//dim_curve[val];
  //sat = 255-(255-sat);
 
  int r = 0;
  int g = 0;
  int b = 0;
  int base;
 
  if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
    r=val;
    g=val;
    b=val;  
  } else  { 
 
    base = ((255 - sat) * val)>>8;
 
    switch(hue/60) {
  case 0:
    r = val;
    g = (((val-base)*hue)/60)+base;
    b = base;
  break;
 
  case 1:
    r = (((val-base)*(60-(hue%60)))/60)+base;
    g = val;
    b = base;
  break;
 
  case 2:
    r = base;
    g = val;
    b = (((val-base)*(hue%60))/60)+base;
  break;
 
  case 3:
    r = base;
    g = (((val-base)*(60-(hue%60)))/60)+base;
    b = val;
  break;
 
  case 4:
    r = (((val-base)*(hue%60))/60)+base;
    g = base;
    b = val;
  break;
 
  case 5:
    r = val;
    g = base;
    b = (((val-base)*(60-(hue%60)))/60)+base;
  break;
    }
  }   
  return strip.Color(r,g,b);
}

uint32_t colorHue(int hue)
{ 
  if (hue>360)
  {
    hue = hue % 360;
  }
  return colorHSB(hue, 255, 255/LED_POWER_SAVE_FACTOR); 
}

uint32_t colorRandom()
{
  return colorHSB(random(360),255,255/LED_POWER_SAVE_FACTOR);
}

