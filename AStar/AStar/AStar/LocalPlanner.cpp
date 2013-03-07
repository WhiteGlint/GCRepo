#include "LocalPlanner.h"


LocalPlanner::LocalPlanner()
{
}

void LocalPlanner::move_to_point(){
	get_current_location();
	get_current_velocity();
	get_destination();
	calculate_new_heading();
}

void LocalPlanner::get_current_location(){
	/****************************
	This needs to be adjusted such
	that it poll ROS for the current
	location coords
	****************************/
	cout << "Current Location:\nX = ";
	cin >> current_location[0];
	cout << "\nY = ";
	cin >> current_location[1];
	cout << "\nZ = ";
	cin >> current_location[2];
	cout << "\nHeading (in radians) = ";
	cin >> current_heading;
}

void LocalPlanner::get_current_velocity(){
	/****************************
	This needs to be adjusted such
	that it poll ROS for the current
	velocity
	****************************/
	cout << "Current velocity = ";
	cin >> current_velocity;
}

void LocalPlanner::get_destination(){
	/****************************
	This needs to be adjusted such
	that it poll ROS for the up to
	date destination
	****************************/
	cout << "Current destination:\nX = ";
	cin >> destination[0];
	cout << "\nY = ";
	cin >> destination[1];
}

void LocalPlanner::calculate_new_heading(){
	if (
}