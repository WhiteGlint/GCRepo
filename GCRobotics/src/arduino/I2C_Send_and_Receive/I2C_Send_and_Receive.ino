
#include <ArduinoHardware.h>


#include <ros.h>
#include <Wire.h>
#include <GCRobotics/Encoder_msg.h>
#include <GCRobotics/i2cData.h>
#include <std_msgs/String.h>

#include <TimerOne.h>

ros::NodeHandle n;
//std_msgs::String encoders;
GCRobotics::Encoder_msg encoders;
ros::Publisher pub("EncoderData", &encoders);

void setup(){
  Wire.begin(); // join i2c bus
  Timer1.initialize(10000); // 10 ms between inetrrupts
  Timer1.attachInterrupt(Read);
}

void WriteOne(char address, char velocity, char dir) {
  Wire.beginTransmission(address); // transmit to device "address"
  Wire.write(velocity);            // sends velocity
  Wire.write(dir);                 // sends direction
  Wire.endTransmission();          // stop transmitting
}

void Read() {
  int EC1, EC2, EC3, EC4; // these should probably be global
  encoders.encoder1 = ReadOne (1); // these need to be the right address
  encoders.encoder2 = ReadOne (2); // these need to be the right address
  encoders.encoder3 = ReadOne (3); // these need to be the right address
  encoders.encoder4 = ReadOne (4); // these need to be the right address
  
  //pub.publish(&encoders);
}

int ReadOne(char address) { // pass in the motor you want to read
  int encoderCount = 0;
  Wire.requestFrom(address, 2);    // request 6 bytes from slave device #2

  while(Wire.available())   // slave may send less than requested
  { 
    char c = Wire.read();   // receive a byte as character
    encoderCount<<8;        // shifts lower byte to upper byte
    encoderCount += c;      //adds in the new lower byte
  }
  
  return encoderCount;
}

void loop(){
  // get input from Comp via USB
  //Write(address, velocity, dir);
}
