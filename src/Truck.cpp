#include "Truck.h"

using namespace std;

Truck::Truck(int id,string type,int capacity){
	this->id = id;
	this->type = type;
	this->capacity=50;
}

int Truck::getId(){
	return id;
}

int Truck::getCapacity() const {
	return capacity;
}



string Truck::getType(){
	return type;
}


