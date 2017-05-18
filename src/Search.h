/*
 * Search.h
 *
 *  Created on: 03/05/2017
 *      Author: rpedr
 */

#ifndef SRC_SEARCH_H_
#define SRC_SEARCH_H_

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <map>
#include "Bin.h"
#include "Aresta.h"

#include "Graph.h"
#include "NodeInf.h"
#include "graphviewer.h"
#include "Road.h"
#include "Position.h"
using namespace std;


// dar uma rua e verificar se algum dos contentores encontrados nessa rua é contentor


class Search {

	string street1;
	vector<Road>roads;
	vector<Aresta>arestas;
	vector<Bin>bins;

public:

	Search(string st1, vector<Road>roads,vector<Aresta>ar,vector<Bin>bins);
	bool KMP(string pattern, string target);
	void preKMP(string pattern, int f[]);
	const vector<Road>& getRoads() const;
	const string& getStreet1() const;
	bool isDumpster(long long id);
	vector<long long> findRoad();
	vector<Bin> hasDumpster();
	unsigned int editDistance( string &pattern, string &text);
	vector<long long> aproxSearch();
	Road getRoad(long long edge_id);


};


#endif /* SRC_SEARCH_H_ */
