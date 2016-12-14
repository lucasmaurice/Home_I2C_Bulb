/**
 * Exemple de code pour la bibliothèque Mirf – Client Ping Pong
 */
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

#define SIZE_MSG 5

#define LEDBULB1 3
#define LEDBULB2 5

#define KEYRED 0
#define KEYGREEN 1
#define KEYBLUE 2
#define KEYRADIO 3
#define KEYBULB 4

void setup() {
  Serial.begin(9600);

  Mirf.cePin = 7; // Broche CE sur D9
  Mirf.csnPin = 8; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothèque

  Mirf.channel = 1; // Choix du canal de communication (128 canaux disponibles, de 0 à 127)
  Mirf.payload = 16; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) "nrf01"); // Adresse de transmission
  Mirf.setRADDR((byte *) "nrf02"); // Adresse de réception

  pinMode(LEDBULB1, OUTPUT);
  analogWrite(LEDBULB1, 0);

  pinMode(LEDBULB2, OUTPUT);
  analogWrite(LEDBULB2, 0);

  Serial.println("Go !");
}

void loop() {
  byte bMessage[16];
  int iPower;
  if(Mirf.dataReady()){
    Serial.println("reception");
    Mirf.getData(bMessage);
    if(bMessage[KEYBULB]==1){
      iPower = (bMessage[KEYRED] + bMessage[KEYGREEN] + bMessage[KEYBLUE])/3;
      Serial.print("bulb 1 : ");
      Serial.println(iPower*100/255);
      analogWrite(LEDBULB1, iPower);
    }else if(bMessage[KEYBULB]==2){
      iPower = (bMessage[KEYRED] + bMessage[KEYGREEN] + bMessage[KEYBLUE])/3;
      Serial.print("bulb 2 : ");
      Serial.println(iPower*100/255);
      analogWrite(LEDBULB2, iPower);
    }
  }
}
