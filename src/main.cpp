#include "Graph.h"
#include "NodeInf.h"
#include "Position.h"
#include "Road.h"
#include "graphviewer.h"
#include "Bin.h"

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>

Graph<NodeInf> graph;


using namespace std;


vector<Bin> readBins() {
	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("bin.txt");

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


		cout << "node_id: " << node_id << " type:" << type <<endl;
		Bin newBin = Bin(node_id,type);
		contentor.push_back(newBin);
	}
	inFile.close();

	return contentor;

}

void readNodes() {

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("node.txt");

	if (!inFile) {
		cerr << "Unable to open file node.txt";
		exit(1);   // call system to stop
	}

	string line;
	long long  id = 0;
	double coordX, coordY, pointX, pointY;
	int nLine = 0;
	vector<Bin> existingBins = readBins();

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

		for (unsigned int i = 0; i < existingBins.size();i++){
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
	inFile.open("roads.txt");

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

void readEdges() {

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("edges.txt");

	if (!inFile) {
		cerr << "Unable to open file node.txt";
		exit(1);   // call system to stop
	}

	string line;

	long long street_id;

	long long source_id, dest_id;

	vector<Road>rr = readStreets();

	int check = 0;
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
		//cout << node1->getInfo().getId();
		/*if(graph.getVertex(nn) == NULL)
			cout<<"nulll"<<endl;*/

		// calcular distancia (peso)
		//cout<<node1->getInfo().getId()<<endl;




		double long1 = node1->getInfo().getCoordinate().getLongitude();


		double long2 = node2->getInfo().getCoordinate().getLongitude();
		double lat1 = node1->getInfo().getCoordinate().getLatitude();
		double lat2 = node2->getInfo().getCoordinate().getLatitude();
		//cout<<"--"<< lat2<<endl;


		double u = sin((lat2 - lat1) / 2);
		double v = sin((long2 - long1) / 2);

		double res = 2.0 * 6371.0* asin(sqrt(u * u + cos(lat1) * cos(lat2) * v * v));

	//	if(res==0.0)
	//	res+=0.0001;


		if(node2->getInfo().isContentor())
			res= res/100000;

		node1->addEdge(node2, res);



		for (unsigned int i = 0; i < rr.size(); i++)
		{
			//cout << rr[i].getId()<<endl;
			//cout << street_id<<endl;
			if ( ( rr[i].getId() == street_id ) && (rr[i].isBothWays() == true))
			{
				check++;
				node2->addEdge(node1, res);
			}
		}


		//cout << res << endl;

	}

	inFile.close();

}


int main() {

	//vector<Road>rr = readStreets();
	readNodes();
	//cout << "pla" << endl;
	//cout << "----" << graph.getVertexSet()[0]->getInfo().getId();
	readEdges();
	vector<Bin> lixo = readBins();


	for (unsigned int i = 0; i < graph.getVertexSet().size() ; i++) {

		for(unsigned int j=0;j<graph.getVertexSet()[i]->getAdj().size();j++)
			cout<<graph.getVertexSet()[i]->getAdj()[j].getWeight()<<endl;

	}

	//25504120

	graph.dijkstraShortestPath(graph.getVertexSet()[5210]->getInfo());

	vector<NodeInf>v = graph.getPath(graph.getVertexSet()[5210]->getInfo(),graph.getVertexSet()[5296]->getInfo());



	cout<<v.size()<<endl;
	for(int i=0;i<v.size();i++){
		cout<<v[i].getId()<<endl;
	}

	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);
	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	double minLat = 9999;
	double minLon = 9999;
	double maxLat = -9999;
	double maxLon = -9999;
	//y is latitude
	//x is longitude

	for (unsigned int i = 0; i < graph.getVertexSet().size(); i++) {
		double nodeLat =
				graph.getVertexSet()[i]->getInfo().getCoordinate().getLatitude();
		double nodeLon =
				graph.getVertexSet()[i]->getInfo().getCoordinate().getLongitude();
		//cout << " |nodelat" << nodeLat << " |nodeLon" << nodeLon << endl;
		if (nodeLat < minLat)
			minLat = nodeLat;
		if (nodeLat > maxLat)
			maxLat = nodeLat;
		if (nodeLon < minLon)
			minLon = nodeLon;
		if (nodeLat > maxLon)
			maxLon = nodeLat;
	}

	//cout << " |minlat" << minLat << " |maxlat" << maxLat << " |minlon" << minLon<< " |maxlon" << minLon << endl;

	for (unsigned int i = 0; i < graph.getVertexSet().size(); i++) {
		double lat = graph.getVertexSet()[i]->getInfo().getCoordinate().getLatitude();
		double lon = graph.getVertexSet()[i]->getInfo().getCoordinate().getLongitude();
		int x,y;
		x = floor(((lon-minLon)*4200/(maxLon-minLon)));
		y = floor(((lat-minLat)*3183/(maxLat-minLat)));

		gv->addNode(graph.getVertexSet()[i]->getInfo().getId(),x,y);
		long long idPrint = graph.getVertexSet()[i]->getInfo().getId();
		stringstream idV;
		idV << idPrint;
		gv->setVertexLabel(graph.getVertexSet()[i]->getInfo().getId(), idV.str());
	}
	/*
	struct foo{
		int

	};*/
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

	for (unsigned int i = 0; i < v.size(); i++)
	{
		gv->setVertexColor(v[i].getId(), RED);
/*
		Vertex<NodeInf>* node1;
		NodeInf nn(v[i].getId());
		node1 = graph.getVertex(nn);

		for (int i = 0; i < edgeID;i++)
		{
			gv->setEdgeColor(path[i]->adj[k]->getEdgeID(), RED);
		}
*/
	}

	/*
	for (unsigned int i = 0; i < lixo.size(); i++) {

		gv->setVertexColor(lixo[i].getId(), GREEN);
	}*/


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
