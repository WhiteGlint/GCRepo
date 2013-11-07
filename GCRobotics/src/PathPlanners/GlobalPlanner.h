#ifndef GLOBALPLANNER
#define GLOBALPLANNER

#include <iostream>
#include <fstream>
#include "ros/ros.h"
#include "Cell.h"
//#include "GCRobotics/Pose_msg.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/OccupancyGrid.h"

using namespace std;

class GlobalPlanner
{
private:
	

	Cell AllNodes[50][50];

	// Internal functions
	// Send Next Step
	void get_map_data();
	void populate_all_nodes();
	void get_destination();
	void get_current_location();
	void calculate_path();
		void set_current_square(int, int);
		void add_to_open_set(int, int);
		void find_lowest_f();
		void current_square_closed();
		void for_each_adjacent_square();
			void set_parent_to_current(int, int);
			void calculate_f_g_h(int, int, int);
			void compare_g_cost(int, int, int);
		int check_destination();
	void find_next_step();
		int find_heading(int, int);

	// Unused, pending decommission
	void activate_local_planner();

	
	


	// Debugging
	void print_map();
	void print_parents();
	void print_coordinates();
	

public:
	GlobalPlanner();
	void send_next_step();


	void halt();
	
	// ros things
	ros::NodeHandle n;
	ros::Subscriber CurrentPoseSub;
	ros::Subscriber GoalPoseSub;
	ros::Subscriber MapSub;
	ros::Publisher pub;
	void init(int argc, char **argv);
	void CurrentPositionCallback(const geometry_msgs::Twist::ConstPtr& msg);
	void GoalPositionCallback(const geometry_msgs::Twist::ConstPtr& msg);
	void MapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg);
	
	int next_step[2]; // y,x
	int current_location[2]; // y,x
	int destination[2]; // y,x
	int current_square[2];
	int map[50][50];
};

#endif
