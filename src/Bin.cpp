#include "Bin.h"

using namespace std;

Bin::Bin(int id,string type){
	this->id = id;
	this->type = type;
	this->max_capacity=10;
}

int Bin::getId(){
	return id;
}

int Bin::getMaxCapacity() const {
	return max_capacity;
}

void Bin::setMaxCapacity(int maxCapacity) {
	max_capacity = maxCapacity;
}

string Bin::getType(){
	return type;
}
