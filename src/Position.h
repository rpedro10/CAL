#ifndef POSITION_H_
#define POSITION_H_
#include <string>
using namespace std;

class DegPos{
	long longitude,latitude;

public:
	DegPos(long longitude, long latitude);
	long getLongitude(){return longitude;};
	long getLatitude(){return latitude;};
};

class RadPos{
	long longitude,latitude;

public:
	RadPos(long longitude, long latitude);
	long getLongitude(){return longitude;};
	long getLatitude(){return latitude;};
};


#endif
