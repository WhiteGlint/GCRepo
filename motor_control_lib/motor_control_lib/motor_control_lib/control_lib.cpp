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

}

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