#ifndef BIN_H_
#define BIN_H_
#include <string>
using namespace std;

class Bin{
	int id;
	string type;

public:
	Bin(int id,string type);

	int getId();

	string getType();

};

#endif
