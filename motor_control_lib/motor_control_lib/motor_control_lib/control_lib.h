// header for motor control library

class control_lib
{
private:
	static int const acceleration = 50; // wait time between motor speed steps in milleseconds
	int motor1_speed,
		motor2_speed,
		motor3_speed,
		motor4_speed,
		motor1_direction,
		motor2_direction,
		motor3_direction,
		motor4_direction,
		movement_direction, // overal direction of movement
		travel_speed; // overall speed of movement

	void set_speed(int, int, int);
	void goto_speed(int, int);

public:
	// constructor
	control_lib();

	// motion control functions
	void move_forward(int);
	void move_right(int);
	void move_backward(int);
	void move_left(int);
	void rotate_clockwise(int);
	void rotate_couterclockwise(int);
	void stop();
	void emergency_stop();

};