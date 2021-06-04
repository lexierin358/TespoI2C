/*
 Tespo Chat Bot Project
 -- CODE FOR SLAVE UNO
 -- uses I2C to communicate between mega and uno
 
 The circuit: 
 * Uno Ground -> Mega Ground
 * Uno SDA (A4) -> Mega SDA (20)
 * Uno SCL (A5) -> Mega SCL (21)
 
 Created: June 2 2021
 Modified: June 3 2021
 by Lexi Adams
 */

#include <Wire.h>
#include <string.h>

#define ANSWER_SIZE 32 //size of request message
#define LF    0x0A

long randNumber;
String userInput = "";
int idx;
int numFacts = 10;
String answers[] = { "Halley's commet will come in 2062", "Saturn has 62 moons",
                     "Octopuses have three hearts", "Boring Test Tunnel is 4,475 feet",
                     "Tespo is a awesome! ", "First computer virus: 1983",
                     "First computer game: 1961", "Weiner dogs are the best!",
                     "Lexi is a twin", "The moon has moonquakes"};

// FUNCTIONS
void receiveEvent(int bytes);
void requestEvent();

// ---------------------------- SETUP ----------------------------
void setup() {
  
  // Start Serial communication
  Serial.begin(9600);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9);
  // Attach a function to trigger when something is received
  Wire.onReceive(receiveEvent);
  // Attach a function to trigger when message is requested
  Wire.onRequest(requestEvent);

  randomSeed(analogRead(0)); // Creat random seed using Analog noise 
}

// ---------------------------- MAIN LOOP ----------------------------
void loop() {
  
}

// ---------------------------- FUNCTIONS ----------------------------

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int bytes)
{  
  while(0 < Wire.available()) // loop through all 
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
    userInput += c;     // store message into userInput string
  }
  Serial.println();
  delay(1000);

}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void requestEvent() {
 
  // Setup byte variable in the correct size
  byte response[ANSWER_SIZE];
  randNumber = random(numFacts);
    
  // Format answer as array
  for (byte i=0;i<ANSWER_SIZE;i++) {
    response[i] = (byte)answers[randNumber].charAt(i);
  } 
  
  Wire.write(response,sizeof(response)); // Send response back to Master
  Serial.println("Request event");     // Print to Serial Monitor
}
