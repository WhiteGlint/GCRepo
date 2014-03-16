/*
 * UltrasonicInterrupt.ino
 *
 * Created: 3/14/2014 7:22:23 PM
 * Author: Quang
 */ 
#include "Ultrasonic.h"
	
// Create instance of the class Ultrasonic
Ultrasonic Ultra;

void setup()
{
	Ultra.initialize();
	// Attach int.0 interrupt at pin 2
	attachInterrupt(0,ultraInterrupt,CHANGE);
}

void loop()
{
	// Code for the break message:
	// {Ultra.EchoTime[0]},{Ultra.EchoTime[1]}, {Ultra.Echotime[2]},{Ultra.Echotime[3]},{Ultra.Echotime[4]},{Ultra.Echotime[5]}
	Ultra.spinOnce();
	delay(100);
}

void ultraInterrupt()
{
	Ultra.interrupt();
}


