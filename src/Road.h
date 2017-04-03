/*
 * road.h
 *
 *  Created on: 29/03/2017
 *      Author: rpedr
 */

#ifndef SRC_ROAD_H_
#define SRC_ROAD_H_

#include <string>
#include "Position.h"
using namespace std;

class Road{

	long int id;
	string name;
	bool both_ways;



public:
	Road(long int _id,string _name,bool b_ways){
		this->id=_id;
		this->name=_name;
		this->both_ways=b_ways;
	}

	bool isBothWays() const {
		return both_ways;
	}

	void setBothWays(bool bothWays) {
		both_ways = bothWays;
	}

	long int getId() const {
		return id;
	}

	void setId(long int id) {
		this->id = id;
	}

	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}
};

#endif /* SRC_ROAD_H_ */
