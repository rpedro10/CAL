#include "Graph.h"
#include "NodeInf.h"
#include "Position.h"
#include "Road.h"
#include "graphviewer.h"
#include "Bin.h"
#include "Utilities.h"

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>

#define SOURCE_INDEX 15
#define DEST_INDEX 5760

using namespace std;

void displayGraph(Graph<NodeInf> &graph, vector<NodeInf> &path,vector<Bin>lixo){
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

		gv->setVertexLabel(graph.getVertexSet()[i]->getInfo().getId(),
				idV.str());

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

		Vertex<NodeInf>* node1;
		NodeInf nn(path[i].getId());
		node1 = graph.getVertex(nn);

	}

	for (unsigned int i = 0; i < lixo.size(); i++) {

		gv->setVertexColor(lixo[i].getId(), GREEN);
		gv->setVertexIcon(lixo[i].getId(),"bin.png");
		gv->setVertexLabel(lixo[i].getId(), "contentor");
	}
	gv->setVertexIcon(graph.getVertexSet()[SOURCE_INDEX]->getInfo().getId(), "truck.png");
	gv->setVertexIcon(graph.getVertexSet()[DEST_INDEX]->getInfo().getId(), "landfill.png");

	gv->rearrange();
	cin.ignore(1000,'\n');
	cin.clear();
	cin.get();
}

int main() {
	Graph<NodeInf> graph;
	readNodes(graph);
	readEdges(graph);
	vector<Bin> lixo = readBins();
	int num;
	cout << "Existem " << lixo.size() << "contentores cheios" << endl;
	cout << "Capacidade do camiao (em contentores)?";
	cin >> num;

	Vertex<NodeInf>* source = graph.getVertexSet()[SOURCE_INDEX];
	Vertex<NodeInf>* dest = graph.getVertexSet()[DEST_INDEX];
	Vertex<NodeInf>* temp=source;

	Vertex<NodeInf>* node_prox;
	vector<Bin> bins_visited;
	vector<Bin> all_bins;

	//graph.dijkstraShortestPath(temp->getInfo());
	//vector<NodeInf> v = graph.getPath(source->getInfo(),
		//				dest->getInfo());

	int nIte = lixo.size() / num;
	for (int k = 0; k < nIte; k++) {
		vector<NodeInf> path;
		temp=source;
		for (int j = 0; j < num; j++) {
			cout << "size:" << lixo.size() << endl;
			int index;
			double distmin = 33.33;
			for (int i = 0; i < lixo.size(); i++) {
				Vertex<NodeInf>* node1;
				node1 = graph.getVertex(lixo[i].getId());
				cout << lixo[i].getId() << endl;
				double res = calculateDistance(temp,node1);
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

			if (j == (num - 1)) {
				graph.dijkstraShortestPath(temp->getInfo());
				vector<NodeInf> v = graph.getPath(temp->getInfo(),
						dest->getInfo());
				for (unsigned int jj = 0; jj < v.size(); jj++) {
					path.push_back(v[jj]);
				}

			}
			bins_visited.push_back(lixo[index]);
			lixo.erase(lixo.begin() + index);
			temp=node_prox;
		}
		all_bins=lixo;
		all_bins.insert( all_bins.end(), bins_visited.begin(), bins_visited.end() );
		bins_visited.clear();

		displayGraph(graph, path,all_bins);
	}
	if (lixo.size() > 0) {
		//temp=source;
		int nIte = lixo.size();
		graph.dijkstraShortestPath(temp->getInfo());

		vector<NodeInf> path;
		for (int j = 0; j < nIte; j++) {
			cout << "size:" << lixo.size() << endl;
			int index;
			double distmin = 33.33;
			for (int i = 0; i < lixo.size(); i++) {
				Vertex<NodeInf>* node1;
				node1 = graph.getVertex(lixo[i].getId());
				double res=calculateDistance(temp,node1);
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

			if (j == (nIte - 1)) {
				graph.dijkstraShortestPath(temp->getInfo());
				vector<NodeInf> v = graph.getPath(temp->getInfo(),
						dest->getInfo());
				for (unsigned int jj = 0; jj < v.size(); jj++) {
					path.push_back(v[jj]);
				}

			}
			bins_visited.push_back(lixo[index]);
			lixo.erase(lixo.begin() + index);
			temp=node_prox;
		}

		all_bins=lixo;
		all_bins.insert( all_bins.end(), bins_visited.begin(), bins_visited.end() );
		bins_visited.clear();

		displayGraph(graph, path,all_bins);

	}


	return 0;
}
