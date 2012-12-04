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

// test functions
void control_lib::run_test()
{
	give_output();
	system("pause");
	move_forward(5);
	give_output();
	move_forward(2);
	give_output();
	stop();
	give_output();
	system("pause");
	rotate_clockwise(8);
	give_output();
	rotate_counterclockwise(5);
	give_output();
	cout << "\n***THE END***\n";
	system("pause");	
}

void control_lib::give_output()
{
	cout << "motor1_speed = " << motor1_speed << endl
		<< "motor2_speed = " << motor2_speed << endl
		<< "motor3_speed = " << motor3_speed << endl
		<< "motor4_speed = " << motor4_speed << endl
		<< "motor1_direction = " << motor1_direction << endl
		<< "motor2_direction = " << motor2_direction << endl
		<< "motor3_direction = " << motor3_direction << endl
		<< "motor4_direction = " << motor4_direction << endl
		<< "movement_direction = " << movement_direction << endl
		<< "travel_speed = " << travel_speed << endl;
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

void control_lib::move_right(int speed)
{
	if (movement_direction != 1)
		stop();

	movement_direction = 1;
	goto_speed(speed, movement_direction);
}

void control_lib::move_backward(int speed)
{
	if (movement_direction != 2)
		stop();

	movement_direction = 2;
	goto_speed(speed, movement_direction);
}

void control_lib::move_left(int speed)
{
	if (movement_direction != 3)
		stop();

	movement_direction = 3;
	goto_speed(speed, movement_direction);
}

void control_lib::rotate_clockwise(int speed)
{
	if (movement_direction != 4)
		stop();

	movement_direction = 4;
	goto_speed(speed, movement_direction);
}

void control_lib::rotate_counterclockwise(int speed)
{
	if (movement_direction != 5)
		stop();

	movement_direction = 5;
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
		slow_down();
	
	if (travel_speed < speed) // need to speed up
		speed_up();

	send_message();
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
// not sure if the right and left combos are correct
// not sure if rotations are correct
// not sure about wheel numbering scheme
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
	movement_direction = 1;
	motor1_direction = 1;
	motor2_direction = 1;
	motor3_direction = 0;
	motor4_direction = 0;
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
	movement_direction = 3;
	motor1_direction = 0;
	motor2_direction = 0;
	motor3_direction = 1;
	motor4_direction = 1;
}

void control_lib::set_direction_clockwise()
{
	movement_direction = 4;
	motor1_direction = 1;
	motor2_direction = 0;
	motor3_direction = 1;
	motor4_direction = 0;
}

void control_lib::set_direction_counterclockwise()
{
	movement_direction = 5;
	motor1_direction = 0;
	motor2_direction = 1;
	motor3_direction = 0;
	motor4_direction = 1;
}

void control_lib::set_direction_stop()
{
	movement_direction = 6;
	motor1_direction = 0;
	motor2_direction = 0;
	motor3_direction = 0;
	motor4_direction = 0;
}

// Speed controllers
void control_lib::slow_down()
{
	travel_speed--;
	motor1_speed--;
	motor2_speed--;
	motor3_speed--;
	motor4_speed--;
}

void control_lib::speed_up()
{
	travel_speed++;
	motor1_speed++;
	motor2_speed++;
	motor3_speed++;
	motor4_speed++;
}

void control_lib::wait()
{
	// wait for 50 ms
}

void control_lib::send_message()
{
	bool message[24];
	cout << "\nmessage sent\n";
	send_motor1();
	send_motor2();
	send_motor3();
	send_motor4();
}

void control_lib::send_motor1()
{

}

void control_lib::send_motor2()
{

}

void control_lib::send_motor3()
{

}

void control_lib::send_motor4()
{

}