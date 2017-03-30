#ifndef NODEINF_H_
#define NODEINF_H_
#include <string>
#include "Position.h"
using namespace std;

class NodeInf{

	long int  id;
	Position coordinate ;

	bool contentor;
	bool full;
	int capacity;


public:
	NodeInf(long int id,Position coordinates){
		this->id=id;
		this->coordinate=coordinates;
		this->capacity=0;
		this->contentor=false;
		this->full=false;


	};
	NodeInf(long int id){
			this->id=id;
		};

	 bool operator== (const NodeInf &nf1)const{
		return nf1.id==id;
	}

	long getId(){return id;};

	Position getCoordinate(){return coordinate;};



	int getCapacity() const {
		return capacity;
	};

	void setCapacity(int capacity) {
		this->capacity = capacity;
	};

	bool isContentor() const {
		return contentor;
	};

	void setContentor(bool contentor) {
		this->contentor = contentor;
	};

	bool isFull() const {
		return full;
	};

	void setFull(bool full) {
		this->full = full;
	};


};


#endif
