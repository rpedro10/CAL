#ifndef NODEINF_H_
#define NODEINF_H_
#include <string>
#include "Position.h"
using namespace std;

class NodeInf{

	long long  id;
	Position coordinate ;
	bool contentor;


public:
	NodeInf(long long id,Position coordinates, bool bin){
		this->id=id;
		this->coordinate=coordinates;
		this->contentor=bin;

	};
	NodeInf(long long id){
			this->id=id;
		};

	 bool operator== (const NodeInf &nf1)const{
		return nf1.id==id;
	}

	long long getId(){return id;};

	Position getCoordinate(){return coordinate;};

	bool isContentor() const {
		return contentor;
	};

	void setContentor(bool contentor) {
		this->contentor = contentor;
	};


};


#endif
