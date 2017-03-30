#include "Bin.h"

using namespace std;

Bin::Bin(int id,string type,int capacity){
	this->id = id;
	this->type = type;
}

int Bin::getId(){
	return id;
}

string Bin::getType(){
	return type;
}



bool Bin::isFull(){
	return full;
}
