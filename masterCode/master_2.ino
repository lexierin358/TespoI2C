// Include the required Wire library for I2C<br>#include 

// MASTER CODE -> MEGA
#include <Wire.h>
#include <string.h>

#define LF          0x0A 

char user_str[150]; 
int idx; 




int x = 0;
int incomingByte = 0;
bool firstLoop = true;
String userInput = "";

void sendMessage( String , int  );

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Hellow Stink butts!");
  // Start the I2C Bus as Master
  idx = 0;


  Wire.beginTransmission(9); // transmit to device #9
  Wire.write("Hello World");              // sends x 
  Wire.endTransmission();    // stop transmitting    

  
}

void loop() {

    while (Serial.available() > 0) {
    user_str[idx] = Serial.read();
    if (user_str[idx] == LF) {
        //Serial.print("Received new angle: ");
        user_str[idx] = 0;
        Serial.println(user_str);
 
        sendMessage( user_str, 9 );      
        
        idx = -1;
        }
    idx++;
    }



}

void sendMessage( char message[], int address ){

      Wire.beginTransmission(address); // transmit to device at specified address
      Wire.write(message);              // sends message
      //Wire.write(address);
      Wire.endTransmission();    // stop transmitting    
  
}
