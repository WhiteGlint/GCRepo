#ifndef CELL
#define CELL

class Cell
{
private:
	int F, G, H;
	int parent[2];
	int available; // 0 = available, 1 = unavailable
	int set; // 8 = none, 0 = open set, 1 = closed set; default 8
public:
	// Constructor
	Cell();
	// Accessors
	int get_F();
	int get_G();
	int get_H();
	void get_parent(int*, int*);
	int get_available();
	int get_set();
	// Mutators
	void set_F(int);
	void set_G(int);
	void set_H(int);
	void set_parent(int, int);
	void set_available(int);
	void set_set(int);
};

#endif