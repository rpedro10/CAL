#include "Graph.h"
#include "NodeInf.h"
#include "Position.h"
#include "Road.h"
#include "graphviewer.h"
#include "Bin.h"
#include "Parser.h"

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>


using namespace std;



int main() {
	Graph<NodeInf> graph;
	readNodes(graph);
	readEdges(graph);
	vector<Bin> lixo = readBins();

	/**
	 for (unsigned int i = 0; i < graph.getVertexSet().size() ; i++) {

	 for(unsigned int j=0;j<graph.getVertexSet()[i]->getAdj().size();j++)
	 cout<<graph.getVertexSet()[i]->getAdj()[j].getWeight()<<endl;

	 }
	 */
	Vertex<NodeInf>* source = graph.getVertexSet()[15];
	Vertex<NodeInf>* dest = graph.getVertexSet()[1425];


	Vertex<NodeInf>* node_prox;
	cout<<"size:"<<lixo.size()<<endl;

	vector<NodeInf> path;
for(int j =0;j<3;j++){
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

		double res = abs(2.0 * 6371.0* asin(sqrt(u * u + cos(lat1) * cos(lat2) * v * v)));
		cout<<"res:"<<res<<endl;
		if ((res < distmin) && (res!=0) ){
			distmin = res;
			node_prox = node1;
			index=i;
		}
	}
	graph.dijkstraShortestPath(source->getInfo());
	vector<NodeInf> v = graph.getPath(source->getInfo(), node_prox->getInfo());

	for(unsigned int jj=0;jj<v.size();jj++){
		path.push_back(v[jj]);
	}
	if(j==2){
		graph.dijkstraShortestPath(source->getInfo());
			vector<NodeInf> v = graph.getPath(source->getInfo(), dest->getInfo());
			for(unsigned int jj=0;jj<v.size();jj++){
				path.push_back(v[jj]);
			}

	}
	else
	{
	lixo.erase(lixo.begin()+index);
	cout<<"size:"<<lixo.size()<<endl;
	}

}

	long int xmin = 999999999;
	long int xmax = -9999999999999999;
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

		double lat =graph.getVertexSet()[i]->getInfo().getCoordinate().getLatitude();
		double lon =graph.getVertexSet()[i]->getInfo().getCoordinate().getLongitude();
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
	int k = 1;
	for (unsigned int i = 0; i < graph.getVertexSet().size(); i++) {
		for (unsigned int j = 0; j < graph.getVertexSet()[i]->getAdj().size();
				j++) {
			gv->addEdge(edgeID, graph.getVertexSet()[i]->getInfo().getId(),
					graph.getVertexSet()[i]->getAdj()[j].getDest()->getInfo().getId(),
					EdgeType::UNDIRECTED);
			edgeID++;
			//add road names, not advised.
			//gv->setEdgeLabel(k, graph->vertexSet[i]->adj[j]->getRoad()->getName());
			k++;
		}
	}

	for (unsigned int i = 0; i < path.size(); i++) {
		gv->setVertexColor(path[i].getId(), RED);

		Vertex<NodeInf>* node1;
		NodeInf nn(path[i].getId());
		node1 = graph.getVertex(nn);

	}

	for (unsigned int i = 0; i < lixo.size(); i++) {

		//gv->setVertexColor(lixo[i].getId(), GREEN);
		gv->setVertexLabel(lixo[i].getId(), "contentor");
	}

	gv->rearrange();
	cin.get();

	/**
	 for (unsigned int i = 0; i < graph.getVertexSet().size() ; i++) {
	 cout<<"    "<<endl;
	 if(graph.getVertexSet()[i]->path == NULL)
	 cout<<"nulo";
	 }
	 */

	return 0;
}
