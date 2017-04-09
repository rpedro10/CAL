#ifndef POSITION_H_
#define POSITION_H_
#include <string>
#include <math.h>
using namespace std;

class Position{
	double longitude,latitude;

public:
	Position(double longitude, double latitude);
	Position();

	double getLongitude();
	double getLatitude();
	double getDistance(double long1,double lat1);
};

#endif
