/*
 * Edge.h
 *
 *  Created on: 03/05/2017
 *      Author: rpedr
 */

#ifndef SRC_ARESTA_H_
#define SRC_ARESTA_H_

using namespace std;

class Aresta {
	long long edge_id;
	long long source_id;
	long long dest_id;


public:
	Aresta(long long edge_id,long long source_id,long long dest_id);
	long long getDestId() const;
	long long getEdgeId() const;
	long long getSourceId() const;
};


#endif /* SRC_ARESTA_H_ */
