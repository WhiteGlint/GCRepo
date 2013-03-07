#include "Cell.h"

Cell::Cell(){
	F = 0;
	G = 0;
	H = 0;
	parent[0] = 0;
	parent[1] = 0;
	available = 0;
	set = 8;
}
// Accessors
int Cell::get_F(){
	return F;
}
int Cell::get_G(){
	return G;
}
int Cell::get_H(){
	return H;
}
void Cell::get_parent(int* x, int* y){
	*x = parent[0];
	*y = parent[1];
}
int Cell::get_available(){
	return available;
}
int Cell::get_set(){
	return set;
}
// Mutators
void Cell::set_F(int new_f){
	F = new_f;
}
void Cell::set_G(int new_g){
	G = new_g;
}
void Cell::set_H(int new_h){
	H = new_h;
}
void Cell::set_parent(int x, int y){
	parent[0] = x;
	parent[1] = y;
}
void Cell::set_available(int value){
	available = value;
}
void Cell::set_set(int value){
	set = value;
}
