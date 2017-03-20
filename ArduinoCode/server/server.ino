//Bibliotheques de communication sans fil
#include <SPI.h>                    // Pour la communication via le port SPI

//Bibliotheque de communication avec le micro ordinateur Raspberry
#include <Wire.h>

//Definition des constantes PI
#define SIZE_MSG 5

//KEY FOR USE I2C DATA
#define KEYRED 0
#define KEYGREEN 1
#define KEYBLUE 2
#define KEYRADIO 3
#define KEYBULB 4

//PIN NUMBER FOR BULB 1
#define REDPIN 9
#define GREENPIN 10
#define BLUEPIN 11

int iNewRed = 0;
int iNewGreen = 0;
int iNewBlue = 0;
  
void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}

void loop() {
  static int iRed = 0;
  static int iGreen = 0;
  static int iBlue = 0;

  if(iRed < iNewRed - 2){
    iRed += 3;
    analogWrite(REDPIN, iRed);
  }else if(iRed > iNewRed + 2){
    iRed -= 3;
    analogWrite(REDPIN, iRed);
  }
  
  if(iGreen < iNewGreen - 2){
    iGreen += 3;
    analogWrite(GREENPIN, iGreen);
  }else if(iGreen > iNewGreen + 2){
    iGreen -= 3;
    analogWrite(GREENPIN, iGreen);
  }
  
  if(iBlue < iNewBlue - 2){
    iBlue += 3;
    analogWrite(BLUEPIN, iBlue);
  }else if(iBlue > iNewBlue + 2){
    iBlue -= 3;
    analogWrite(BLUEPIN, iBlue);
  }
  delay(30);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  static uint8_t bMessage[SIZE_MSG];


  if(howMany>=SIZE_MSG){
    for(int iLoop=0; iLoop<SIZE_MSG; iLoop++){
       bMessage[iLoop]=Wire.read();
    }
    //ENTER HERE WHAT TO DO ON I2C DATA RECEPTION:
    //USE THE FOLLOWING KEY TO USE DATA:
    //bMessage[KEY]
    //KEYBULB : ID of the bulb
    //KEYRED - KEYGREEN - KEYBLUE : intensity of the different colors
    //KEYRADIO : used for RF module only, Adress of the receiving rf module
    if(bMessage[KEYBULB]==1){
      iNewRed = bMessage[KEYRED];
      iNewGreen = bMessage[KEYGREEN];
      iNewBlue = bMessage[KEYBLUE];
    }
  }
  delay(100);
}
