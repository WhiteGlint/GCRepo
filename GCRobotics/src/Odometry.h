#ifndef ODOMETRY_GCR
#define ODOMETRY_GCR

#include "ros/ros.h"
#include "GCRobotics/Pose_msg.h"
#include "GCRobotics/Encoder_msg.h"

class Odometry
{
private:

	double en1, en2, en3, en4;
	bool direction1, direction2, direction3, direction4;
	
	const float wheelCircumference = 16.95; // in centimeters per revolution
	const float wheelRadius = 2.699; // in centimeters
	const int CPR = 360; // counts per revolution
	const int degreesPerCircle = 360;
	const float circleCircumference = 88.175081008304729835; // in centimeters... close enough
	const double degreesPerCount = (degreesPerCircle * wheelCircumference) / (circleCircumference * CPR); // how far around the circle we've traveled in deg/count

	double x = 0;			
	double y = 0;
	double heading = 0;

	GCRobotics::Pose_msg data;
	
	// Ros things
	ros::NodeHandle n;
	ros::Subscriber sub;
	ros::Publisher pub;
	void init(int argc, char **argv);
	void odometryCallback(const GCRobotics::Encoder_msg::ConstPtr& msg);
	void processMotion();
	double moveStraight (double EC1, double EC2, double EC3, double EC4);
	double moveStrafe (double EC1, double EC2, double EC3, double EC4);
	double moveRotate (double EC1, double EC2, double EC3, double EC4);
	
};

#endif
