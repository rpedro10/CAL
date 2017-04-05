#include "Bin.h"

using namespace std;

Bin::Bin(int id,string type){
	this->id = id;
	this->type = type;
}

int Bin::getId(){
	return id;
}

string Bin::getType(){
	return type;
}
