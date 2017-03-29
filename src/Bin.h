#ifndef BIN_H_
#define BIN_H_
#include <string>
using namespace std;

class Bin{
	int id;
	string type;
	int capacity;
	bool full;

public:
	Bin(int id,string type, int capacity);

	int getId();

	string getType();

	int getCapacity();

	bool isFull();
};

#endif
