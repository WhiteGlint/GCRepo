
/*

		NAME 	 - Arduino Control Bridge 
		DESIGN - Josh Galicic
		PRIORITY - Required - Neccessary for communicating between PC and Pics.
	
\
*/

#define Front_Left   0x08
#define Front_Right  0x02
#define Back_Right   0x04
#define Back_Left    0x06


#define Forward      0x00
#define Backward     0x01

#define SlowSpeed    30
#define MediumSpeed  50
#define FastSpeed    70
#define Stop         00

#include <ArduinoHardware.h>
#include <Wire.h>
#include <TimerOne.h>

int ReadOne(char address);

int SerialInput = 0;    // This variable is used to stored the value of the keyboard button that was press
                                    // if SerialInput = 119 , W , that mean go forward
                                    // if SerialInput = 115 , S , that mean go backward
                                    // if SerialInput = 97  , A , that mean strafe left
                                    // if SerialInput = 100 , D , that mean strafe right
                                    // if SerialInput = 113 , Q , that mean left diagonal forward
                                    // if SerialInput = 101 , E , that mean right diagonal forward
                                    // if SerialInput = 114 , R , that mean rotate left
                                    // if SerialInput = 116 , T , that mean rotate right
                                    // if SerialInput = 120 , X , that mean STOP!!
                                    // if SerialInput = 49  , 1 , that mean SlowSpeed
                                    // if SerialInput = 50  , 2 , that mean MediumSpeed
                                    // if SerialInput = 51  , 3 , that mean FastSpeed
                                    // if SerialInput = 99  , C , that mean RECORD ODEMETRY
                                    
int RobotSpeed = MediumSpeed;
int COUNTS = 0;         // This will contain the number of counts per loop. NOT the total distance
int i2cDirection = 0, i2cSpeed = 0;   // for incoming serial data
int ODOM1 = 0, ODOM2 = 0, ODOM3 = 0, ODOM4 = 0;

void setup(){
  Wire.begin(); // join i2c bus
  Serial.begin(4800);
  pinMode(13, OUTPUT);
}

void loop()
{
      i2cWrite(Front_Left,   RobotSpeed,   Forward  );
      i2cWrite(Front_Right,  RobotSpeed,   Forward  );
      i2cWrite(Back_Left,    RobotSpeed,   Forward  );
      i2cWrite(Back_Right,   RobotSpeed,   Forward  );
      delay(1000);
 
}

void i2cWrite ( char Address, char Speed , char Direction)
{
    Wire.beginTransmission(Address >> 1 );
    Wire.write((byte)0);
    Wire.write((byte)Speed);
    Wire.write((byte)Direction);
    Wire.endTransmission();
}

int ReadOne(char address) {                               // pass in the motor you want to read
  unsigned int encoder[2] = {0,0};
  int encoderCountTotal = 0;
  Wire.requestFrom(address >>1 , 2);    // request 2 bytes from address
   int i = 0;
  while(Wire.available())   // slave may send less than requested
  { 
    encoder[i] = Wire.read();   // receive a byte as character
    i++;
  }
  
  encoder[1] = encoder[1] << 8; // Combine the two bytes into one value, lower byte is sent first, upper second.
  
  return encoder[1] + encoder[0];
}


