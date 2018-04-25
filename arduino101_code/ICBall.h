
#define ICBprint(text)  if (Serial) Serial.print(text)
#define ICBprintln(text)  if (Serial) Serial.println(text)

// standard colors
uint32_t colorRGB(int r, int g, int b);
uint32_t colorHSB(int hue, int sat, int val);

#define LED_POWER_SAVE_FACTOR  6

#define RED  colorRGB(255/LED_POWER_SAVE_FACTOR,0,0)
#define BLUE  colorRGB(0,0,255/LED_POWER_SAVE_FACTOR)
#define GREEN  colorRGB(0,255/LED_POWER_SAVE_FACTOR,0)
#define BLACK colorRGB(0,0,0)
#define WHITE colorRGB(255/LED_POWER_SAVE_FACTOR,255/LED_POWER_SAVE_FACTOR,255/LED_POWER_SAVE_FACTOR)
#define YELLOW colorRGB(255/LED_POWER_SAVE_FACTOR,255/LED_POWER_SAVE_FACTOR,0)
#define RAINBOW 0xffffffff

// color effects
void solidColor(uint32_t c, uint16_t duration);
void solidColorQuick(uint32_t c);
void effectFlash(uint32_t color, int count);
void effectInit();

// games
void gameColorfulPlay();
void gameBumpPlay();
void gameFirePlay();
void gameMovementDetectionPlay();
void gameSimonPlay();


// sound
#define ICBALL_BUZZER   11

#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131

