
// object for motor control library
#include <iostream>
#include <unistd.h>
#include "../include/motorControl.h"
#include "GCRobotics/i2cData.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "ros/ros.h"

using namespace std;

void motorControl::init(int argc, char **argv)
{
	pub = n.advertise<GCRobotics::i2cData>("i2cSend",100);
	
	sub = n.subscribe("cmd_vel", 100, &motorControl::velocityCallback, this);
	return;
}

char get_direction(geometry_msgs::Twist msg) {
    if (msg.linear.x > 0)
        return 'w';
    else if (msg.linear.x < 0)
        return 's';
    else if (msg.linear.y > 0)
        return 'a';
    else if (msg.linear.y < 0)
        return 'd';
    else if (msg.angular.z > 0)
        return 'q';
    else if (msg.angular.z < 0)
        return 'e';
    return 'f';
}

int get_velocity(geometry_msgs::Twist msg) {
    if (msg.linear.x != 0)
        return int(msg.linear.x);
    else if (msg.linear.y != 0)
        return int(msg.linear.y);
    else if (msg.angular.z != 0)
        return int(msg.angular.z);
    return 0;
}

// Transforms m/s and rad/s into the units/s used by the arduino
geometry_msgs::Twist transform_velocity(const geometry_msgs::Twist::ConstPtr& msg)
{
    float standard_conversion = 260; // Max velocity is 0.25 m/s and max u/s is 65 u/s.
    float angular_conversion = 2 * 3.14159265359 / 1.13; // 2PI / robot circumference
    geometry_msgs::Twist transformed_velocity;

    transformed_velocity.linear.x = standard_conversion * msg->linear.x;
    transformed_velocity.linear.y = standard_conversion * msg->linear.y;
    transformed_velocity.angular.z = standard_conversion * msg->angular.z / angular_conversion;

    return transformed_velocity;
}

void motorControl::velocityCallback(const geometry_msgs::Twist::ConstPtr& msg)
{	
    geometry_msgs::Twist transformed_velocity = transform_velocity(msg);
	
	switch (get_direction(transformed_velocity))
	{
        case 'f':
        case 'w':  
            move_forward(get_velocity(transformed_velocity));
            break;
        case 'd':
            move_right(-get_velocity(transformed_velocity));
            break;
        case 's':  
            move_backward(-get_velocity(transformed_velocity));
            break;
        case 'a':
            move_left(get_velocity(transformed_velocity));
            break;
        case 'e':  
            rotate_clockwise(-get_velocity(transformed_velocity));
            break;
        case 'q':
            rotate_counterclockwise(get_velocity(transformed_velocity));
            break;
		case 11:
		case 12:
		case 13:
		case 14:
			motor_n(get_velocity(transformed_velocity),
                    get_direction(transformed_velocity),
                    get_direction(transformed_velocity) - 10);
			break;
		case 15:
		case 16:
		case 17:
		case 18:
			motor_n(get_velocity(transformed_velocity),
                    get_direction(transformed_velocity),
                    get_direction(transformed_velocity) - 14);
			break;
	}
	

	return;	
}

// constructor
motorControl::motorControl()
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
void motorControl::run_test()
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
//	system("pause");
	cin.get();

	move_forward(5);
	give_output();
	cin.get();

	move_forward(2);
	give_output();
	cin.get();

	stop();
	give_output();
//	system("pause");
	cin.get();

	rotate_clockwise(8);
	give_output();
	cin.get();

	rotate_counterclockwise(5);
	give_output();
	cout << "\n***THE END***\n";
//	system("pause");	
	cin.get();
}

void motorControl::give_output()
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
void motorControl::move_forward(int speed)
{
	// If it isn't already moving forward, stop current motion
	if (movement_direction != 0)
		stop();

	movement_direction = 0;
	goto_speed(speed, movement_direction);
}

void motorControl::move_right(int speed)
{
	if (movement_direction != 1)
		stop();

	movement_direction = 1;
	goto_speed(speed, movement_direction);
}

void motorControl::move_backward(int speed)
{
	if (movement_direction != 2)
		stop();

	movement_direction = 2;
	goto_speed(speed, movement_direction);
}

void motorControl::move_left(int speed)
{
	if (movement_direction != 3)
		stop();

	movement_direction = 3;
	goto_speed(speed, movement_direction);
}

void motorControl::rotate_clockwise(int speed)
{
	if (movement_direction != 4)
		stop();

	movement_direction = 4;
	goto_speed(speed, movement_direction);
}

void motorControl::rotate_counterclockwise(int speed)
{
	if (movement_direction != 5)
		stop();

	movement_direction = 5;
	goto_speed(speed, movement_direction);
}

void motorControl::stop()
{
	goto_speed(0, movement_direction);
	movement_direction = 6;
}

void motorControl::motor_n(int speed, int direction, int motor)
{
	if (movement_direction != 0)
		stop();

	movement_direction = direction;
	goto_speed_isolated(speed, movement_direction, motor);
}

// Inside jobs
// top levels
void motorControl::goto_speed(int speed, int direction)
{
	// if it is already going at the requested speed then stop
	if (speed == travel_speed)
		return;

	set_direction(direction);

	//if (travel_speed > speed) // need to slow down
	//	slow_down();
	
	//if (travel_speed < speed) // need to speed up
	//	speed_up();
	travel_speed = speed;
	motor1_speed = speed;
	motor2_speed = speed;
	motor3_speed = speed;
	motor4_speed = speed;
	
	send_message();
	//wait();
	//goto_speed(speed, direction); // go again until the speed is reached
}

void motorControl::goto_speed_isolated(int speed, int direction, int motor)
{
	// if it is already going at the requested speed then stop
	if (speed == travel_speed)
		return;

	if (direction >= 11 && direction <= 14)
		set_direction(0);
	else
		set_direction(1);

	travel_speed = speed;

	motor1_speed = 0;
	motor2_speed = 0;
	motor3_speed = 0;
	motor4_speed = 0;

	switch (motor)
	{
		case 1:
			motor1_speed = speed;
			break;
		case 2:
			motor2_speed = speed;
			break;
		case 3:
			motor3_speed = speed;
			break;
		case 4:
			motor4_speed = speed;
			break;
	}
	
	send_message();
}

// low level controllers
void motorControl::set_direction(int direction)
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
void motorControl::set_direction_forward()
{
	movement_direction = 0;
	motor1_direction = 0;
	motor2_direction = 0;
	motor3_direction = 0;
	motor4_direction = 0;
}

void motorControl::set_direction_right()
{
	movement_direction = 1;
	motor1_direction = 1;
	motor2_direction = 0;
	motor3_direction = 1;
	motor4_direction = 0;
}	

void motorControl::set_direction_backward()
{
	movement_direction = 2;
	motor1_direction = 1;
	motor2_direction = 1;
	motor3_direction = 1;
	motor4_direction = 1;
}

void motorControl::set_direction_left()
{
	movement_direction = 3;
	motor1_direction = 0;
	motor2_direction = 1;
	motor3_direction = 0;
	motor4_direction = 1;
}

void motorControl::set_direction_clockwise()
{
	movement_direction = 4;
	motor1_direction = 1;
	motor2_direction = 1;
	motor3_direction = 0;
	motor4_direction = 0;
}

void motorControl::set_direction_counterclockwise()
{
	movement_direction = 5;
	motor1_direction = 0;
	motor2_direction = 0;
	motor3_direction = 1;
	motor4_direction = 1;
}

void motorControl::set_direction_stop()
{
	movement_direction = 6;
	motor1_direction = 0;
	motor2_direction = 0;
	motor3_direction = 0;
	motor4_direction = 0;
}

// Speed controllers
void motorControl::slow_down()
{
	travel_speed--;
	motor1_speed--;
	motor2_speed--;
	motor3_speed--;
	motor4_speed--;
}

void motorControl::speed_up()
{
	travel_speed++;
	motor1_speed++;
	motor2_speed++;
	motor3_speed++;
	motor4_speed++;
}

void motorControl::wait()
{
	// wait for 50 ms
//	Sleep(wait_time);
	usleep(1000*wait_time);
}

// I^2C messaging
void motorControl::send_message()
{
	cout << "\nmessage sent\n";
	send_motor1();
	send_motor2();
	send_motor3();
	send_motor4();

}

void motorControl::send_motor1()
{
	create_message1();
	push_i2c();
}

void motorControl::send_motor2()
{
	create_message2();
	push_i2c();
}

void motorControl::send_motor3()
{
	create_message3();
	push_i2c();
}

void motorControl::send_motor4()
{
	create_message4();
	push_i2c();
}

// Message creation
void motorControl::create_message1()
{
	create_address(0x02);
	create_type(0);
	create_data(motor1_direction, motor1_speed); 
}

void motorControl::create_message2()
{
	create_address(0x04);
	create_type(0);
	create_data(motor2_direction, motor2_speed);
}

void motorControl::create_message3()
{
	create_address(0x06);
	create_type(0);
	create_data(motor3_direction, motor3_speed);
}

void motorControl::create_message4()
{
	create_address(0x08);
	create_type(0);
	create_data(motor4_direction, motor4_speed);
}

void motorControl::create_address(int address)
{
	message_address = address;
}

void motorControl::create_type(int type)
{
	// since this only uses one type of message
	// i need to know what literal to put in here
	message[0] = 0;
}

void motorControl::create_data(int direction, int speed)
{
	message[1] = speed;
	
	if (direction == 1)
		message[2] = 1;
	else
		message[2] = 0;
}

void motorControl::push_i2c()
{

//	if (i2c_Init(I2CMODE_AUTO,100000) == false) cout << "ERROR!!: " << roboio_GetErrMsg();
	//i2c_Send(message_address, message, 2);

	GCRobotics::i2cData data;

	data.address = message_address;
	data.messageType = message[0];
	data.messageData = message[1];
	data.messageData2 = message[2];
	
	pub.publish(data);

//	i2c_Close();
	/*
	// actual message when we get it working
	// i2c_Send(addr(char), buf(char[]), size(int);
	// i2c_Send(message_address, message, 2);
	//cout << (int) message_address << " | "
	//	<< (int) message[0] << " | "
	//	<< (int) message[1];
	
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
                << message[15];
        
        cout << endl;
        */
}
