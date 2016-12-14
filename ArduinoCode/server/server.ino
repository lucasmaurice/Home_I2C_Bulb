//Bibliotheques de communication sans fil
#include <SPI.h>                    // Pour la communication via le port SPI
#include <Mirf.h>                   // Pour la gestion de la communication
#include <nRF24L01.h>               // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h>  // Pour la communication SPI

//Bibliotheque de communication avec le micro ordinateur Raspberry
#include <Wire.h>

//Definition des constantes PI
#define SIZE_MSG 5

//Definition des constante RF
//SET USERF TO FALSE IF YOU DONT NEED THAT
#define ADDR_RECEPT 01
#define USERF true
uint8_t addr_recep[5] = {'n','r','f','0'+(ADDR_RECEPT/10)%10,'0'+ADDR_RECEPT%10};

//KEY FOR USE I2C DATA
#define KEYRED 0
#define KEYGREEN 1
#define KEYBLUE 2
#define KEYRADIO 3
#define KEYBULB 4

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event

  if(USERF){
    Mirf.cePin = 7; // Broche CE sur D9
    Mirf.csnPin = 8; // Broche CSN sur D10
    Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
    Mirf.init(); // Initialise la bibliothèque

    Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
    Mirf.payload = 16; // Taille d'un message (maximum 32 octets)
    Mirf.config(); // Sauvegarde la configuration dans le module radio

    //Mirf.setTADDR(addr); // Adresse de transmission
    Mirf.setRADDR(addr_recep); // Adresse de réception
  }

  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  static uint8_t bMessage[SIZE_MSG];
  static uint8_t addr_emit[5]={'n','r','f','0','0'};

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

    //YOU NEED TO OVERWRITE THE FOLLOWING LINES:
    addr_emit[3]='0'+(bMessage[KEYRADIO]/10)%10;
    addr_emit[4]='0'+ bMessage[KEYRADIO]%10;
    while(Mirf.isSending());
    Mirf.setTADDR(addr_emit); // Adresse de transmission
    Mirf.send(bMessage);
    //STOP
  }
  delay(100);
}
