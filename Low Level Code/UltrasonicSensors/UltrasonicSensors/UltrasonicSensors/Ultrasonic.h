/*
* Ultrasonic.h
*
* Created: 3/15/2014 4:32:08 PM
* Author: Quang
*/


#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__




class Ultrasonic
{
	//variables
	public:
	volatile unsigned long PreviousTime, InterruptEchoTime;
	volatile int Select, Edge;
	unsigned long EchoTime[6];	// Array containing the time of the ultrasonic sensors

	//functions
	public:
	Ultrasonic();
	~Ultrasonic();
	void interrupt();
	void initialize();
	void spinOnce();
	void trigger();
	void addressSelect(int Address);
	void pinSelect (int Address);

	private:
	Ultrasonic( const Ultrasonic &c );
	Ultrasonic& operator=( const Ultrasonic &c );

}; //Ultrasonic

#endif //__ULTRASONIC_H__
