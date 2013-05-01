#include <ArduinoHardware.h>
#include <ros.h>
#include <Wire.h>
#include <GCRobotics/Encoder_msg.h>
#include <GCRobotics/i2cData.h>
#include <std_msgs/Float32.h>
#include <std_msgs/UInt16.h>
#include <TimerOne.h>

void i2cCallback( const GCRobotics::i2cData& msg);
void gpioCallback( const std_msgs::UInt16& msg);
void Read();
int ReadOne(char address);

ros::NodeHandle n;

//Message data variables
GCRobotics::Encoder_msg encoders;
std_msgs::Float32 voltage;
std_msgs::UInt16 errorCode;
//pubs
ros::Publisher encoderPub("EncoderData", &encoders);
ros::Publisher diagPub("BatteryVoltage", &voltage);
ros::Publisher errorPub("ArduinoError", &errorCode);
// subs
ros::Subscriber<GCRobotics::i2cData> i2cSub("i2cSend", &i2cCallback );
ros::Subscriber<std_msgs::UInt16> gpioSub("gpio", &gpioCallback);

void setup(){
  Wire.begin(); // join i2c bus
  n.initNode();
  n.advertise(encoderPub);
  n.advertise(diagPub);
  n.advertise(errorPub);
  
  n.subscribe(i2cSub);
  n.subscribe(gpioSub);

  pinMode(13, OUTPUT);
  //DDRD = B11111111;
  
  errorCode.data = 0;
  Timer1.initialize(2000000); // 2000 ms between interrupts
  Timer1.attachInterrupt(Read);
  //Timer1.attachInterrupt(Read);
 // Timer1.attachInterrupt(sendVoltage);

}

void loop(){
  n.spinOnce();
  
  /*
  Wire.beginTransmission(0x04>>1); // transmit to device "address"
  Wire.write((byte)0);
  Wire.write((byte)200);
  Wire.write((byte)1);
  Wire.endTransmission();  
    digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  */
  
  
}

void i2cCallback( const GCRobotics::i2cData& msg)
{

  digitalWrite(13,HIGH);
  Wire.beginTransmission(msg.address>>1); // transmit to device "address"
  Wire.write((byte)0);
  Wire.write(msg.messageData);
  Wire.write(msg.messageData2);
  errorCode.data = Wire.endTransmission(); 
  errorCode.data = msg.address;
  errorPub.publish(&errorCode);
 
  digitalWrite(13,LOW);
}

void gpioCallback( const std_msgs::UInt16& msg)
{
  PORTD = msg.data;
}

void Read() {
  sei(); // enable interrupts inside of this interrrupt, allowing wire fucntion calls to still function instead of blocking
  digitalWrite(13,HIGH);
  encoders.encoder1 = ReadOne (0x2); // these need to be the right address
  encoders.encoder2 = ReadOne (0x4); // these need to be the right address
  encoders.encoder3 = ReadOne (0x6); // these need to be the right address
  encoders.encoder4 = ReadOne (0x8); // these need to be the right address
  //delay(5);
  encoderPub.publish(&encoders);
  digitalWrite(13,LOW);

}

int ReadOne(char address) { // pass in the motor you want to read
  unsigned int encoder[2] = {0,0};
  int encoderCountTotal = 0;
  Wire.requestFrom(address>>1, 2,0);    // request 2 bytes from address
   // digitalWrite(13,LOW);
   int i = 0;
  while(Wire.available())   // slave may send less than requested
  { 
    encoder[i] = Wire.read();   // receive a byte as character
    i++;
  }
  //encoders.encoder2 = encoder[0];
  
  encoder[1] = encoder[1] << 8;
  
  return encoder[1] + encoder[0];
  
}

void sendVoltage()
{
   voltage.data  = analogRead(0); // average reading
  voltage.data += analogRead(0);
  voltage.data += analogRead(0);
  voltage.data += analogRead(0);
  voltage.data = voltage.data/4;
  
  voltage.data = voltage.data * 0.021251222; // analog/1023 * 5 * 4.348, convert to voltage
  //delay(200);
  diagPub.publish(&voltage);
}

