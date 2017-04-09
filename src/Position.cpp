#include "Position.h"

Position::Position(double longitude, double latitude) {
	this->longitude = longitude;
	this->latitude = latitude;
}
;
Position::Position() {
}
;

double Position::getLongitude() {
	return longitude;
}
;
double Position::getLatitude() {
	return latitude;
}
;
double Position::getDistance(double long1, double lat1) {
	double u = sin((latitude - lat1) / 2);
	double v = sin((longitude - long1) / 2);
	return 2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1) * cos(latitude) * v * v));

}
