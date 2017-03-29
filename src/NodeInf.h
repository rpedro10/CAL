#ifndef NODEINF_H_
#define NODEINF_H_
#include <string>
#include "Position.h"
using namespace std;

class NodeInf{

	long id;
	DegPos coordinate;
	RadPos point;

public:
	long getId(){return id;};
	DegPos getCoordinate(){return coordinate;};
	RadPos getPoint(){return point;};
};


#endif
