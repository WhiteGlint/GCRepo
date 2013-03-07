#include "ros/ros.h"
#include "Odometry.h"

using namespace std;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "Odometry");
	Odometry controller;
	controller.init(argc, argv);
	
	ros::Rate r(10); // 10 hz
	while (ros::ok())
	{
		data.x = controller.x;
		data.y = controller.y;
		data.z = controller.z;
		data.heading = controller.heading;

		pub.publish(data);

		ros::spinOnce();

		r.sleep();
	}


}


