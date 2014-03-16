#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_PWMServoDriver.h"


Adafruit_MotorShield Steppers = Adafruit_MotorShield();

Adafruit_StepperMotor *LiftStepper = Steppers.getStepper(100, 1);
//Adafruit_StepperMotor *LiftStepper = Steppers.getStepper(200, 1);

int Level = 0, Data = 0;

void setup()
{
	// Setup default for steppers
	Steppers.begin();
	// Set the rpm of the stepper
	LiftStepper -> setSpeed(100);
	
	liftSlaveInitialize();
	Level = liftSlaveGetLevel();
}

void loop()
{
	if (liftSlaveStateChangeCheck() == 1)
	{
		liftSlaveSetBusy();
		LiftStepper -> step(300, FORWARD, SINGLE);
		//LiftStepper -> step(400, FORWARD, SINGLE);
		liftSlaveSetReady();
	}
}

