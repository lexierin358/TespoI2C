# TespoI2C
I2C communication between Arduino Uno and Mega

This project gives a scalable example of how to send and recive messages using I2C communication.

# Hardware Required
- Arduino Uno
- Arduino Mega
- 3 Jumper Wires
- USB Cable

# Circuit Setup
 * Uno Ground -> Mega Ground
 * Uno SDA (A4) -> Mega SDA (20)
 * Uno SCL (A5) -> Mega SCL (21)
 ![HardwareSetup1_schem](https://user-images.githubusercontent.com/27176759/120734375-c39efa80-c4b6-11eb-890b-d52ad4e0a9a3.png)


# Uploading Code
In this project the Arduino Mega acts at the Master Device, so upload masterCode to the Mega.
The Arduino Uno is the slave device, upload slaveCode to it.

Once the code is uploaded to both arduinos, open the Serial monitor on the Mega and you are good to go!

# Other Resources
Arduino Wire Library: https://www.arduino.cc/en/reference/wire

I2C Basics: https://www.circuitbasics.com/basics-of-the-i2c-communication-protocol/
