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
	double getDistance(double long1,double lat1){
		double u = sin((latitude - lat1) / 2);
				double v = sin((longitude - long1) / 2);
		return 2.0 * 6371.0* asin(sqrt(u * u + cos(lat1) * cos(latitude) * v * v));

	}
};

#endif
