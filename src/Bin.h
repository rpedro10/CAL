#ifndef BIN_H_
#define BIN_H_
#include <string>
using namespace std;

class Bin{
	int id;
	string type;
	int max_capacity;

public:
	Bin(int id,string type);

	int getId();

	string getType();
	int getMaxCapacity() const;
	void setMaxCapacity(int maxCapacity);
};

#endif
