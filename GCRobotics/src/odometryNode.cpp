#include "Odometry.h"

using namespace std;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "Odometry");
	Odometry controller;
	controller.init(argc, argv);
	
	ros::spin();
}


