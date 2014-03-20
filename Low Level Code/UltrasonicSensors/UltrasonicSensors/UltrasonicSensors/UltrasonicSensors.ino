
/*
 * UltrasonicInterrupt.ino
 *
 * Created: 3/14/2014 7:22:23 PM
 * Author: Quang
 */ 
#include "Ultrasonic.h"
#include <Wire.h>
#include "Motors.h"
	
	
/********************************************************
*          Constants for Ultrasonic Sensors
*********************************************************/
#define SENSOR_RIGHT_1 0
#define SENSOR_RIGHT_2 1
#define SENSOR_BACK_1  2
#define SENSOR_TOLERANCE 5
#define MAX_DISTANCE 200

#define _A_ Ultra.EchoDistance[0]
#define _B_ Ultra.EchoDistance[1]
#define _C_ Ultra.EchoDistance[2]
#define _D_ Ultra.EchoDistance[3]
#define _E_ Ultra.EchoDistance[4]
#define _F_ Ultra.EchoDistance[5]



int StateMachine;        // This is a State Machine that tells the robot what it should do
// with the ultrasonic data
// 0 -> The robot is trying to make it self parallel to the wall by rotating CW/CCW
// 1 -> The robot is trying to reach the x-axis target by strafing
// 2 -> The robot is trying to reach the y-axis target by moving forward or backward

// Target Variables
int SensorTargetRight = 30, SensorTargetBack = 40;


// Create instance of the class Ultrasonic
Ultrasonic Ultra;
// Create instance of the class Motors
Motors Robot;


/*********************************************************
*
*				Setup Loop
*
**********************************************************/
void setup()
{
	Ultra.initialize();
	// Attach int.0 interrupt at pin 2
	attachInterrupt(0,ultraInterrupt,CHANGE);
}

/*********************************************************
*
*				Infinite Loop
*
**********************************************************/
void loop()
{
	int temp = StateMachine;
	// Code for the break message:
	// {Ultra.EchoDistance[0]},{Ultra.EchoDistance[1]}, {Ultra.EchoDistance[2]},{Ultra.EchoDistance[3]},{Ultra.EchoDistance[4]},{Ultra.EchoDistance[5]}
	Ultra.spinOnce();
	
	// If we have finally collect the first set of the ultrasonic data
	if (Ultra.FullSet == 1)
	{
		// All the conditional Statements goes in here.
		// Making sure both sides are parallel
		if (StateMachine == 0)
		{
			// If the difference of the 2 right sensors are greater than the tolerance
			if ( ((_A_ - _B_) > SENSOR_TOLERANCE) || ((_A_ - _B_) < -SENSOR_TOLERANCE) )
			{
				// Determining if robot needs to rotate CW or CCW
				if (_A_ > _B_)
				{
					Robot.cw(MediumSpeed);
					delay(1);
				}
				else
				{
					Robot.ccw(MediumSpeed);
					delay(1);
				}
			}
			// Stop the robot and move to the next state if the robot parallel
			else {
				Robot.stop();
				StateMachine++;
			}
		}
		
		// Making sure the robot reaches the x-axis target
		if (StateMachine == 1)
		{
			// If the Front right sensor is greater than the X-Target
			// We are only using one of the sensor to check for distance
			if ((_A_ < (SensorTargetRight - SENSOR_TOLERANCE)) || (_A_ > (SensorTargetRight + SENSOR_TOLERANCE)))
			{
				// Determining if the robot needs to strafe left or right
				if (_A_ < (SensorTargetRight - SENSOR_TOLERANCE))
				{
					Robot.left(MediumSpeed);
				}
				else
				{
					Robot.right(MediumSpeed);
				}
			}
			// The robot is at the x-axis target
			else
			{
				// Determine if the robot is at the x-axis target && is parallel to the wall
				if ((_A_ >= (SensorTargetRight - SENSOR_TOLERANCE)) && (_A_ <= (SensorTargetRight + SENSOR_TOLERANCE))
																	&&
				(_B_ >= (SensorTargetRight - SENSOR_TOLERANCE)) && (_B_ <= (SensorTargetRight + SENSOR_TOLERANCE)))
				{
					//stop the robot and go to the next state
					Robot.stop();
					StateMachine++;
				}
				// else the robot needs to go back to state 0 and try to get it self parallel to the wall
				else
				{
					StateMachine--;
				}
			}
		}
		
		// Making sure the robot reaches the y-axis
		if (StateMachine == 2)
		{
			// Making sure the back sensor is outside the target value
			if ((_C_ < (SensorTargetBack - SENSOR_TOLERANCE)) || (_C_ > (SensorTargetBack + SENSOR_TOLERANCE)))
			{
				// Deciding if the robot needs to move forward or backward
				if (_C_ < (SensorTargetBack - SENSOR_TOLERANCE))
				{
					Robot.forward(MediumSpeed);
				}
				else
				{
					Robot.backward(MediumSpeed);
				}
			}
			// The robot is at the y-axis target
			else
			{
				// Determining if the robot is (parallel to the wall) && (at the x-axis target) && (at the y-axis target)
				if (
				(_A_ >= (SensorTargetRight - SENSOR_TOLERANCE)) &&
				(_A_ <= (SensorTargetRight + SENSOR_TOLERANCE)) &&
				(_B_ >= (SensorTargetRight - SENSOR_TOLERANCE)) &&
				(_B_ <= (SensorTargetRight + SENSOR_TOLERANCE)) &&
				(_C_ >= (SensorTargetRight - SENSOR_TOLERANCE)) &&
				(_C_ <= (SensorTargetRight + SENSOR_TOLERANCE))   )
				{
					//stop the robot and go to the next state
					Robot.stop();
					StateMachine++;
				}
				// else the robot needs to go back to state 0 and try to get it self parallel to the wall
				else
				{
					StateMachine = 0;
				}
			}
		}
	}
	delay(10);
}

/*********************************************************
*
*				Ultrasonic Interrupt Routine
*
**********************************************************/
void ultraInterrupt()
{
	Ultra.interrupt();
}


