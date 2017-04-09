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

	long long id;
	string name;
	bool both_ways;

public:
	Road(long long _id,string _name,bool b_ways);
	bool isBothWays() const;
	void setBothWays(bool bothWays);
	long long getId() const;
	void setId(long long id);
	const string& getName() const;
	void setName(const string& name);
};

#endif /* SRC_ROAD_H_ */
