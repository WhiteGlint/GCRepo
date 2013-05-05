#ifndef ODOMETRY_GCR
#define ODOMETRY_GCR

#include "ros/ros.h"
#include "GCRobotics/Pose_msg.h"
#include "GCRobotics/Encoder_msg.h"

class Odometry
{
private:

	double en1, en2, en3, en4;

	// Random constants, not sure if their 100% correct	
	float wheelCircumference; // in centimeters per revolution
	float wheelRadius; // in centimeters
	int CPR; // counts per revolution
	int degreesPerCircle;
	float circleCircumference; // in centimeters... close enough
	double degreesPerCount; // how far around the circle we've traveled in deg/count
	int motorGearing;

	void processMotion();

	double XConversion;
	double YConversion;
	double frameWidth;
public:
	
	double X;
	double Y;
	double heading;

	
	// Ros things
	ros::NodeHandle n;
	ros::Subscriber sub;
	ros::Publisher pub;
	void init(int argc, char **argv);
	void odometryCallback(const GCRobotics::Encoder_msg::ConstPtr& msg);
	
};

#endif
