#include "ros/ros.h"
#include "LocalPlanner.h"


using namespace std;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "LocalPlannerNode");
	
	LocalPlanner planner;
	GCRobotics::simpleVelocity data;
	
	planner.init(argc, argv);

	ros::Rate r(10); // 10 hz, decide appropriate value plz
	while (ros::ok())
	{
		ros::spinOnce();
		
		planner.move_to_point();
		data.speed = planner.velocity_out;
		data.direction = planner.direction_out;
		
		planner.pub.publish(data);
		r.sleep();
	}


}


