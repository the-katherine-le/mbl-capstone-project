#include <UTFT.h>
#include <URTouch.h>

//Model Parameters//
UTFT myGLCD(ILI9486, 38, 39, 40, 41);
URTouch  myTouch( 6, 5, 4, 3, 2);

//Declare Fonts//
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

int x,y; //coordinate variables
int currentPage; //current page

//Define the x,y coordinates of the elements on HOME SCREEN//

int statusMsgX1 = 10; //start corner
int statusMsgY1 = 10;
int statusMsgX2 = 470; //end corner
int statusMsgY2 = 30;

int runButtonX1 = 10; //start corner
int runButtonY1 = 40;
int runButtonX2 = 150; //end corner
int runButtonY2 = 240;

int pauseButtonX1 = 170;
int pauseButtonY1 = 40;
int pauseButtonX2 = 310;
int pauseButtonY2 = 240;

int resetButtonX1 = 330;
int resetButtonY1 = 40;
int resetButtonX2 = 470;
int resetButtonY2 = 240;

int connectButtonX1 = 10;
int connectButtonY1 = 250;
int connectButtonX2 = 230;
int connectButtonY2 = 310;

int setupButtonX1 = 250;
int setupButtonY1 = 250;
int setupButtonX2 = 470;
int setupButtonY2 = 310;

//Define the x,y coordinates of the buttons on SETUP SCREEN//

//Declare Variables Related to the Motor here//

void setup() {
  ////Set up LCD////
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  ////Draw the GUI on the screen////
  drawHomeScreen();
  // 0 for home screen, 1 for setup screen
  currentPage = 0;

  ////Define Pin Modes////
  //pinMode()
}
//Our main loop here//
void loop() {
  //We are on the home page
  if (currentPage == 0) {
    if (myTouch.dataAvailable()) {
      myTouch.read();
      //Get the coordinates of where the screen has been pressed
      x = myTouch.getX(); // X coordinate
      y = myTouch.getY(); // Y coordinate

      //If we press the Run Button
      if ((x >= runButtonX1) && (y >= runButtonY1) && (x <= runButtonX2) && (y <= runButtonY2)) {
        //Highlight the button to indicate we've pressed RUN
        highlightFrame(runButtonX1, runButtonY1, runButtonX2, runButtonY2);
        currentPage = 0; //We are on the home page still
        myGLCD.clrScr();
        updateStatus("RUNNING MOTOR",0,0,0);
        //Motor run function here
      }
      //If we press the Pause Button
      if ((x >= pauseButtonX1) && (y >= pauseButtonY1) && (x <= pauseButtonX2) && (y <= pauseButtonY2)) {
        //Highlight the button to indicate we've pressed PAUSE
        highlightFrame(pauseButtonX1, pauseButtonY1, pauseButtonX2, pauseButtonY2);
        currentPage = 0; //We are on the home page still
        myGLCD.clrScr();
        updateStatus("MOTOR PAUSED",1,1,1);
        //Motor pause function here
      }
      //If we press the Reset Button
      if ((x >= resetButtonX1) && (y >= resetButtonY1) && (x <= resetButtonX2) && (y <= resetButtonY2)) {
        //Highlight the button to indicate we've pressed RESET
        highlightFrame(resetButtonX1, resetButtonY1, resetButtonX2, resetButtonY2);
        currentPage = 0; //We are on the home page still
        myGLCD.clrScr();
        updateStatus("RESETTING",2,2,2);
        //Motor reset function here
      }
      //If we press the Connect to Controller Button
      if ((x >= connectButtonX1) && (y >= connectButtonY1) && (x <= connectButtonX2) && (y <= connectButtonY2)) {
        //Highlight the button to indicate we've pressed CONNECT TO CONTROLLER
        highlightFrame(connectButtonX1, connectButtonY1, connectButtonX2, connectButtonY2);
        currentPage = 0; //We are on the home page still
        myGLCD.clrScr();
        updateStatus("CONNECTING...",3,3,3);
        //Connect to controller button here
      }
      //If we press the Setup Button
      if ((x >= setupButtonX1) && (y >= setupButtonY1) && (x <= setupButtonX2) && (y <= setupButtonY2)) {
        //Highlight the button to indicate we've pressed SETUP
        highlightFrame(setupButtonX1, setupButtonY1, setupButtonX2, setupButtonY2);
        currentPage = 1; //We are now on the setup page
        myGLCD.clrScr();
        updateStatus("CHANGE SETUP",4,4,4);
        drawSetupScreen();
      }
    }
  }
}

//SETUP THE HOME SCREEN//
void drawHomeScreen() {
  
  //Status message//
  myGLCD.setColor(185, 224, 165); // Sets green color
  myGLCD.fillRoundRect (statusMsgX1, statusMsgY1, statusMsgX2, statusMsgY2); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.drawRoundRect (statusMsgX1, statusMsgY1, statusMsgX2, statusMsgY2); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(16, 167, 103); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("CHOOSE OPTION...", CENTER, 102); // Prints the string
  
  //Run Button//
  myGLCD.setColor(185, 224, 165); // Sets green color
  myGLCD.fillRoundRect (runButtonX1, runButtonY1, runButtonX2, runButtonY2); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.drawRoundRect (runButtonX1, runButtonY1, runButtonX2, runButtonY2); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(16, 167, 103); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("RUN", CENTER, 102); // Prints the string

  //Pause Button//
  myGLCD.setColor(185, 224, 165); // Sets green color
  myGLCD.fillRoundRect (pauseButtonX1, pauseButtonY1, pauseButtonX2, pauseButtonY2); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.drawRoundRect (pauseButtonX1, pauseButtonY1, pauseButtonX2, pauseButtonY2); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(16, 167, 103); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("PAUSE", CENTER, 102); // Prints the string

  //Reset Button//
  myGLCD.setColor(185, 224, 165); // Sets green color
  myGLCD.fillRoundRect (resetButtonX1, resetButtonY1, resetButtonX2, resetButtonY2); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.drawRoundRect (resetButtonX1, resetButtonY1, resetButtonX2, resetButtonY2); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(16, 167, 103); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("REST", CENTER, 102); // Prints the string

  //Connect to Controller Button//
  myGLCD.setColor(185, 224, 165); // Sets green color
  myGLCD.fillRoundRect (connectButtonX1, connectButtonY1, connectButtonX2, connectButtonY2); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.drawRoundRect (connectButtonX1, connectButtonY1, connectButtonX2, connectButtonY2); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(16, 167, 103); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("CONNECT TO CONTROLLER", CENTER, 102); // Prints the string

  //Setup Button//
  myGLCD.setColor(185, 224, 165); // Sets green color
  myGLCD.fillRoundRect (setupButtonX1, setupButtonY1, setupButtonX2, setupButtonY2); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.drawRoundRect (setupButtonX1, setupButtonY1, setupButtonX2, setupButtonY2); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(16, 167, 103); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print("SETUP", CENTER, 102); // Prints the string

}

//SETUP MENU//
void drawSetupScreen() {
  //
}
//Highlights the button when it is pressed//
void highlightFrame(int x1, int y1, int x2, int y2) { 
  myGLCD.setColor(255, 0, 0); //Highlights it in red
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable()) {
    myTouch.read();
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (x1, y1, x2, y2);
  }
}
//Updates the status strip with appropriate color and message//
void updateStatus(String message, int rgb1, int rgb2, int rgb3) { 
  myGLCD.setColor(rgb1, rgb2, rgb3); // 
  myGLCD.fillRoundRect (statusMsgX1, statusMsgY1, statusMsgX2, statusMsgY2); // Draws filled rounded rectangle
  myGLCD.setColor(255, 255, 255); // Sets color to white
  myGLCD.drawRoundRect (statusMsgX1, statusMsgY1, statusMsgX2, statusMsgY2); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD.setFont(BigFont); // Sets the font to big
  myGLCD.setBackColor(16, 167, 103); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD.print(message, CENTER, 102); // Prints the string
}
