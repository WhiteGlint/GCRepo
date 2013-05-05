/*

		NAME 	 - Dead Reckoning Node 
		DESIGN - Josh Galicic
		PRIORITY - Diagnostic - Not required for functionality
	
		--------OVERVIEW--------
This node takes in velocity data and creates a 3D pose based only off of this data.
The idea is to show the ideal position of the bot, and be able to compare it to
the actual position created by odometry. Use this to test for the accuracy of the
bot's travel path & motor configuration.

		--------FUTURE WORK--------
This node has no ability to process rotation, therefore only pure X or Y movement
Will be calculated, I dunno what rotation will do it right now. If you fix it,
please remove this message.

*/

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
	
	t1 = ros::Time::now().toSec();
	
	pub.publish(msg);
	
	tf::TransformBroadcaster br;
	tf::Transform transform;
 	transform.setOrigin( tf::Vector3(msg.pose.position.x, msg.pose.position.y, 0.0) );
 	transform.setRotation(tf::Quaternion(0,0,0));
 	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "ideal_base_link"));
	
	
}
