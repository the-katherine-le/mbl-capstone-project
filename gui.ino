#if 1

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#define MINPRESSURE 200
#define MAXPRESSURE 1000

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP = 8, XM = A2, YP = A3, YM = 9; //320x480 ID=0x9487
const int TS_LEFT = 194, TS_RT = 937, TS_TOP = 963, TS_BOT = 200;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button run_btn, pause_btn, reset_btn, setup_btn;
Adafruit_GFX_Button flow_inc_btn, flow_dec_btn, carriage_inc_btn, carriage_dec_btn, return_home_btn;

bool buttonPress = true;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);   //because TFT control pins
  digitalWrite(XM, HIGH);
  bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
  if (pressed) {
    pixel_x = map(p.y, TS_TOP, TS_BOT, 0, tft.width()); //.kbv makes sense to me
    pixel_y = map(p.x, TS_RT, TS_LEFT, 0, tft.height());
  }
  return pressed;
}

//ADAFRUIT DEFAULT
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//https://flatuicolors.com/palette/nl
//Convert to proper hex: http://www.rinkydinkelectronics.com/calc_rgb565.php
//ORANGE-YELLOW-REDS
#define SUNFLOWER 0xFE02
#define RADIANT_YELLOW 0xF4E3
#define PUFFINS_BILL 0xEAC4
#define RED_PIGMENT 0xE904

//GREENS
#define ENERGOS 0xC727
#define ANDROID_GREEN 0xA647
#define PIXELATED_GRASS 0x04A6
#define TURKISH_AQUA 0x030C

//BLUES
#define BLUE_MARTINA 0x1658
#define MEDITERRANEAN_SEA 0x1454
#define MERCHANT_MARINE_BLUE 0x029B
#define K_LEAGUES_UNDER_THE_SEA 0x18AC

//PINKS-PURPLES
#define LAVENDER_ROSE 0xFD3B
#define LAVENDER_TEA 0xDC1F
#define FORGOTTEN_PURPLE 0x9C1F
#define CIRCUMORBITAL_RING 0x52D7

//REDS-MAGENTA
#define BARA 0xEA6C
#define VERY_BERRY 0xB1AE
#define HOLLY 0x81AE
#define MAGENTA_PURPLE 0x68EA

//FUNCTION DECLARATIONS
bool initHomeScreen(void);
bool initSetupScreen(void);
void drawHomeScreen(void);
void drawSetupScreen(void);

//Screen setup
int state = 0; //0 for home screen, 1 for setup screen
bool drawHome = false; //initial setup
bool drawSetup = false; //inital setup

void setup(void)
{
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  Serial.println("Calibrate for your Touch Panel");
  if (ID == 0xD3D3) ID = 0x9486; // write-only shield
  tft.begin(ID);
  tft.setRotation(1);            //LANDSCAPE
  tft.fillScreen(BLACK);
}

void loop(void)
{
    if (state == 0) { //HOME SCREEN
      if (drawHome == false) {
        drawHome = initHomeScreen();
      }
      else {
        drawHomeScreen();
      }
    }
  if (state == 1) { //SETUP SCREEN
    if (drawSetup == false) {
      drawSetup = initSetupScreen();
    }
    else {
      drawSetupScreen();
    }
  }
}

bool initHomeScreen(void) {
  //http://adafruit.github.io/Adafruit-GFX-Library/html/class_adafruit___g_f_x___button.html#a0cb6999a324b9999a1f4b610e36b16b6
  //Adafruit_GFX_Button::initButton(gfx,x,y,w,h,outline,fill,textcolor,label,textsize)
  //x: x-coordinate of button center; y: y-coordinate of button center; w: width; h: height

  run_btn.initButton(&tft,  85, 155, 140, 170, WHITE, ENERGOS, BLACK, "RUN", 3);
  pause_btn.initButton(&tft, 240, 155, 140, 170, WHITE, RADIANT_YELLOW, BLACK, "PAUSE", 3);
  reset_btn.initButton(&tft, 395 155, 140, 170, WHITE, BLUE_MARTINA, BLACK, "RESET", 3);
  setup_btn.initButton(&tft, 240, 285, 460, 60, WHITE, BARA, BLACK, "SETUP", 3);

  //  run_btn_pressed.initButton(&tft,  75, 150, 140, 180, WHITE, ANDROID_GREEN, BLACK, "RUN", 2);
  //  pause_btn_pressed.initButton(&tft, 240, 150, 140, 180, WHITE, PUFFINS_BILL, BLACK, "PAUSE", 2);
  //  reset_btn_pressed.initButton(&tft,  400, 150, 140, 180, WHITE, MEDITERRANEAN_SEA, BLACK, "RESET", 2);
  //  setup_btn_pressed.initButton(&tft, 240, 280, 460, 60, WHITE, VERY_BERRY, BLACK, "SETUP", 2);

  run_btn.drawButton(false);
  pause_btn.drawButton(false);
  reset_btn.drawButton(false);
  setup_btn.drawButton(false);

  //  run_btn_pressed.drawButton(false);
  //  pause_btn_pressed.drawButton(false);
  //  reset_btn_pressed.drawButton(false);
  //  setup_btn_pressed.drawButton(false);

  //DRAW GRAPHICS
  tft.drawRect(0,0,480,320,WHITE);//menu frame
  tft.drawRect(10,65,150,175,WHITE);//frame for run button
  tft.drawRect(165,65,150,175,WHITE);//frame for pause button
  tft.drawRect(320,65,150,175,WHITE);//frame for reset button
  tft.drawRect(0,250,480,70,WHITE);//frame for setup button

  //STATUS MESSAGE STRIP
  //void fillRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color);
  //[x0, y0] coordinates of top left corner of rectangle; [w,h]: width and height of rectangle
  tft.fillRect(0, 0, 480, 20, WHITE);
  tft.setCursor(220, 5);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setTextWrap(true);
  tft.println("HOME");

  //STATUS
  tft.drawRect(5,250,480,70,WHITE);//frame for setup button
  
  return true;
}

bool initSetupScreen(void) {
  //Pump flow rate, //print carriage speed
  flow_inc_btn.initButton(&tft,  70, 195, 90, 60, WHITE, ENERGOS, BLACK, "+", 4);
  flow_dec_btn.initButton(&tft, 170, 195, 90, 60, WHITE, RADIANT_YELLOW, BLACK, "-", 4);
  carriage_inc_btn.initButton(&tft,  310, 195, 90, 60, WHITE, ENERGOS, BLACK, "+", 4);
  carriage_dec_btn.initButton(&tft, 410, 195, 90, 60, WHITE, RADIANT_YELLOW, BLACK, "-", 4);
  return_home_btn.initButton(&tft,  240, 280, 200, 60, WHITE, BLUE_MARTINA, BLACK, "HOME", 2);

  flow_inc_btn.drawButton(false);
  flow_dec_btn.drawButton(false);
  carriage_inc_btn.drawButton(false);
  carriage_dec_btn.drawButton(false);
  return_home_btn.drawButton(false);

  //SETUP SCREEN GRAPHICS
  tft.fillRect(0,0,480,25,WHITE);
  tft.setCursor(210,5);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setTextWrap(true);
  tft.println("SETUP");

  //BORDER FOR PAGE
  tft.drawRect(5,20,470,300,WHITE);
  
  //FLOW RATE GRAPHICS
  tft.drawRect(15,45,210,195,WHITE);//frame
  tft.setCursor(20, 50);
  tft.setTextColor(WHITE,BLACK);
  tft.setTextSize(2);
  tft.setTextWrap(true);
  tft.println("FLOW RATE uL/s");
  tft.drawRect(20,160,200,70,WHITE);//frame for button

  //FLOW RATE TEXT BOX
  tft.fillRect(20,80,200,80, WHITE);
  tft.setCursor(20, 90);
  tft.setTextColor(BLACK);
  tft.setTextSize(5);
  tft.setTextWrap(true);
  //INSERT FUNCTION HERE TO UPDATE THE TEXT EVERY TIME IT IS INC/DEC
  tft.println("0.00");

  //CARRIAGE SPEED GRAPHICS
  tft.drawRect(255,45,210,195,WHITE);//Big frame
  tft.setCursor(260, 50);
  tft.setTextColor(WHITE,BLACK);
  tft.setTextSize(2);
  tft.setTextWrap(true);
  tft.println("CARRIAGE SPD mm/s");
  tft.drawRect(260,160,200,70,WHITE);//frame for button

  //CARRIAGE SPEED TEXT BOX
  tft.fillRect(260, 80, 200, 80, WHITE);
  tft.setCursor(260, 90);
  tft.setTextColor(BLACK);
  tft.setTextSize(5);
  tft.setTextWrap(true);
  //INSERT FUNCTION HERE TO UPDATE THE TEXT EVERY TIME IT IS INC/DEC
  tft.println("0.00");

  return true;
}

void drawHomeScreen(void) {

  bool down = Touch_getXY();
  buttonPress = true;
  //CHECK TO SEE IF ANY OF THE BUTTONS HAVE BEEN PRESSED
  run_btn.press(down && run_btn.contains(pixel_x, pixel_y));
  pause_btn.press(down && pause_btn.contains(pixel_x, pixel_y));
  reset_btn.press(down && reset_btn.contains(pixel_x, pixel_y));
  setup_btn.press(down && setup_btn.contains(pixel_x, pixel_y));

  //CONFIGURING BUTTONS
  if (run_btn.justReleased())
    run_btn.drawButton();
  if (pause_btn.justReleased())
    pause_btn.drawButton();
  if (reset_btn.justReleased())
    reset_btn.drawButton();
  if (setup_btn.justReleased())
    setup_btn.drawButton();

  //IF ANY OF THE BUTTONS ARE PRESSED
  //CHANGE THE STATUS MESSAGE
  if (run_btn.justPressed()) {
    run_btn.drawButton(true);
    //UPDATE STATUS MESSAGE STRIP
    //void fillRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color);
    //[x0, y0] coordinates of top left corner of rectangle; [w,h]: width and height of rectangle
    tft.fillRect(10, 10, 460, 30, ANDROID_GREEN);
    tft.setCursor(10, 15);
    tft.setTextColor(BLACK);
    tft.setTextSize(3);
    tft.setTextWrap(true);
    tft.println("RUNNING...");
  }
  if (pause_btn.justPressed()) {
    pause_btn.drawButton(true);
    tft.fillRect(10, 10, 460, 30, PUFFINS_BILL);
    tft.setCursor(10, 10);
    tft.setTextColor(BLACK, WHITE);
    tft.setTextSize(3);
    tft.setTextWrap(true);
    tft.println("PAUSED");
  }
  if (reset_btn.justPressed()) {
    reset_btn.drawButton(true);
    tft.fillRect(10, 10, 460, 30, MEDITERRANEAN_SEA);
    tft.setCursor(10, 10);
    tft.setTextColor(BLACK, WHITE);
    tft.setTextSize(3);
    tft.setTextWrap(true);
    tft.println("RESETTING");
    //Function here to zero the pump...
  }
  if (setup_btn.justPressed()) {
    setup_btn.drawButton(true);
    //CALL SETUP MENU FUNCTION HERE
    tft.fillRect(10, 10, 460, 30, MAGENTA_PURPLE);
    tft.setCursor(10, 10);
    tft.setTextColor(BLACK, WHITE);
    tft.setTextSize(3);
    tft.setTextWrap(true);
    tft.println("CONFIGURE SETUP");
  }

}

void drawSetupScreen(void) {
  bool down = Touch_getXY();
  //CHECK TO SEE IF ANY OF THE BUTTONS HAVE BEEN PRESSED
  flow_inc_btn.press(down && flow_inc_btn.contains(pixel_x, pixel_y));
  flow_dec_btn.press(down && flow_dec_btn.contains(pixel_x, pixel_y));
  carriage_inc_btn.press(down && carriage_inc_btn.contains(pixel_x, pixel_y));
  carriage_dec_btn.press(down && carriage_dec_btn.contains(pixel_x, pixel_y));
  return_home_btn.press(down && return_home_btn.contains(pixel_x, pixel_y));
}
void updateStatusMsg(void) {

}

#endif
