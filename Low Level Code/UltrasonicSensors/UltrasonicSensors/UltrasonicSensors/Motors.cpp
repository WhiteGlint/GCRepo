/* 
* Motors.cpp
*
* Created: 3/16/2014 12:16:09 AM
* Author: Quang
*/


#include "Motors.h"
#include <Wire.h>
#include <Arduino.h>

// default constructor
Motors::Motors()
{
	Wire.begin(); // join i2c bus
} //Motors

// default destructor
Motors::~Motors()
{
} //~Motors

void Motors::forward(int RobotSpeed)
{
	i2cWrite(Front_Left,   RobotSpeed,   Forward  );
	i2cWrite(Front_Right,  RobotSpeed,   Forward  );
	i2cWrite(Back_Left,    RobotSpeed,   Forward  );
	i2cWrite(Back_Right,   RobotSpeed,   Forward  );
}

void Motors::backward(int RobotSpeed)
{
	i2cWrite(Front_Left,   RobotSpeed,   Backward  );
	i2cWrite(Front_Right,  RobotSpeed,   Backward  );
	i2cWrite(Back_Left,    RobotSpeed,   Backward  );
	i2cWrite(Back_Right,   RobotSpeed,   Backward  );
}

void Motors::left(int RobotSpeed)
{
	i2cWrite(Front_Left,   RobotSpeed,   Backward  );
	i2cWrite(Front_Right,  RobotSpeed,   Forward   );
	i2cWrite(Back_Left,    RobotSpeed,   Forward   );
	i2cWrite(Back_Right,   RobotSpeed,   Backward  );
}

void Motors::right(int RobotSpeed)
{
	i2cWrite(Front_Left,   RobotSpeed,   Forward   );
	i2cWrite(Front_Right,  RobotSpeed,   Backward  );
	i2cWrite(Back_Left,    RobotSpeed,   Backward  );
	i2cWrite(Back_Right,   RobotSpeed,   Forward   );
}

void Motors::cw(int RobotSpeed)
{
	i2cWrite(Front_Left,   RobotSpeed,   Forward   );
	i2cWrite(Front_Right,  RobotSpeed,   Backward  );
	i2cWrite(Back_Left,    RobotSpeed,   Forward   );
	i2cWrite(Back_Right,   RobotSpeed,   Backward  );
}

void Motors::ccw(int RobotSpeed)
{
	i2cWrite(Front_Left,   RobotSpeed,   Backward   );
	i2cWrite(Front_Right,  RobotSpeed,   Forward    );
	i2cWrite(Back_Left,    RobotSpeed,   Backward   );
	i2cWrite(Back_Right,   RobotSpeed,   Forward    );
}

void Motors::stop()
{
	i2cWrite(Front_Left,   Stop,   Forward   );
	i2cWrite(Front_Right,  Stop,   Forward  );
	i2cWrite(Back_Left,    Stop,   Forward  );
	i2cWrite(Back_Right,   Stop,   Forward   );
}

void Motors::i2cWrite ( char Address, char Speed , char Direction)
{
	Wire.beginTransmission(Address >> 1 );
	Wire.write((byte)0);
	Wire.write((byte)Speed);
	Wire.write((byte)Direction);
	Wire.endTransmission();
}