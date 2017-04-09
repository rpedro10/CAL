#ifndef NODEINF_H_
#define NODEINF_H_
#include <string>
#include "Position.h"
using namespace std;

class NodeInf {

	long long id;
	Position coordinate;
	bool contentor;

public:
	NodeInf(long long id, Position coordinates, bool bin);
	NodeInf(long long id);

	bool operator==(const NodeInf &nf1) const;
	bool operator!=(const NodeInf &nf1) const;
	long long getId();

	Position getCoordinate();
	bool isContentor() const;
	void setContentor(bool contentor);
};

#endif
