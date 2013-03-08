#include <iostream>
#include "GlobalPlanner.h"
#include "LocalPlanner.h"
using namespace std;

int main(){
	GlobalPlanner GP;
	LocalPlanner LP;

	//GP.send_next_step();
	LP.move_to_point();

	cout << "Hello World\n";
	system("pause");
	return 0;
}