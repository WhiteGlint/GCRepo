#ifndef LOCALPLANNER
#define LOCALPLANNER

#include <iostream>
#include <cmath>
#define PI 3.14159265
using namespace std;

class LocalPlanner
{
private:
	int current_location[3]; // have a slot for z, but it will not be used
	float current_heading; // the read in value is in radians
	int current_velocity;
	float new_heading;
	int destination[2];
	
	// Published variables
	int velocity_out;
	float direction_out;
	/***********************
	0 = forward
	1 = right
	2 = backward
	3 = left
	4 = clockwise
	5 = counterclockwise
	6 = stop
	***********************/

	// Move to Point methods
	void get_current_location();
	void get_destination();
	void get_current_velocity();
	void calculate_new_heading();
		int calculate_quadrant();
		float calculate_theta(int);
	void resolve_heading();
		int check_heading_difference();
		void rotate_clockwise();
		void rotate_counterclockwise();
	void resolve_distance();

	// Debugging functions
	void print_output();

public:
	LocalPlanner();
	void move_to_point();
	void halt();
};

#endif