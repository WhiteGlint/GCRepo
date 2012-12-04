// header for motor control library

class control_lib
{
private:
	static int const acceleration = 50; // wait time between motor speed steps in milleseconds
	int motor1_speed, // directionless, 0-10
		motor2_speed,
		motor3_speed,
		motor4_speed;
	bool motor1_direction, // 0 forward, 1 backward
		motor2_direction,
		motor3_direction,
		motor4_direction;
	int movement_direction, // overal direction of movement
		travel_speed; // directionless, 0-10

	// top level inside jobs
	void set_speed(int, int, int);
	void goto_speed(int, int);

	// low level controllers
	void set_direction(int);
	void slow_down();
	void speed_up();
	void wait();

	// direction setters
	void set_direction_forward();
	void set_direction_right();
	void set_direction_backward();
	void set_direction_left();
	void set_direction_clockwise();
	void set_direction_counterclockwise();
	void set_direction_stop();

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