/*

		NAME 	 - Motor Control Node 
		DESIGN - Yan Sleight
		PRIORITY - Required - Converts velocity to motor commands
	
		--------OVERVIEW--------
This node takes in velocity and generates motor commands to send to the arduino.
No issues have been found, this node has been tested pretty thuroughly. Some
steamlining for effeciency/readability could be done but is not required.

*/

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "../include/motorControl.h"
#include <iostream>

using namespace std;

// Takes in velocity and direction,
// Publishes messages for indiv motor control to i2cSend topic.



int main(int argc, char **argv)
{
	ros::init(argc, argv, "motorControlNode");
	motorControl controller;
	controller.init(argc, argv);

	//cin.get();
	//controller.move_forward(5);
    	

	ros::spin();
	return 0;
}

