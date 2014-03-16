/*
* Ultrasonic.cpp
*
* Created: 3/15/2014 4:32:08 PM
* Author: Quang
*/

#include "Ultrasonic.h"
#include <Arduino.h>

#define TRIGGER_PIN 3
#define ECHO_PIN 2
#define ADDR0_PIN 6			// Least significant of the address select
#define ADDR1_PIN 5
#define ADDR2_PIN 4			// Most significant of the address select bit

// default constructor
Ultrasonic::Ultrasonic()
{
} //Ultrasonic

// default destructor
Ultrasonic::~Ultrasonic()
{
} //~Ultrasonic


void Ultrasonic::initialize()
{
	// Set echo pin as input
	pinMode(ECHO_PIN, INPUT);
	// set trigger pin as output
	pinMode(TRIGGER_PIN, OUTPUT);
	
	
	// Set the address pins as output
	pinMode(ADDR0_PIN, OUTPUT);
	pinMode(ADDR1_PIN, OUTPUT);
	pinMode(ADDR2_PIN, OUTPUT);
	
	// Set these pin to LOW to begin with
	digitalWrite(ADDR0_PIN, LOW);
	digitalWrite(ADDR1_PIN, LOW);
	digitalWrite(ADDR2_PIN, LOW);
	digitalWrite(TRIGGER_PIN, LOW);
	
	
}

void Ultrasonic::spinOnce()
{
	if ((Select == 0) || (Select == 2) || (Select == 4) ||
	(Select == 6) || (Select == 8) || (Select == 10) || (Select == 12))
	{
		// Record the ultrasonic sensor.
		// Skip the first one since there is nothing to read
		if (Select > 0)
		{
			// The index of the array is equal to (Select/2) +1
			// Ex.
			// We want to store of the first ultrasonic sensor, which is at Select = 2
			// index = (2/2) - 1 = 0  <-- that's is the index that we want
			EchoTime[((Select/2) - 1)] = InterruptEchoTime;
		}
		
		// Reset to zero at the value of 12
		if (Select >= 12)
		{
			Select = 0;
		}
		
		// Set the address pins to the correct address
		addressSelect(Select);
		// Set the trigger pin to HIGH for 10 us
		trigger();
		// Increment to odd
		Select++;
	}
}

void Ultrasonic::interrupt()
{
	// If it just went from lOW to HIGH, then this is the beginning of the echo cycle
	if (digitalRead(ECHO_PIN) == 1) {
		//if (Edge == 0) {
		PreviousTime = micros();
		Edge = 1;
	}
	// If it just went from HIGH to LOW, then this is the end of the echo cycle
	else if (digitalRead(ECHO_PIN) == 0){
		//else if (Edge == 1) {
		InterruptEchoTime = micros() - PreviousTime;
		//Increment the select variable to even
		Select++;
		Edge = 0;
	}
}

void Ultrasonic::trigger()
{
	// According to the data sheet, we need to set trigger to high for 10 us
	digitalWrite(TRIGGER_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIGGER_PIN,LOW);
}

void Ultrasonic::addressSelect(int Address)
{
	switch (Address)
	{
		case 0:
		pinSelect(0);
		break;
		case 2:
		pinSelect(1);
		break;
		case 4:
		pinSelect(2);
		break;
		case 6:
		pinSelect(3);
		break;
		case 8:
		pinSelect(4);
		break;
		case 10:
		pinSelect(5);
		break;
		
	}
}

void Ultrasonic::pinSelect (int Address)
{
	// Set the least sig. digit
	digitalWrite(ADDR0_PIN, (Address & 0x01));			// & is to mask the bits
	// Set the middle digit
	digitalWrite(ADDR1_PIN, (Address & 0x02));
	// Set the most sig. digit
	digitalWrite(ADDR2_PIN, (Address & 0x04));
}