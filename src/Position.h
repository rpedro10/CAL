#ifndef POSITION_H_
#define POSITION_H_
#include <string>
using namespace std;

class Position{
	double longitude,latitude;

public:
	Position(double longitude, double latitude){
		this->longitude=longitude;
		this->latitude =latitude;
	};
	Position(){};

	double getLongitude(){return longitude;};
	double getLatitude(){return latitude;};
};

#endif
