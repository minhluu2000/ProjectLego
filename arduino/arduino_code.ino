/* This code is a modified version of André Balboa's RFID library for MFRC522 sensor.
 */


/* Follow the pin diagram below for your specific board
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>

#define LIGHT_PIN       2          // Optional, activity light
#define SOUND_PIN       8          // Sound sensor
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

int counter = 0;
boolean clientOpen = false;

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
  pinMode(SOUND_PIN, INPUT);
  pinMode(LIGHT_PIN, OUTPUT);
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
}

// Since activity light is optional, a lot of the code below can be removed

void loop() {
  
  if (digitalRead(SOUND_PIN) && counter < 3) {
    digitalWrite(LIGHT_PIN, HIGH); 
    delay(100);
    digitalWrite(LIGHT_PIN, LOW);
    counter += 1;
  }
  
  if (counter == 3) {
    if (!clientOpen) {
      clientOpen = true;
      digitalWrite(LIGHT_PIN, HIGH); 
      Serial.println("Open client");
      Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
    }
    
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
    
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }
    
    // Dump debug info about the card; PICC_HaltA() is automatically called
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
    counter = 0;
    clientOpen = false;
    digitalWrite(LIGHT_PIN, LOW);
  }
}
