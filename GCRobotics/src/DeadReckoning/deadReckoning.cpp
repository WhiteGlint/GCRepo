#include "ros/ros.h"
#include "std_msgs/String.h"
#include "GCRobotics/i2cData.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/PoseStamped.h"
#include "GCRobotics/simpleVelocity.h"
#include <tf/transform_broadcaster.h>

#include <iostream>

using namespace std;


double vx1 = 0;
double vy1 = 0;
double t1 = 0;


ros::Publisher pub;

geometry_msgs::PoseStamped msg;

void callback(const GCRobotics::simpleVelocity::ConstPtr&);

int main(int argc, char **argv)
{
	ros::init(argc, argv,"DeadReckoningNode");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("Velocity", 100, callback);

	pub = n.advertise<geometry_msgs::PoseStamped>("DeadPose",100);
		
	msg.header.frame_id = "/odom";	
	ros::spin();

	return 0;
}
			
void callback(const GCRobotics::simpleVelocity::ConstPtr& data)
{
	if(vx1 != 0) // forward x velocity
	{ 
		msg.pose.position.x = msg.pose.position.x + (vx1*(ros::Time::now().toSec()-t1));
		msg.pose.position.y = msg.pose.position.y + 0;
	}
	if(vy1 != 0) // backward x velocity
	{
		msg.pose.position.x = msg.pose.position.x +0;
		msg.pose.position.y = msg.pose.position.y + (vy1*(ros::Time::now().toSec()-t1));
	}
		
	//vx1 = data->linear.x;  // FIX HERE!!!!!!!!!!!1
	//vy1 = data->linear.y;
	t1 = ros::Time::now().toSec();
	
	pub.publish(msg);
	
	tf::TransformBroadcaster br;
	tf::Transform transform;
  	transform.setOrigin( tf::Vector3(msg.pose.position.x, msg.pose.position.y, 0.0) );
  	transform.setRotation(tf::Quaternion(0,0,0));
  	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));
	
	
}
