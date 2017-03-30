#include "Truck.h"

using namespace std;

Truck::Truck(int id,string type,int capacity){
	this->id = id;
	this->type = type;
}

int Truck::getId(){
	return id;
}

string Truck::getType(){
	return type;
}


