#ifndef TRUCK_H_
#define TRUCK_H_
#include <string>
using namespace std;

class Truck{

	string type;
	int capacity;

public:
	Truck(string type, int capacity);

	string getType();

	int getCapacity();

};

#endif
