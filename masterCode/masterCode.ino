/*
 Tespo Chat Bot Project
 -- CODE FOR MASTER MEGA
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

#define LF          0x0A
#define SLAVE_ADDR 9
#define ANSWER_SIZE 32

char user_str[150];
int idx;
int incomingByte = 0;

// FUNCTIONS
void sendMessage( String , int  );
void requestMessage(int , int );

// ---------------------------- SETUP ----------------------------
void setup() {
  // Start the I2C Bus as Master
  Wire.begin();
  // Start Serial communication
  Serial.begin(9600);
  
  Serial.println("Say anything to get a random fact!");  
  idx = 0;

}
// ---------------------------- MAIN LOOP ----------------------------
void loop() {

// loop to get user input from serial monitor
    while (Serial.available() > 0) {
      user_str[idx] = Serial.read();
      if (user_str[idx] == LF) {
          user_str[idx] = 0;
          Serial.print("Master:\t");
          Serial.println(user_str);    
          //Serial.println(sendMessage(user_str,9));      
          while(sendMessage(user_str,SLAVE_ADDR) != 0){ // Error in transmitting message, needs to be resent
            Serial.println("  Error: Message not sent");
            delay(2000); // wait 2 seconds and try again
          }
          requestMessage(ANSWER_SIZE, SLAVE_ADDR);      
          idx = -1;
          }
      idx++;
    }
}

// ---------------------------- FUNCTIONS ----------------------------

int sendMessage( char message[], int address ){
  // function send message[] to specified address and returns error code
  // 0 - success, 1-4 error

      Wire.beginTransmission(address); // transmit to device at specified address
      Wire.write(message);              // sends message
      return(Wire.endTransmission());    // stop transmitting      
}

void requestMessage(int msgSize, int address){
      // Get message from slave
    Wire.requestFrom(address,msgSize);
    String response = "";
    while(Wire.available()){
      char b = Wire.read();
      response += b;
    }
    Serial.print("Slave:\t");
    Serial.println(response); 
}
