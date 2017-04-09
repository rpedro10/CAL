#include "Road.h"

Road::Road(long long _id, string _name, bool b_ways) {
	this->id = _id;
	this->name = _name;
	this->both_ways = b_ways;
}

bool Road::isBothWays() const {
	return both_ways;
}

void Road::setBothWays(bool bothWays) {
	both_ways = bothWays;
}

long long Road::getId() const {
	return id;
}

void Road::setId(long long id) {
	this->id = id;
}

const string& Road::getName() const {
	return name;
}

void Road::setName(const string& name) {
	this->name = name;
}
