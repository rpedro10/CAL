#include "Truck.h"

using namespace std;

Truck::Truck(string type,int capacity){
	this->type = type;
	this->capacity = capacity;
}

string Truck::getType(){
	return type;
}

int Truck::getCapacity(){
	return capacity;
}
