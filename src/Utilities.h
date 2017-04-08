/*
 * Parser.h
 *
 *  Created on: 07/04/2017
 *      Author: rpedr
 */

#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_
#include "Utilities.h"

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define NODES_FILE  "file1.txt"
#define EDGES_FILE  "file3.txt"
#define ROADS_FILE  "file2.txt"
#define BINS_FILE  "bin.txt"


double calculateDistance(Vertex<NodeInf> *source, Vertex<NodeInf> *node1) {
	double long1 = node1->getInfo().getCoordinate().getLongitude();
				double long2 = source->getInfo().getCoordinate().getLongitude();
				double lat1 = node1->getInfo().getCoordinate().getLatitude();
				double lat2 = source->getInfo().getCoordinate().getLatitude();

				double u = sin((lat2 - lat1) / 2);
				double v = sin((long2 - long1) / 2);

				return ( abs(
						2.0 * 6371.0
								* asin(
										sqrt(
												u * u
														+ cos(lat1) * cos(lat2) * v
																* v))));


}

vector<Bin> readBins() {
	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open(BINS_FILE);

	if (!inFile) {
		cerr << "Unable to open file node.txt";
		exit(1);   // call system to stop
	}

	string line;
	string type;
	vector<Bin> contentor;

	long long node_id;

	while (getline(inFile, line)) {

		string optStr = line.substr(0, line.find(";"));

		node_id = atoi(optStr.c_str());

		line = line.substr(line.find(";") + 1, string::npos);
		type = line.substr(0, line.find(";"));

		bool found = false;
		for (int i = 0; i < contentor.size(); i++) {
			if (node_id == contentor[i].getId()) {
				found = true;
			}

		}
		if (!found) {
			Bin newBin = Bin(node_id, type);
			contentor.push_back(newBin);
		}
	}
	inFile.close();

	return contentor;

}

template<class T>
void readNodes(Graph<T> &graph) {

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open(NODES_FILE);

	if (!inFile) {
		cerr << "Unable to open file node.txt";
		exit(1);   // call system to stop
	}

	string line;
	long long id = 0;
	double coordX, coordY, pointX, pointY;
	int nLine = 0;
	vector<Bin> existingBins = readBins();

	while (getline(inFile, line)) {

		stringstream linestream(line);
		string data;
		bool isBin = false;

		++nLine;
		//cout << "Linha n�mero:" << nLine << endl;

		linestream >> id;

		getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> coordX;

		getline(linestream, data, ';');
		linestream >> coordY;

		getline(linestream, data, ';');
		linestream >> pointX;

		getline(linestream, data, ';');
		linestream >> pointY;

		//cout << "id: " << id << " x1: " << coordX << " y1: " << coordY
		//<< " x2: " << pointX << " y2: " << pointY << endl;

		Position pos(pointX, pointY);

		for (unsigned int i = 0; i < existingBins.size(); i++) {
			if (existingBins[i].getId() == id)
				isBin = true;
		}
		NodeInf nn(id, pos, isBin);

		graph.addVertex(nn);

		//cout<<"--" <<graph.getVertex(nn)->getInfo().getCoordinate().getLatitude();
	}

	inFile.close();

}
vector<Road> readStreets() {

	ifstream inFile;
	vector<Road> roads;

	//Ler o ficheiro nos.txt
	inFile.open(ROADS_FILE);

	if (!inFile) {
		cerr << "Unable to open file node.txt";
		exit(1);   // call system to stop
	}

	string line;
	string name;

	while (getline(inFile, line)) {

		string optStr = line.substr(0, line.find(";"));

		long long id = atoi(optStr.c_str());

		line = line.substr(line.find(";") + 1, string::npos);
		string nome = line.substr(0, line.find(";"));						//

		line = line.substr(line.find(";") + 1, string::npos);
		string both = line.substr(0, line.find(";") - 1);					//

		/*cout << "id: " << id << " name:" << nome << " both:" << both
		 << endl;*/
		bool both_ways;

		if (both == "False")
			both_ways = false;
		else
			both_ways = true;

		Road rr(id, nome, both_ways);

		roads.push_back(rr);
	}

	inFile.close();
	return roads;

}

template<class T>
void readEdges(Graph<T> &graph) {

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open(EDGES_FILE);

	if (!inFile) {
		cerr << "Unable to open file node.txt";
		exit(1);   // call system to stop
	}

	string line;

	long long street_id;

	long long source_id, dest_id;

	vector<Road> rr = readStreets();

	while (getline(inFile, line)) {

		stringstream linestream(line);
		string data;

		linestream >> street_id;

		getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> source_id;

		getline(linestream, data, ';');
		linestream >> dest_id;

		//cout << "id: " << street_id <<endl; //<< " source: " << source_id << " destiny: "
		//<< dest_id << endl;

		Vertex<NodeInf>* node1;
		Vertex<NodeInf>* node2;

		NodeInf nn(source_id);
		NodeInf dd(dest_id);
		//cout<<"--"<<endl;

		node1 = graph.getVertex(nn);
		node2 = graph.getVertex(dd);

		double res = calculateDistance(node1,node2);
		if(node2->getInfo().isContentor())
			res/=100;
		node1->addEdge(node2, res);

		for (unsigned int i = 0; i < rr.size(); i++) {
			//cout << rr[i].getId()<<endl;
			//cout << street_id<<endl;
			if ((rr[i].getId() == street_id) && (rr[i].isBothWays() == true)) {
				node2->addEdge(node1, res);
			}
		}


	}

	inFile.close();

}


#endif /* SRC_UTILITIES_H_ */
