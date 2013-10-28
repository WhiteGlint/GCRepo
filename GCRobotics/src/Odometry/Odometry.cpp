#include "Odometry.h"
#include "GCRobotics/Pose_msg.h"
#include "GCRobotics/Encoder_msg.h"
#include <iostream>


void Odometry::init(int argc, char **argv)
{
	pub = n.advertise<GCRobotics::Pose_msg>("CurrentPose",100);
	
	sub = n.subscribe("EncoderData", 100, &Odometry::odometryCallback, this);
	
	// Random constants, not sure if their 100% correct
	wheelCircumference = 0.1695; // in centimeters per revolution
	wheelRadius = 2.699; // in centimeters
	CPR = 360; // counts per revolution
	degreesPerCircle = 360;
	circleCircumference = 88.175081008304729835; // in centimeters... close enough
	/*	degreesPerCount = (CPR * wheelCircumference) / (circleCircumference * degreesPerCircle); // how far around the circle we've traveled in deg/count 
		units don't make sense	*/
	degreesPerCount = (degreesPerCircle * wheelCircumference) / (CPR * circleCircumference);
	motorGearing = 10;
	
	XConversion=250; // these two conversions were measured experimentally, they are probably not very accurate.
	YConversion =250;
	frameWidth = 0.3048;
	X = 0;
	Y = 0;
	heading = 0;

	return;
}

void Odometry::odometryCallback(const GCRobotics::Encoder_msg::ConstPtr& msg)
{
	en1 = msg->encoder1;
	en2 = msg->encoder2;
	en3 = msg->encoder3;
	en4 = msg->encoder4;
	
	processMotion();

	return;				
}

void Odometry::processMotion()
{
	double Yl = (en1 + en3)/YConversion;
	double Yr = (en2 + en4)/YConversion;
	
	double Xt = (en1 + en2)/XConversion;
	double Xb = (en3 + en4)/XConversion;
	
	Y += (Yl + Yr)/2;
	X += (Xt - Xb)/2;

	heading += atan((Yl-Yr)/frameWidth);
}
