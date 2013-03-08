#include "LocalPlanner.h"


LocalPlanner::LocalPlanner(){
	initialize_tables();
}

void LocalPlanner::initialize_tables(){
	/***************************************
	The left hand column is the speed output
	of the process.  In the distance table,
	the column on the right is the difference
	in map cells (5cm per cell) from the
	current location to the waypoint.  In the
	heading table, the column on the right is
	the difference in heading (in radians) from
	the current heading and the needed heading.
	***************************************/
	table_distance[0] = 0;
	table_distance[1] = 1;
	table_distance[2] = 2;
	table_distance[3] = 3;
	table_distance[4] = 5;
	table_distance[5] = 8;
	table_distance[6] = 12;
	table_distance[7] = 17;
	table_distance[8] = 23;
	table_distance[9] = 30;
	table_distance[10] = 100;

	table_heading[0] = 0;
	table_heading[1] = 0.087266463; // 5 deg
	table_heading[2] = 0.174532925; // 10 deg
	table_heading[3] = 0.261799388; // 15 deg
	table_heading[4] = 0.436332313; // 25 deg
	table_heading[5] = 0.698131701; // 40 deg
	table_heading[6] = 1.047197551; // 60 deg
	table_heading[7] = 1.483529864; // 85 deg
	table_heading[8] = 2.007128640; // 115 deg
	table_heading[9] = 2.617993878; // 150 deg
	table_heading[10] = 3.141592654; // 180 deg
}

void LocalPlanner::move_to_point(){
	get_current_location();
	get_destination();
	calculate_new_heading();
	if (check_heading_difference() == 0)
		resolve_heading();
	else
		resolve_distance();
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
	cout << "\nHeading (in degrees) = ";
	cin >> current_heading;

	// Converts input heading from degrees into radians
	current_heading = (current_heading) * ((2 * PI) / 360);
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
	float delta_x, delta_y;
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
		rotate_counterclockwise(delta);
	else if (((-(PI) < delta) && (delta < 0)) || ((PI < delta) && (delta < (2 * PI))))
		rotate_clockwise(delta);
	else if (delta == PI || delta == -(PI))
		rotate_clockwise(delta);
}

void LocalPlanner::rotate_clockwise(float delta){
	velocity_out = 0;
	delta = abs(delta);
	if (delta > PI)
		delta = (2 * PI) - delta;

	for (int i = 10; i >= 0; i--){
		if (delta <= table_heading[i]){
			velocity_out = i;
		}
	}
	direction_out = 4;
}

void LocalPlanner::rotate_counterclockwise(float delta){
	velocity_out = 0;
	delta = abs(delta);
	if (delta > PI)
		delta = (2 * PI) - delta;

	for (int i = 10; i >= 0; i--){
		if (delta <= table_heading[i]){
			velocity_out = i;
		}
	}
	direction_out = 5;
}

void LocalPlanner::resolve_distance(){
	velocity_out = 0;
	int delta;
	delta = calculate_distance_difference();
	for (int i = 10; i >= 0; i--){
		if (delta <= table_distance[i]){
			velocity_out = i;
		}
	}
	direction_out = 0;
}

int LocalPlanner::calculate_distance_difference(){
	float delta;
	int dx, dy;
	dx = abs(destination[0] - current_location[0]);
	dy = abs(destination[1] - current_location[1]);

	delta = sqrt(pow(dx, 2) + pow(dy, 2));

	return delta;
}

// Debugging functions
void LocalPlanner::print_output(){

	cout << "Velocity out = " << velocity_out << endl
		<< "Direction out = " << direction_out << endl;
	system("pause");
}