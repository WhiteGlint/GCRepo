#include "ros/ros.h"
#include "Odometry.h"
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
using namespace std;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "Odometry");
	Odometry controller;
	controller.init(argc, argv);
	GCRobotics::Pose_msg data;
	tf::TransformBroadcaster br;
	tf::Transform transform;
	tf::Quaternion q;
	

	ros::Rate r(10); // 10 hz
	while (ros::ok())
	{
		data.x = controller.x;
		data.y = controller.y;
		data.z = 0;
		data.heading = controller.heading;

		controller.pub.publish(data);

  		transform.setOrigin( 
			tf::Vector3(controller.x*cos(controller.heading) - controller.y*sin(controller.heading),
						controller.x*sin(controller.heading) + controller.y*cos(controller.heading) , 0.0) );
		q.setRPY(0,0,controller.heading);
  		transform.setRotation(q);
  		br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));
	

		ros::spinOnce();

		r.sleep();
	}


}


