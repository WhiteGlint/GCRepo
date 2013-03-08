#include "ros/ros.h"
#include "GlobalPlanner.h"

using namespace std;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "GlobalPlannerNode");
	
	GlobalPlanner planner;
	GCRobotics::Pose_msg data;
	
	planner.init(argc, argv);

	ros::Rate r(10); // 10 hz, decide appropriate value plz
	while (ros::ok())
	{
		ros::spinOnce();
		planner.send_next_step();
		data.x = planner.next_step[1];
		data.y = planner.next_step[0];
		planner.pub.publish(data);
		r.sleep();
	}


}


