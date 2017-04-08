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
#define DEST_INDEX 1425

using namespace std;

void displayGraph(Graph<NodeInf> &graph, vector<NodeInf> &path){
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

	vector<Bin> original_lixos = readBins();
	for (unsigned int i = 0; i < original_lixos.size(); i++) {

		gv->setVertexColor(original_lixos[i].getId(), GREEN);
		gv->setVertexLabel(original_lixos[i].getId(), "contentor");
	}
	gv->setVertexColor(graph.getVertexSet()[SOURCE_INDEX]->getInfo().getId(), BLUE);
	gv->setVertexColor(graph.getVertexSet()[DEST_INDEX]->getInfo().getId(), CYAN);

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

	/**
	 for (unsigned int i = 0; i < graph.getVertexSet().size() ; i++) {

	 for(unsigned int j=0;j<graph.getVertexSet()[i]->getAdj().size();j++)
	 cout<<graph.getVertexSet()[i]->getAdj()[j].getWeight()<<endl;

	 }
	 */
	Vertex<NodeInf>* source = graph.getVertexSet()[SOURCE_INDEX];
	Vertex<NodeInf>* dest = graph.getVertexSet()[DEST_INDEX];

	Vertex<NodeInf>* node_prox;



	int nIte = lixo.size() / num;
	for (int k = 0; k < nIte; k++) {
		vector<NodeInf> path;
		for (int j = 0; j < num; j++) {
			cout << "size:" << lixo.size() << endl;
			int index;
			double distmin = 33.33;
			for (int i = 0; i < lixo.size(); i++) {
				Vertex<NodeInf>* node1;
				node1 = graph.getVertex(lixo[i].getId());
				cout << lixo[i].getId() << endl;
				double res = calculateDistance(source,node1);
				if ((res < distmin) && (res != 0)) {
					distmin = res;
					node_prox = node1;
					index = i;
				}
			}
			graph.dijkstraShortestPath(source->getInfo());
			vector<NodeInf> v = graph.getPath(source->getInfo(),
					node_prox->getInfo());

			for (unsigned int jj = 0; jj < v.size(); jj++) {
				path.push_back(v[jj]);
			}

			if (j == (num - 1)) {
				graph.dijkstraShortestPath(source->getInfo());
				vector<NodeInf> v = graph.getPath(source->getInfo(),
						dest->getInfo());
				for (unsigned int jj = 0; jj < v.size(); jj++) {
					path.push_back(v[jj]);
				}

			}
			lixo.erase(lixo.begin() + index);
		}

		displayGraph(graph, path);
	}
	if (lixo.size() > 0) {

		int nIte = lixo.size();

		vector<NodeInf> path;
		for (int j = 0; j < nIte; j++) {
			cout << "size:" << lixo.size() << endl;
			int index;
			double distmin = 33.33;
			for (int i = 0; i < lixo.size(); i++) {
				Vertex<NodeInf>* node1;
				node1 = graph.getVertex(lixo[i].getId());
				cout << lixo[i].getId() << endl;

				double long1 = node1->getInfo().getCoordinate().getLongitude();
				double long2 = source->getInfo().getCoordinate().getLongitude();
				double lat1 = node1->getInfo().getCoordinate().getLatitude();
				double lat2 = source->getInfo().getCoordinate().getLatitude();

				double u = sin((lat2 - lat1) / 2);
				double v = sin((long2 - long1) / 2);

				double res = abs(
						2.0 * 6371.0
								* asin(
										sqrt(
												u * u
														+ cos(lat1) * cos(lat2)
																* v * v)));
				cout << "res:" << res << endl;
				if ((res < distmin) && (res != 0)) {
					distmin = res;
					node_prox = node1;
					index = i;
				}
			}
			graph.dijkstraShortestPath(source->getInfo());
			vector<NodeInf> v = graph.getPath(source->getInfo(),
					node_prox->getInfo());

			for (unsigned int jj = 0; jj < v.size(); jj++) {
				path.push_back(v[jj]);
			}

			if (j == (nIte - 1)) {
				graph.dijkstraShortestPath(source->getInfo());
				vector<NodeInf> v = graph.getPath(source->getInfo(),
						dest->getInfo());
				for (unsigned int jj = 0; jj < v.size(); jj++) {
					path.push_back(v[jj]);
				}

			}
			lixo.erase(lixo.begin() + index);
		}

		displayGraph(graph, path);

	}
	/**
	 for (unsigned int i = 0; i < graph.getVertexSet().size() ; i++) {
	 cout<<"    "<<endl;
	 if(graph.getVertexSet()[i]->path == NULL)
	 cout<<"nulo";
	 }
	 */

	return 0;
}
