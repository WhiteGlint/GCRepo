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
	char message[24]; // will hold the literal I^2C message

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

	// I^2C functions
	void send_message();
	void send_motor1();
	void send_motor2();
	void send_motor3();
	void send_motor4();
	void create_message1();
	void create_message2();
	void create_message3();
	void create_message4();
	void create_address(int);
	void create_type(int);
	void create_data(int, int);
	void push_i2c();

public:
	// constructor
	control_lib();

	// test functions
	void run_test();
	void give_output();

	// motion control functions
	void move_forward(int);
	void move_right(int);
	void move_backward(int);
	void move_left(int);
	void rotate_clockwise(int);
	void rotate_counterclockwise(int);
	void stop();
	void emergency_stop();

};