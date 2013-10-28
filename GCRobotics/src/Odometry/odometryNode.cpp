
/*

		NAME 	 - Odometry Node 
		DESIGN - Josh Galicic - David Mine
		PRIORITY - Required - Required for deriving position from encoders
	
		--------OVERVIEW--------
This node takes encoder data from the arduino and calculates the 3D position of the bot.
To convert between encoder counts and meters, there is an XConversion and a YConversion that
get multiplied to the encoder position (see Odometry.cpp). This position is broadcast through
tf as well as a custom position message for debugging purposes only. The tf transform goes between
'odom', the frame that is fixed to the world; and 'base_link', the frame that is attached to the bot frame.


		--------FUTURE WORK--------
The X and Y conversion factors are very rough approximations that were found experimentally by driving the
bot forward a meter and checking encoder counts, a better way should be figured out for doing this. 

A lot of the conversion factors should be setup as ros parameters so that recompiling isnt necessary for
minor changes. Checkout how to do this on the ros wiki, there are also tutorials on how to do this. 

*/

#include "ros/ros.h"
#include "Odometry.h"
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
using namespace std;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "odometryNode");
	Odometry controller;
	controller.init(argc, argv);
	GCRobotics::Pose_msg data;
	tf::TransformBroadcaster br;
	tf::Transform transform;
	tf::Quaternion q;
	

	ros::Rate r(10); // 10 hz
	while (ros::ok())
	{
		data.x = controller.X;
		data.y = controller.Y;
		data.z = 0;
		data.heading = controller.heading;

		controller.pub.publish(data);

  		transform.setOrigin( // Set global position to send to tf
			tf::Vector3(
						controller.X*sin(controller.heading) + controller.Y*cos(controller.heading) ,
						controller.X*cos(controller.heading) - controller.Y*sin(controller.heading) ,
						0.0 ) );
						
			q.setRPY(0,0,controller.heading); // Convert heading calculation into quaternion to give to tf.
  		transform.setRotation(q);
  		br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link")); // Send the transform
	

		ros::spinOnce();

		r.sleep();
	}


}


