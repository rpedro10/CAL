#include "NodeInf.h"

NodeInf::NodeInf(long long id, Position coordinates, bool bin) {
	this->id = id;
	this->coordinate = coordinates;
	this->contentor = bin;

}
;
NodeInf::NodeInf(long long id) {
	this->id = id;
}
;

bool NodeInf::operator==(const NodeInf &nf1) const {
	return nf1.id == id;
}
bool NodeInf::operator!=(const NodeInf &nf1) const {
	return nf1.id != id;
}

long long NodeInf::getId() {
	return id;
}
;

Position NodeInf::getCoordinate() {
	return coordinate;
}
;

bool NodeInf::isContentor() const {
	return contentor;
}
;

void NodeInf::setContentor(bool contentor) {
	this->contentor = contentor;
}
;
