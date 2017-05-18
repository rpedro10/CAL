/*
 * Utilities.h
 *
 *  Created on: 07/04/2017
 *      Author: rpedr
 */

#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <map>

#include "Aresta.h"
#include "Bin.h"
#include "Graph.h"
#include "NodeInf.h"
#include "graphviewer.h"
#include "Road.h"
#include "Position.h"


using namespace std;

#define NODES_FILE  "file1.txt"
#define EDGES_FILE  "file3.txt"
#define ROADS_FILE  "file2.txt"
#define BINS_FILE  "bin.txt"
#define DEST2_INDEX 2597

#define SOURCE_INDEX 15
#define DEST_INDEX 5760

/**
 * Recebe 2 nós e calcula a distância de um ao outro a partir das coordenadas.
 *
 *@param source primeiro nó
 *@param node1 segundo nó
 */
double calculateDistance(Vertex<NodeInf> *source, Vertex<NodeInf> *node1) {
	double long1 = node1->getInfo().getCoordinate().getLongitude();
	double long2 = source->getInfo().getCoordinate().getLongitude();
	double lat1 = node1->getInfo().getCoordinate().getLatitude();
	double lat2 = source->getInfo().getCoordinate().getLatitude();

	double u = sin((lat2 - lat1) / 2);
	double v = sin((long2 - long1) / 2);

	return (abs(
			2.0 * 6371.0 * asin(sqrt(u * u + cos(lat1) * cos(lat2) * v * v))));

};

/**
 *	Usado para representar uma grafo recorrendo ao graphviewer e caminho calculado.
 *
 * @param graph Grafo a representar.
 * @param path Caminho a pintar.
 */
void displayGraph(Graph<NodeInf> &graph, vector<NodeInf> &path,
		vector<Bin> lixo) {
	long int xmin = 999999999;
	long int xmax = -99999999;
	long int ymin = 999999999;
	long int ymax = -1;

	for (unsigned int i = 0; i < graph.getVertexSet().size(); i++) {
		double lat =
				graph.getVertexSet()[i]->getInfo().getCoordinate().getLatitude();
		double lon =
				graph.getVertexSet()[i]->getInfo().getCoordinate().getLongitude();
		int x, y;
		x = -6370000 * cos(lat) * sin(lon);
		y = 6370000 * sin(lat);

		if (x > xmax)
			xmax = x;
		if (x < xmin)
			xmin = x;
		if (y > ymax)
			ymax = y;
		if (y < ymin)
			ymin = y;
	}
	GraphViewer *gv = new GraphViewer(xmax - xmin, ymax - ymin, false);
	gv->createWindow(xmax - xmin, ymax - ymin);
	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	gv->setBackground("map.png");

	for (unsigned int i = 0; i < graph.getVertexSet().size(); i++) {

		double lat =
				graph.getVertexSet()[i]->getInfo().getCoordinate().getLatitude();
		double lon =
				graph.getVertexSet()[i]->getInfo().getCoordinate().getLongitude();
		int x, y;
		x = -6370000 * cos(lat) * sin(lon);
		y = 6370000 * sin(lat);

		gv->addNode(graph.getVertexSet()[i]->getInfo().getId(),
				round((x - xmin) * 0.5), round((y - ymin) * 0.5));
		long long idPrint = graph.getVertexSet()[i]->getInfo().getId();
		stringstream idV;
		idV << idPrint;
		//25632467;geral;
		// 137994720;geral;
		//
		gv->setVertexLabel(graph.getVertexSet()[i]->getInfo().getId(),"-");

	}

	int edgeID = 0;
	for (unsigned int i = 0; i < graph.getVertexSet().size(); i++) {
		for (unsigned int j = 0; j < graph.getVertexSet()[i]->getAdj().size();
				j++) {
			gv->addEdge(edgeID, graph.getVertexSet()[i]->getInfo().getId(),
					graph.getVertexSet()[i]->getAdj()[j].getDest()->getInfo().getId(),
					EdgeType::UNDIRECTED);
			edgeID++;
			//add road names, not advised.
			//gv->setEdgeLabel(k, graph->vertexSet[i]->adj[j]->getRoad()->getName());


		}
	}

	for (unsigned int i = 0; i < path.size(); i++) {
		gv->setVertexColor(path[i].getId(), RED);
	}

	for (unsigned int i = 0; i < lixo.size(); i++) {

		gv->setVertexColor(lixo[i].getId(), GREEN);
		gv->setVertexIcon(lixo[i].getId(), "bin.png");
		//gv->setVertexLabel(lixo[i].getId(), lixo[i].getType());

	}
	gv->setVertexIcon(graph.getVertexSet()[SOURCE_INDEX]->getInfo().getId(),
			"truck.png");
	gv->setVertexIcon(graph.getVertexSet()[DEST_INDEX]->getInfo().getId(),
			"landfill.png");
	gv->setVertexIcon(graph.getVertexSet()[DEST2_INDEX]->getInfo().getId(),
			"landfill.png");

	gv->rearrange();
	cout<<"Premir Enter para continuar." <<endl;
	cin.ignore(1000, '\n');
	cin.clear();
	cin.get();
};

int getEdgeId(vector<Aresta> arestas, long long source, long long dest){

	for (unsigned int i=0; i<arestas.size();i++){
		if(arestas[i].getDestId()==dest && source ==arestas[i].getSourceId() ){
			return i;
		}
	}
};

void displayGraph(Graph<NodeInf> &graph, vector<NodeInf> &path,
		vector<Bin> lixo,vector<Aresta> arestas,vector<Road> streets) {
	long int xmin = 999999999;
	long int xmax = -99999999;
	long int ymin = 999999999;
	long int ymax = -1;

	for (unsigned int i = 0; i < graph.getVertexSet().size(); i++) {
		double lat =
				graph.getVertexSet()[i]->getInfo().getCoordinate().getLatitude();
		double lon =
				graph.getVertexSet()[i]->getInfo().getCoordinate().getLongitude();
		int x, y;
		x = -6370000 * cos(lat) * sin(lon);
		y = 6370000 * sin(lat);

		if (x > xmax)
			xmax = x;
		if (x < xmin)
			xmin = x;
		if (y > ymax)
			ymax = y;
		if (y < ymin)
			ymin = y;
	}
	GraphViewer *gv = new GraphViewer(xmax - xmin, ymax - ymin, false);
	gv->createWindow(xmax - xmin, ymax - ymin);
	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	gv->setBackground("map.png");

	for (unsigned int i = 0; i < graph.getVertexSet().size(); i++) {

		double lat =
				graph.getVertexSet()[i]->getInfo().getCoordinate().getLatitude();
		double lon =
				graph.getVertexSet()[i]->getInfo().getCoordinate().getLongitude();
		int x, y;
		x = -6370000 * cos(lat) * sin(lon);
		y = 6370000 * sin(lat);

		gv->addNode(graph.getVertexSet()[i]->getInfo().getId(),
				round((x - xmin) * 0.5), round((y - ymin) * 0.5));
		long long idPrint = graph.getVertexSet()[i]->getInfo().getId();
		stringstream idV;
		idV << idPrint;
		gv->setVertexLabel(graph.getVertexSet()[i]->getInfo().getId(),"-");


	}



	int edgeID = 0;
	for (unsigned int i = 0; i < graph.getVertexSet().size(); i++) {
		for (unsigned int j = 0; j < graph.getVertexSet()[i]->getAdj().size();
				j++) {
			gv->addEdge(edgeID, graph.getVertexSet()[i]->getInfo().getId(),
					graph.getVertexSet()[i]->getAdj()[j].getDest()->getInfo().getId(),
					EdgeType::UNDIRECTED);
			edgeID++;
			//add road names, not advised.
			//gv->setEdgeLabel(k, graph->vertexSet[i]->adj[j]->getRoad()->getName());


		}
	}




for (unsigned int i = 0; i < graph.getVertexSet().size(); i++) {
		for (unsigned int j = 0; j < graph.getVertexSet()[i]->getAdj().size();
				j++) {
			int ss;
					ss=getEdgeId(arestas,graph.getVertexSet()[i]->getInfo().getId()	,graph.getVertexSet()[i]->getAdj()[j].getDest()->getInfo().getId());
					string name;
					for(unsigned int k=0; k<streets.size();k++){
						if(streets[k].getId()== arestas[ss].getEdgeId()){
							name = streets[k].getName();

						}
					}

					gv->setEdgeLabel(ss,name);
			}

		}



	for (unsigned int i = 0; i < lixo.size(); i++) {

		gv->setVertexColor(lixo[i].getId(), GREEN);
		gv->setVertexIcon(lixo[i].getId(), "bin.png");

	}

	gv->rearrange();
		cout<<"Premir Enter para continuar." <<endl;
		cin.ignore(1000, '\n');
		cin.clear();
		cin.get();

};


/**
 * Calcula o caminho que os camião(ões) devem tomar de maneira visitar todos os caixotes, tomando o caminho mais curto póssivel.
 *
 *@param lixo Vector que guarda a localização dos caixotes de lixo.
 *@param num  Capacidade de um camião.
 *@param source Nó onde se localiza a garagem.
 *@param graph Grafo pertinente ao problema.
 *@param dest Nó onde se localiza o primeiro aterro.
 *@param dest2 Nó onde se localiza o segundo aterro.
 */
void computePath(vector<Bin>&lixo, int num, Vertex<NodeInf>* source,
	Graph<NodeInf> graph, Vertex<NodeInf>* dest, Vertex<NodeInf>* dest2) {
	Vertex<NodeInf>* temp = source;
	Vertex<NodeInf>* node_prox;
	vector<Bin> bins_visited;
	vector<Bin> all_bins;

	int nIte = lixo.size() / num;
	for (int k = 0; k < nIte; k++) {
		vector<NodeInf> path;
		temp = source;
		for (int j = 0; j < num; j++) {
			//cout << "size:" << lixo.size() << endl;
			int index;
			double distmin = 33.33;
			for (unsigned int i = 0; i < lixo.size(); i++) {
				Vertex<NodeInf>* node1;
				node1 = graph.getVertex(lixo[i].getId());
				//cout << lixo[i].getId() << endl;
				double res = calculateDistance(temp, node1);
				if ((res < distmin) && (res != 0)) {
					distmin = res;
					node_prox = node1;
					index = i;
				}
			}
			graph.dijkstraShortestPath(temp->getInfo());
			vector<NodeInf> v = graph.getPath(temp->getInfo(),
					node_prox->getInfo());

			for (unsigned int jj = 0; jj < v.size(); jj++) {
				path.push_back(v[jj]);
			}
			temp = node_prox;

			if (j == (num - 1)) {
				graph.dijkstraShortestPath(temp->getInfo());
				vector<NodeInf> v;
				double dist1 = calculateDistance(temp, dest);
				double dist2 = calculateDistance(temp, dest2);
				if (dist1 < dist2) {
					v = graph.getPath(temp->getInfo(),
							dest->getInfo());
				}
				else {
					v = graph.getPath(temp->getInfo(),
							dest2->getInfo());
				}

				for (unsigned int jj = 0; jj < v.size(); jj++) {
					path.push_back(v[jj]);
				}

			}
			bins_visited.push_back(lixo[index]);
			lixo.erase(lixo.begin() + index);
		}
		all_bins = lixo;
		all_bins.insert(all_bins.end(), bins_visited.begin(),
				bins_visited.end());
		bins_visited.clear();

		displayGraph(graph, path, all_bins);
	}
	if (lixo.size() > 0) {
		temp = source;
		int nIte = lixo.size();
		graph.dijkstraShortestPath(temp->getInfo());

		vector<NodeInf> path;
		for (int j = 0; j < nIte; j++) {
			//cout << "size:" << lixo.size() << endl;
			int index;
			double distmin = 33.33;
			for (unsigned int i = 0; i < lixo.size(); i++) {
				Vertex<NodeInf>* node1;
				node1 = graph.getVertex(lixo[i].getId());
				double res = calculateDistance(temp, node1);
				if ((res < distmin) && (res != 0)) {
					distmin = res;
					node_prox = node1;
					index = i;
				}
			}
			graph.dijkstraShortestPath(temp->getInfo());
			vector<NodeInf> v = graph.getPath(temp->getInfo(),
					node_prox->getInfo());

			for (unsigned int jj = 0; jj < v.size(); jj++) {
				path.push_back(v[jj]);
			}
			temp = node_prox;
			if (j == (nIte - 1)) {
				graph.dijkstraShortestPath(temp->getInfo());
				vector<NodeInf> v;
				double dist1 = calculateDistance(temp, dest);
				double dist2 = calculateDistance(temp, dest2);
				if (dist1 < dist2)
					v = graph.getPath(temp->getInfo(),
							dest->getInfo());
				else
					v = graph.getPath(temp->getInfo(),
							dest2->getInfo());

				for (unsigned int jj = 0; jj < v.size(); jj++) {
					path.push_back(v[jj]);
				}

			}
			bins_visited.push_back(lixo[index]);
			lixo.erase(lixo.begin() + index);
		}

		all_bins = lixo;
		all_bins.insert(all_bins.end(), bins_visited.begin(),
				bins_visited.end());
		bins_visited.clear();

		displayGraph(graph, path, all_bins);

	}

};

/**
 * Calcula o caminho que os camião(ões) devem tomar de maneira visitar todos os caixotes, tomando em conta
 * o caminho mais curto póssivel e que o lixo pode ter vários tipos.
 *
 *@param lixo Vector que guarda a localização dos caixotes de lixo.
 *@param source Nó onde se localiza a garagem.
 *@param graph Grafo pertinente ao problema.
 *@param dest Nó onde se localiza o primeiro aterro.
 */
void computePathDifferentTypes(vector<Bin>&lixo, Vertex<NodeInf>*& source,
	Graph<NodeInf> &graph, Vertex<NodeInf>* &dest) {
	Vertex<NodeInf>* temp = source;
	Vertex<NodeInf>* node_prox;


	vector<Bin> industrial;
	vector<Bin> domestico;


	for (unsigned int p = 0; p < lixo.size(); p++) {
		if (lixo[p].getType() == "industrial") {
			industrial.push_back(lixo[p]);
		} else
			domestico.push_back(lixo[p]);
	}
	//cout << domestico.size();

	vector<NodeInf> path;
	temp = source;

	for (unsigned t = 0; t < domestico.size(); t++) {
		double distmin = 33.33;
		int index;
		for (unsigned int i = 0; i < domestico.size(); i++) {
			Vertex<NodeInf>* node1;
			node1 = graph.getVertex(domestico[i].getId());
			//cout << domestico[i].getId() << endl;
			double res = calculateDistance(temp, node1);
			if ((res < distmin) && (res != 0)) {
				distmin = res;
				node_prox = node1;
				index = i;
			}
		}

		graph.dijkstraShortestPath(temp->getInfo());
		vector<NodeInf> v = graph.getPath(temp->getInfo(),
				node_prox->getInfo());

		for (unsigned int jj = 0; jj < v.size(); jj++) {
			path.push_back(v[jj]);
		}
		temp = node_prox;

		if (t == domestico.size() - 1) {
			graph.dijkstraShortestPath(temp->getInfo());
			vector<NodeInf> v = graph.getPath(temp->getInfo(), dest->getInfo());
			for (unsigned int jj = 0; jj < v.size(); jj++) {
				path.push_back(v[jj]);
			}

		}
		lixo.erase(lixo.begin() + index);
		temp = node_prox;
	}

	displayGraph(graph, path, domestico);
	path.clear();
	temp = source;

	for (unsigned t = 0; t < industrial.size(); t++) {
		double distmin = 33.33;
		int index;
		for (unsigned int i = 0; i < industrial.size(); i++) {
			Vertex<NodeInf>* node1;
			node1 = graph.getVertex(industrial[i].getId());
			//cout << domestico[i].getId() << endl;
			double res = calculateDistance(temp, node1);
			if ((res < distmin) && (res != 0)) {
				distmin = res;
				node_prox = node1;
				index = i;
			}
		}

		graph.dijkstraShortestPath(temp->getInfo());
		vector<NodeInf> v = graph.getPath(temp->getInfo(),
				node_prox->getInfo());

		for (unsigned int jj = 0; jj < v.size(); jj++) {
			path.push_back(v[jj]);
		}
		temp = node_prox;

		if (t == industrial.size() - 1) {
			graph.dijkstraShortestPath(temp->getInfo());
			vector<NodeInf> v = graph.getPath(temp->getInfo(), dest->getInfo());
			for (unsigned int jj = 0; jj < v.size(); jj++) {
				path.push_back(v[jj]);
			}

		}
		lixo.erase(lixo.begin() + index);
		temp = node_prox;
	}
	displayGraph(graph, path, industrial);

};

/**
 * Lê os caixotes do lixo existentes de um ficheiro.
 *
 * @param filename Nome do ficheiro.
 */
vector<Bin> readBins(string filename) {
	ifstream inFile;

	inFile.open(filename.c_str());

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
		for (unsigned int i = 0; i < contentor.size(); i++) {
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

};
/**
 * Lê os nós existentes de um ficheiro.
 *
 * @param graph Grafo pertinente ao problema.
 * @param filename Nome do ficheiro.
 */


template<class T>
void readNodes(Graph<T> &graph, string binfilename) {

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
	vector<Bin> existingBins = readBins(binfilename);

	while (getline(inFile, line)) {

		stringstream linestream(line);
		string data;
		bool isBin = false;

		++nLine;
		//cout << "Linha número:" << nLine << endl;

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

};

/**
 * Lê as ruas existentes de um ficheiro.
 *
 */

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

};



/**
 * Lê as arestas existentes de um ficheiro.
 *
 * @param graph Grafo pertinente ao problema.
 */
template<class T>
vector<Aresta> readEdges(Graph<T> &graph) {

	ifstream inFile;
	vector<Aresta> res;

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

		Aresta aresta= Aresta(street_id,source_id,dest_id);

		res.push_back(aresta);

		//cout << "id: " << street_id <<endl; //<< " source: " << source_id << " destiny: "
		//<< dest_id << endl;

		Vertex<NodeInf>* node1;
		Vertex<NodeInf>* node2;

		NodeInf nn(source_id);
		NodeInf dd(dest_id);
		//cout<<"--"<<endl;

		node1 = graph.getVertex(nn);
		node2 = graph.getVertex(dd);

		double res = calculateDistance(node1, node2);
		if (node2->getInfo().isContentor())
			res /= 100;
		node1->addEdge(node2, res);

		for (unsigned int i = 0; i < rr.size(); i++) {
			//cout << rr[i].getId()<<endl;
			//cout << street_id<<endl;
			if ((rr[i].getId() == street_id) && (rr[i].isBothWays() == true)) {
				node2->addEdge(node1, res);
			}
		}

	}
	return res;
	inFile.close();

};
#endif /* SRC_UTILITIES_H_ */
