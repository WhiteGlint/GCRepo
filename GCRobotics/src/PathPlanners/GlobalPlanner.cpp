#include "GlobalPlanner.h"


GlobalPlanner::GlobalPlanner(){
}

//ros code initialization
void GlobalPlanner::init(int argc, char **argv)
{
	pub = n.advertise<geometry_msgs::Twist>("NextPose",100);
	
	CurrentPoseSub = n.subscribe("CurrentPose", 100, &GlobalPlanner::CurrentPositionCallback, this);
	GoalPoseSub = n.subscribe("GoalPose", 100, &GlobalPlanner::GoalPositionCallback, this);
	MapSub = n.subscribe("map", 100, &GlobalPlanner::MapCallback, this);
	return;
}

void GlobalPlanner::CurrentPositionCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
	current_location[0] = msg->linear.y;
	current_location[1] = msg->linear.x;	
	return;
}

void GlobalPlanner::GoalPositionCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
	destination[0] = msg->linear.y;
	destination[1] = msg->linear.x;
	return;
}

void GlobalPlanner::MapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg)
{
	//map = msg->data;
	return;
}

// Public methods
void GlobalPlanner::send_next_step(){
	get_map_data();
	populate_all_nodes();
	get_destination();
	get_current_location();
	calculate_path();
	find_next_step();
}

void GlobalPlanner::halt(){

}


// Internal Functions
void GlobalPlanner::get_map_data(){
	/*****************************
	This needs to be adjusted such
	that it will receive map data
	from ROS
	*****************************/
	fstream readmap;
	readmap.open("testmap.txt");
	for (int i = 0; i < 50; i++){
		for (int j = 0; j < 50; j++){
			readmap >> map[i][j];
			//cout << "Read value map[" << i << "][" << j << "] = " << map[i][j] << endl;	// Debugging line
		}
	}
	readmap.close();
}

void GlobalPlanner::populate_all_nodes(){
	/********************************
	Need to set the value at which it
	is safe to assume a cell is open
	********************************/
	for (int i = 0; i < 50; i++){
		for (int j = 0; j < 50; j++){
			if (map[i][j] < 1){	// set this value as lowest threshold
				AllNodes[i][j].set_available(0);
			}
			else{
				AllNodes[i][j].set_available(1);
			}
		}
	}
}

void GlobalPlanner::get_destination(){
	/*****************************
	This needs to be adjusted such
	that it will read the destination
	coords from ROS
	****************************/
	cout << "Destination:\nX = ";
	cin >> destination[1];
	cout << "\nY = ";
	cin >> destination[0];
}

void GlobalPlanner::get_current_location(){
	/****************************
	This needs to be adjusted such
	that it poll ROS for the current
	location coords
	****************************/
	cout << "Current Location:\nX = ";
	cin >> current_location[1];
	cout << "\nY = ";
	cin >> current_location[0];
}

void GlobalPlanner::calculate_path(){
	set_current_square(current_location[0], current_location[1]);
	add_to_open_set(current_square[0], current_square[1]);
	do{
		find_lowest_f();
		current_square_closed();
		for_each_adjacent_square();
	} while (check_destination() == 0);
}

void GlobalPlanner::set_current_square(int x, int y){
	current_square[0] = x;
	current_square[1] = y;
}

void GlobalPlanner::add_to_open_set(int x, int y){
	AllNodes[x][y].set_set(0);
}

void GlobalPlanner::find_lowest_f(){
	int x = -1, y = -1;
	// Find a starting point in the open set
	for (int i = 0; i < 50; i++){
		for (int j = 0; j < 50; j++){
			if (AllNodes[i][j].get_set() == 0){
				x = i;
				y = j;
				break;
			}
		}
		if (x != -1 && y != -1){
			break;
		}
	}
	for (int i = 0; i < 50; i++){
		for (int j = 0; j < 50; j++){
			if (AllNodes[i][j].get_set() == 0){
				if (AllNodes[i][j].get_F() < AllNodes[x][y].get_F()){
					x = i;
					y = j;
				}
			}
		}
	}

	set_current_square(x, y);
}

void GlobalPlanner::current_square_closed(){
	AllNodes[current_square[0]][current_square[1]].set_set(1);
}

void GlobalPlanner::for_each_adjacent_square(){
	int x, y;
	
	x = current_square[0] + 1;
	y = current_square[1];
	if (x < 50){
		if (AllNodes[x][y].get_available() == 0 && AllNodes[x][y].get_set() != 1){
			if (AllNodes[x][y].get_set() != 0){
				add_to_open_set(x, y);
				set_parent_to_current(x, y);
				calculate_f_g_h(x, y, 10);
			}
			else{
				compare_g_cost(x, y, 10);
			}
		}
	}

	x = current_square[0] + 1;
	y = current_square[1] + 1;
	if (x < 50 && y < 50){
		if (AllNodes[x][y].get_available() == 0 && AllNodes[x][y].get_set() != 1){
			if (AllNodes[x - 1][y].get_available() != 1 && AllNodes[x][y - 1].get_available() != 1){
				if (AllNodes[x][y].get_set() != 0){
					add_to_open_set(x, y);
					set_parent_to_current(x, y);
					calculate_f_g_h(x, y, 14);
				}
				else{
					compare_g_cost(x, y, 14);
				}
			}
		}
	}

	x = current_square[0];
	y = current_square[1] + 1;
	if (y < 50){
		if (AllNodes[x][y].get_available() == 0 && AllNodes[x][y].get_set() != 1){
			if (AllNodes[x][y].get_set() != 0){
				add_to_open_set(x, y);
				set_parent_to_current(x, y);
				calculate_f_g_h(x, y, 10);
			}
			else{
				compare_g_cost(x, y, 10);
			}
		}
	}

	x = current_square[0] - 1;
	y = current_square[1] + 1;
	if (x >= 0 && y < 50){
		if (AllNodes[x][y].get_available() == 0 && AllNodes[x][y].get_set() != 1){
			if (AllNodes[x + 1][y].get_available() != 1 && AllNodes[x][y - 1].get_available() != 1){
				if (AllNodes[x][y].get_set() != 0){
					add_to_open_set(x, y);
					set_parent_to_current(x, y);
					calculate_f_g_h(x, y, 14);
				}
				else{
					compare_g_cost(x, y, 14);
				}
			}
		}
	}

	x = current_square[0] - 1;
	y = current_square[1];
	if (x >= 0){
		if (AllNodes[x][y].get_available() == 0 && AllNodes[x][y].get_set() != 1){
			if (AllNodes[x][y].get_set() != 0){
				add_to_open_set(x, y);
				set_parent_to_current(x, y);
				calculate_f_g_h(x, y, 10);
			}
			else{
				compare_g_cost(x, y, 10);
			}
		}
	}

	x = current_square[0] - 1;
	y = current_square[1] - 1;
	if (x >= 0 && y >= 0){
		if (AllNodes[x][y].get_available() == 0 && AllNodes[x][y].get_set() != 1){
			if (AllNodes[x + 1][y].get_available() != 1 && AllNodes[x][y + 1].get_available() != 1){
				if (AllNodes[x][y].get_set() != 0){
					add_to_open_set(x, y);
					set_parent_to_current(x, y);
					calculate_f_g_h(x, y, 14);
				}
				else{
					compare_g_cost(x, y, 14);
				}
			}
		}
	}

	x = current_square[0];
	y = current_square[1] - 1;
	if (y >= 0){
		if (AllNodes[x][y].get_available() == 0 && AllNodes[x][y].get_set() != 1){
			if (AllNodes[x][y].get_set() != 0){
				add_to_open_set(x, y);
				set_parent_to_current(x, y);
				calculate_f_g_h(x, y, 10);
			}
			else{
				compare_g_cost(x, y, 10);
			}
		}
	}

	x = current_square[0] + 1;
	y = current_square[1] - 1;
	if (x < 50 && y >= 0){
		if (AllNodes[x][y].get_available() == 0 && AllNodes[x][y].get_set() != 1){
			if (AllNodes[x - 1][y].get_available() != 1 && AllNodes[x][y + 1].get_available() != 1){
				if (AllNodes[x][y].get_set() != 0){
					add_to_open_set(x, y);
					set_parent_to_current(x, y);
					calculate_f_g_h(x, y, 14);
				}
				else{
					compare_g_cost(x, y, 14);
				}
			}
		}
	}
}

void GlobalPlanner::set_parent_to_current(int x, int y){
	AllNodes[x][y].set_parent(current_square[0], current_square[1]);
}

void GlobalPlanner::calculate_f_g_h(int x, int y, int cost){
	int px, py, f, g, h;
	AllNodes[x][y].get_parent(&px, &py);
	g = AllNodes[px][py].get_G() + cost;
	AllNodes[x][y].set_G(g);

	h = 10 * (abs(x - destination[0]) + abs(y - destination[1]));
	AllNodes[x][y].set_H(h);

	AllNodes[x][y].set_F(g + h);

}

void GlobalPlanner::compare_g_cost(int x, int y, int cost){
	int new_g;
	new_g = AllNodes[current_square[0]][current_square[1]].get_G() + cost;
	if (new_g < AllNodes[x][y].get_G()){
		AllNodes[x][y].set_parent(current_square[0], current_square[1]);
		calculate_f_g_h(x, y, cost);
	}
}

int GlobalPlanner::check_destination(){
	if (current_square[0] == destination[0] && current_square[1] == destination[1])
		return 1;
	else
		return 0;
}

void GlobalPlanner::find_next_step(){
	int lock[2];
	int heading, temp_heading;
	int temp_coords[2];

	next_step[0] = destination[0];
	next_step[1] = destination[1];

	lock[0] = next_step[0];
	lock[1] = next_step[1];
	
	heading = -1;
	temp_heading = -2;

	while (lock[0] != current_location[0] || lock[1] != current_location[1]){
		
		temp_heading = find_heading(lock[0], lock[1]);
		if (temp_heading != heading){
			heading = temp_heading;
			next_step[0] = lock[0];
			next_step[1] = lock[1];
		}
		
		temp_coords[0] = lock[0];
		temp_coords[1] = lock[1];
		AllNodes[temp_coords[0]][temp_coords[1]].get_parent(&lock[0], &lock[1]);
	}
}

int GlobalPlanner::find_heading(int x, int y){
	int px, py;
	AllNodes[x][y].get_parent(&px, &py);

	if (px == x && py > y)
		return 0;
	if (px < x && py > y)
		return 45;
	if (px < x && py == y)
		return 90;
	if (px < x && py < y)
		return 135;
	if (px == x && py < y)
		return 180;
	if (px > x && py < y)
		return 225;
	if (px > x && py == y)
		return 270;
	if (px > x && py > y)
		return 315;
	else
		return -1;
}



void GlobalPlanner::activate_local_planner(){
	/********************************
	This needs to be reworked so that
	it calls the start function from
	the local planner
	********************************/
	cout << "The coordinates chosen were: (" << next_step[1] << ", " << next_step[0] << ")\n";
	system("pause");
}

// Debugging
void GlobalPlanner::print_map(){
	system("cls");
	for (int i = 0; i < 50; i++){
		for (int j = 0; j < 50; j++){
			cout << AllNodes[i][j].get_set();
		}
		cout << endl;
	}
}

void GlobalPlanner::print_parents(){
	system("cls");
	for (int i = 0; i < 50; i++){
		for (int j = 0; j < 50; j++){
			if (AllNodes[i][j].get_available() == 0){
				int px, py;
				AllNodes[i][j].get_parent(&px, &py);
				cout << "Parent of (" << j << ", " << i << ") is (" << px << ", " << py << ")\n";
				if (j == 20 && i == 2)
					system("pause");
			}
		}
	}
	system("pause");
}

void GlobalPlanner::print_coordinates(){
	cout << "Coordinates chosen were (" << next_step[1] << ", " << next_step[0] << ")\n";
}
