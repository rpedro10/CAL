/*
 * Edge.cpp
 *
 *  Created on: 03/05/2017
 *      Author: rpedr
 */

#include "Aresta.h"


Aresta::Aresta(long long edge_id,long long source_id,long long dest_id) {
	this->edge_id=edge_id;
	this->source_id=source_id;
	this->dest_id=dest_id;

}

long long Aresta::getDestId() const {
	return dest_id;
}

long long Aresta::getEdgeId() const {
	return edge_id;
}

long long Aresta::getSourceId() const {
	return source_id;
}
