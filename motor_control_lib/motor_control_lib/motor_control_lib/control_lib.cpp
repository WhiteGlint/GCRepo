// object for motor control library
#include <iostream>
#include "control_lib.h"
using namespace std;

// constructor
control_lib::control_lib()
{
	motor1_speed = 0;
	motor2_speed = 0;
	motor3_speed = 0;
	motor4_speed = 0;
	motor1_direction = 0;
	motor2_direction = 0;
	motor3_direction = 0;
	motor4_direction = 0;
	movement_direction = 6;
	travel_speed = 0;
}

// motion control functions
void control_lib::move_forward(int speed)
{
	// If it isn't already moving forward, stop current motion
	if (movement_direction != 0)
		stop();

	movement_direction = 0;
	goto_speed(speed, movement_direction);
}

void control_lib::stop()
{
	goto_speed(0, 6);
}

// Inside jobs
// top levels
void control_lib::goto_speed(int speed, int direction)
{
	// if it is already going at the requested speed then stop
	if (speed == travel_speed)
		return;

	set_direction(direction);

	if (travel_speed > speed) // need to slow down
		slow_down(direction);
	
	if (travel_speed < speed) // need to speed up
		speed_up(direction);

	set_all_motor_speeds();

	wait();
	goto_speed(speed, direction); // go again until the speed is reached
}

// low level controllers
void control_lib::set_direction(int direction)
{
	switch (direction)
	{
	case 0: set_direction_forward();
		break;
	case 1: set_direction_right();
		break;
	case 2: set_direction_backward();
		break;
	case 3: set_direction_left();
		break;
	case 4: set_direction_clockwise();
		break;
	case 5: set_direction_counterclockwise();
		break;
	case 6: set_direction_stop();
		break;
	}
}

// set all direction variables
void control_lib::set_direction_forward()
{
	movement_direction = 0;
	motor1_direction = 0;
	motor2_direction = 0;
	motor3_direction = 0;
	motor4_direction = 0;
}

void control_lib::set_direction_right()
{

}

void control_lib::set_direction_backward()
{
	movement_direction = 2;
	motor1_direction = 1;
	motor2_direction = 1;
	motor3_direction = 1;
	motor4_direction = 1;
}

void control_lib::set_direction_left()
{

}

void control_lib::set_direction_clockwise()
{

}

void control_lib::set_direction_counterclockwise()
{

}

void control_lib::set_direction_stop()
{
	movement_direction = 6;
	motor1_direction = 6;
	motor2_direction = 6;
	motor3_direction = 6;
	motor4_direction = 6;
}

// Speed controllers
void control_lib::slow_down(int direction)
{

}

void control_lib::speed_up(int direction)
{

}

void control_lib::set_all_motor_speeds()
{

}

void control_lib::wait()
{

}