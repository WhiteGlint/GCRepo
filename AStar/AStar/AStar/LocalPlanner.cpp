#include "LocalPlanner.h"


LocalPlanner::LocalPlanner()
{
}

void LocalPlanner::move_to_point(){
	get_current_location();
	get_current_velocity();
	get_destination();
	calculate_new_heading();
	if (check_heading_difference() != 1)
		resolve_heading();
	else
		resolve_distance();

	// Begin debugging
	print_output();
	// End debugging
}

int LocalPlanner::check_heading_difference(){
	int ch, nh, sensitivity;
	sensitivity = 100000;
	/**************************************************
	To change the sensitivity of the comparison between
	headings, adjust the sensitivity.  A greater value
	of sensitivity will mean that the comparison is
	valid to more decimal places.  i.e. if the value is
	set to 1, the comparison will only look at the integer
	value of the heading.  If the value is 1000, the
	comparison will look up to three decimal places.
	*************************************************/
	ch = current_heading * sensitivity;
	nh = new_heading * sensitivity;

	if (ch == nh)
		return 1;
	else
		return 0;
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
	int quadrant;
	quadrant = calculate_quadrant();
	new_heading = calculate_theta(quadrant);
}

int LocalPlanner::calculate_quadrant(){
	if (destination[0] > current_location[0] && destination[1] >= current_location[1])
		return 1;
	else if (destination[0] <= current_location[0] && destination[1] > current_location[1])
		return 2;
	else if (destination[0] < current_location[0] && destination[1] <= current_location[1])
		return 3;
	else if (destination[0] >= current_location[0] && destination[1] < current_location[1])
		return 4;
	else
		return 0;
}

float LocalPlanner::calculate_theta(int quadrant){
	int delta_x, delta_y;
	delta_x = abs(destination[0] - current_location[0]);
	delta_y = abs(destination[1] - current_location[1]);
	switch (quadrant){
	case 1:
		return (atan(delta_y / delta_x));
		break;
	case 2:
		return (atan(delta_x / delta_y) + (PI / 2));
		break;
	case 3:
		return (atan(delta_y / delta_x) + PI);
		break;
	case 4:
		return (atan(delta_x / delta_y) + ((3 * PI) / 2));
		break;
	default:
		return -1;
	}
}

void LocalPlanner::resolve_heading(){
	float delta;
	delta = new_heading - current_heading;
	if (((-(2 * PI) < delta) && (delta < -(PI))) || ((0 < delta) && (delta < PI)))
		rotate_counterclockwise();
	else if (((-(PI) < delta) && (delta < 0)) || ((PI < delta) && (delta < (2 * PI))))
		rotate_clockwise();
	else if (delta == PI || delta == -(PI))
		rotate_clockwise();
}

void LocalPlanner::rotate_clockwise(){
	// Need to implement PID
	velocity_out = 5;
	direction_out = 4;
}

void LocalPlanner::rotate_counterclockwise(){
	// Need to implement PID
	velocity_out = 5;
	direction_out = 5;
}

void LocalPlanner::resolve_distance(){
	velocity_out = 5;
	direction_out = 0;
}

// Debugging functions
void LocalPlanner::print_output(){
	cout << "Velocity out = " << velocity_out << endl
		<< "Direction out = " << direction_out << endl;
	system("pause");
}