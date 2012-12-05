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
	message[0] = 'i';
	message[1] = 'n';
	message[2] = 'i';
	message[3] = 't';
	message[4] = 'i';
	message[5] = 'a';
	message[6] = 'l';
	message[7] = 'i';
	message[8] = 'z';
	message[9] = 'e';
	message[10] = 'd';
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
	goto_speed(0, movement_direction);
	movement_direction = 6;
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
	cout << "\nmessage sent\n";
	send_motor1();
	send_motor2();
	send_motor3();
	send_motor4();
}

void control_lib::send_motor1()
{
	create_message1();
	push_i2c();
}

void control_lib::send_motor2()
{
	create_message2();
	push_i2c();
}

void control_lib::send_motor3()
{
	create_message3();
	push_i2c();
}

void control_lib::send_motor4()
{
	create_message4();
	push_i2c();
}

// Message creation
void control_lib::create_message1()
{
	create_address(1);
	create_type(0);
	create_data(motor1_direction, motor1_speed);
}

void control_lib::create_message2()
{
	create_address(2);
	create_type(0);
	create_data(motor2_direction, motor2_speed);
}

void control_lib::create_message3()
{
	create_address(3);
	create_type(0);
	create_data(motor3_direction, motor3_speed);
}

void control_lib::create_message4()
{
	create_address(4);
	create_type(0);
	create_data(motor4_direction, motor4_speed);
}

void control_lib::create_address(int address)
{
	for (int i = 8; i--; i >= 0)
	{
		if (address % 2 == 1)
			message[i] = 1 + 48;
		else
			message[i] = 0 + 48;

		address = address / 2;
	}
}

void control_lib::create_type(int type)
{
	// since this only uses on type of message
	// i need to know what literal to put in here
	message[8] = 0 + 48;
	message[9] = 0 + 48;
	message[10] = 0 + 48;
	message[11] = 0 + 48;
	message[12] = 0 + 48;
	message[13] = 0 + 48;
	message[14] = 0 + 48;
	message[15] = 0 + 48;
}

void control_lib::create_data(int direction, int speed)
{
	for (int i = 24; i--; i >= 17)
	{
		if (i < 17) break;
		if (speed % 2 == 1)
			message[i] = 1 + 48;
		else
			message[i] = 0 + 48;

		speed = speed / 2;
	}
	message[16] = direction + 48;
}

void control_lib::push_i2c()
{
	cout << message[0]
		<< message[1]
		<< message[2]
		<< message[3] << " "
		<< message[4]
		<< message[5]
		<< message[6]
		<< message[7] << " | "
		<< message[8]
		<< message[9]
		<< message[10]
		<< message[11] << " "
		<< message[12]
		<< message[13]
		<< message[14]
		<< message[15] << " | "
		<< message[16]
		<< message[17]
		<< message[18]
		<< message[19] << " "
		<< message[20]
		<< message[21]
		<< message[22]
		<< message[23];
	// test message output
		/*
	for (int i = 0; i = i + 1; i < 24)
	{
		cout << "|";
		cout << message[i];
	}*/
	cout << endl;
}