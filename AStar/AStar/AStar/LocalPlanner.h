#ifndef LOCALPLANNER
#define LOCALPLANNER

#include <iostream>
#include <cmath>
using namespace std;

class LocalPlanner
{
private:
	int current_location[3]; // have a slot for z, but it will not be used
	float current_heading; // the read in value is in radians
	int current_velocity;
	float new_heading;
	int destination[2];
	
	int velocity_out;
	float heading_out;

	// Move to Point methods
	void get_current_location();
	void get_destination();
	void get_current_velocity();
	void calculate_new_heading();
		int calculate_quadrant();
		float calculate_theta(int);
	void resolve_heading();
	void resolve_distance();

public:
	LocalPlanner();
	void move_to_point();
	void halt();
};

#endif