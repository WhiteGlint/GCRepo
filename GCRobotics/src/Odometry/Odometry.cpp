#include "Odometry.h"
#include "GCRobotics/Pose_msg.h"
#include "GCRobotics/Encoder_msg.h"
#include <iostream>


void Odometry::init(int argc, char **argv)
{
	pub = n.advertise<GCRobotics::Pose_msg>("CurrentPose",100);
	
	sub = n.subscribe("EncoderData", 100, &Odometry::odometryCallback, this);
	
	// Measurements are in cm and deg
	// "Circle" refers to the circle made by the rotation of the robot about its axis of rotation (which should be dead center)
	wheelRadius = 2.699; // in centimeters
	wheelCircumference = 16.958 ; // in centimeters
	CPR = 650; // encoder counts per revolution of the wheel
	degreesPerCircle = 360;
	circleCircumference = 113; // in centimeters (approximate)
	degreesPerCount = (degreesPerCircle * wheelCircumference) / (CPR * circleCircumference);
	motorGearing = 10;
	
	XConversion= 1; // these two conversions were measured experimentally, they are probably not very accurate.
	YConversion = 1;
	frameWidth = 30.48;
	X = 0;
	Y = 0;
	heading = 0;
}

void Odometry::odometryCallback(const GCRobotics::Encoder_msg::ConstPtr& msg)
{
	en1 = msg->encoder1;
	en2 = msg->encoder2;
	en3 = msg->encoder3;
	en4 = msg->encoder4;
	
	processMotion();			
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
