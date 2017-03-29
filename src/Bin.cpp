#include "Bin.h"

using namespace std;

Bin::Bin(int id,string type,int capacity){
	this->id = id;
	this->type = type;
	this->capacity = capacity;
}

int Bin::getId(){
	return id;
}

string Bin::getType(){
	return type;
}

int Bin::getCapacity(){
	return capacity;
}

bool Bin::isFull(){
	return full;
}
