#include "ros/ros.h"
#include "Odometry.h"

using namespace std;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "Odometry");
	Odometry controller;
	controller.init(argc, argv);
	GCRobotics::Pose_msg data;
		
	ros::Rate r(10); // 10 hz
	while (ros::ok())
	{
		data.x = controller.x;
		data.y = controller.y;
		data.z = 0;
		data.heading = controller.heading;

		controller.pub.publish(data);

		ros::spinOnce();

		r.sleep();
	}


}


