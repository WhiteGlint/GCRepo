#include "ros/ros.h"
#include "std_msgs/String.h"
#include "GCRobotics/i2cData.h"
#include "../include/motorControl.h"

using namespace std;

// Takes in velocity and direciton,
// Publishes messages for indiv motor control to i2cSend topic.



int main(int argc, char **argv)
{
	motorControl controller;
	controller.init(argc, argv);
	
	ros::spin();
	return 0;
}

