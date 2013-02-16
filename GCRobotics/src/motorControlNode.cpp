#include "ros/ros.h"
#include "std_msgs/String.h"
#include "../include/motorControl.h"
#include <iostream>

using namespace std;

// Takes in velocity and direciton,
// Publishes messages for indiv motor control to i2cSend topic.



int main(int argc, char **argv)
{
	ros::init(argc, argv, "motorController");
	motorControl controller;
	controller.init(argc, argv);

	cin.get();
	controller.move_forward(5);
    	

	ros::spin();
	return 0;
}

