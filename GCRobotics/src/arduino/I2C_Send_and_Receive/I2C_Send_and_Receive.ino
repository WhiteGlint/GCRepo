#include <ArduinoHardware.h>
#include <ros.h>
#include <Wire.h>
#include <GCRobotics/Encoder_msg.h>
#include <GCRobotics/i2cData.h>
#include <std_msgs/UInt16.h>
#include <TimerOne.h>

void i2cCallback( const GCRobotics::i2cData& msg);
void gpioCallback( const std_msgs::UInt16& msg);
void Read();
int ReadOne(char address);

ros::NodeHandle n;

GCRobotics::Encoder_msg encoders;
std_msgs::UInt16 voltage;
ros::Publisher encoderPub("EncoderData", &encoders);
ros::Publisher diagPub("Diagnostic", &voltage);

ros::Subscriber<GCRobotics::i2cData> i2cSub("i2cSend", &i2cCallback );
ros::Subscriber<std_msgs::UInt16> gpioSub("gpio", &gpioCallback);

void setup(){
  Wire.begin(); // join i2c bus
  n.initNode();
  n.advertise(encoderPub);
  n.advertise(diagPub);
  n.subscribe(i2cSub);
  n.subscribe(gpioSub);

  pinMode(13, OUTPUT);
  DDRD = B11111111;
  //Timer1.initialize(200000); // 200 ms between inetrrupts
  //Timer1.attachInterrupt(Read);
}

void loop(){
  n.spinOnce();
 // voltage.data = analogRead(0);
/*
   Wire.beginTransmission(0x010>>1); // transmit to device "address"
  Wire.write(0);
  Wire.write(100);
  Wire.write(0);
  Wire.endTransmission();  
    digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  */
 // voltage.data = ReadOne(0x010>>1);
  //diagPub.publish(&voltage);
}

void i2cCallback( const GCRobotics::i2cData& msg)
{

  digitalWrite(13,HIGH);
  Wire.beginTransmission(msg.address>>1); // transmit to device "address"
  Wire.write(0);
  Wire.write(msg.messageData);
  Wire.write(msg.messageData2);
  Wire.endTransmission();  
  digitalWrite(13,LOW);
}

void gpioCallback( const std_msgs::UInt16& msg)
{
  PORTD = msg.data;
}

void Read() {
  digitalWrite(13,HIGH);
  int EC1, EC2, EC3, EC4; // these should probably be global
  //encoders.encoder1 = ReadOne (1); // these need to be the right address
  //encoders.encoder2 = ReadOne (2); // these need to be the right address
  //encoders.encoder3 = ReadOne (3); // these need to be the right address
  //encoders.encoder4 = ReadOne (4); // these need to be the right address
  //delay(5);
  encoderPub.publish(&encoders);

  digitalWrite(13,LOW);
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

