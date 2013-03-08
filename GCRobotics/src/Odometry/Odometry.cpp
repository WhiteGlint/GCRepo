#include "Odometry.h"
#include "GCRobotics/Pose_msg.h"
#include "GCRobotics/Encoder_msg.h"


void Odometry::init(int argc, char **argv)
{
	pub = n.advertise<GCRobotics::Pose_msg>("CurrentPose",100);
	
	sub = n.subscribe("EncoderData", 100, &Odometry::odometryCallback, this);
	
	wheelCircumference = 16.95; // in centimeters per revolution
	wheelRadius = 2.699; // in centimeters
	CPR = 360; // counts per revolution
	degreesPerCircle = 360;
	circleCircumference = 88.175081008304729835; // in centimeters... close enough
	degreesPerCount = (degreesPerCircle * wheelCircumference) / (circleCircumference * CPR); // how far around the circle we've traveled in deg/count

	x = 0;
	y = 0;
	heading = 0;

	return;
}

void Odometry::odometryCallback(const GCRobotics::Encoder_msg::ConstPtr& msg)
{
	en1 = msg->encoder1;
	en2 = msg->encoder2;
	en3 = msg->encoder3;
	en4 = msg->encoder4;
	
	direction1 = msg->direction1;
	direction2 = msg->direction2;	
	direction3 = msg->direction3;	
	direction4 = msg->direction4;		
	
	processMotion();

	return;				
}

/*void Odometry::processVelocity() // only call this once the robot has actually moved (straight or strafe)
{

}*/
		
void Odometry::processMotion()
{	
	if(!direction1 && !direction2 && !direction3 && !direction4) // back
	{
		//velocityDistance = moveStraight(en1, en2, en3, en4);
		//velocityHeading = heading + 180;
		x += moveStraight(en1, en2, en3, en4) * cos(heading+180);
		y += moveStraight(en1, en2, en3, en4) * sin(heading+180);
	}
	else if(!direction1 && !direction2 && direction3 && direction4) // strafe right
	{
		//velocityDistance = moveStrafe(en1, en2, en3, en4);
		//velocityHeading = heading + 270;
		x += moveStrafe(en1, en2, en3, en4) * cos(heading+270);
		y += moveStrafe(en1, en2, en3, en4) * sin(heading+270);
	}
	else if(!direction1 && direction2 && !direction3 && direction4) // ccw
	{
		heading += moveRotate(en1, en2, en3,en4);
	}
	else if(direction1 && !direction2 && direction3 && !direction4) // cw
	{
		heading -= moveRotate(en1, en2, en3,en4);
	}
	else if(direction1 && direction2 && !direction3 && !direction4) // strafe left
	{
		//velocityDistance = moveStrafe(en1, en2, en3, en4);
		//velocityHeading = heading + 90;
		x += moveStrafe(en1, en2, en3, en4) * cos(heading+90);
		y += moveStrafe(en1, en2, en3, en4) * sin(heading+90);
	}
	else if(direction1 && direction2 && direction3 && direction4) // forward
	{
		//velocityDistance = moveStraight(en1, en2, en3, en4);
		//velocityHeading = heading;
		x += moveStraight(en1, en2, en3, en4) * cos(heading);
		y += moveStraight(en1, en2, en3, en4) * sin(heading);
	}
		
}

double Odometry::moveStraight (double EC1, double EC2, double EC3, double EC4) { // Pass in 4 integers
	long double count = (EC1 + EC2 + EC3 + EC4) / 4; // Average the inputs

	double distanceTraveled = (count * wheelCircumference / CPR); // Kstraight
	return distanceTraveled;
}

double Odometry::moveStrafe (double EC1, double EC2, double EC3, double EC4) { // Pass in 4 integers
	double distanceTraveled = moveStraight(EC1, EC2, EC3, EC4) * sin(45); // Kstrafe = Kstraight * sin(45)
	return distanceTraveled;
}

double Odometry::moveRotate (double EC1, double EC2, double EC3, double EC4) {
	long double count = (EC1 + EC2 + EC3 + EC4) / 4; // Average the inputs	
	double degreesTurned = degreesPerCount * count;
	return (degreesTurned *3.14159/180);
}

