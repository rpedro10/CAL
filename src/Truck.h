#ifndef TRUCK_H_
#define TRUCK_H_
#include <string>
using namespace std;

class Truck{
	int id;
	string type;
	//int capacity;

public:
	Truck(int id,string type, int capacity);

	int getId();

	string getType();


};

#endif
