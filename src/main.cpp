#include "Graph.h"
#include "NodeInf.h"
#include "Position.h"
#include "Road.h"
#include "graphviewer.h"

#include <fstream>
#include <sstream>
#include <stdlib.h>

Graph<NodeInf> graph;


using namespace std;

void readNodes(char filename) {

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("node.txt");

	if (!inFile) {
		cerr << "Unable to open file node.txt";
		exit(1);   // call system to stop
	}

	string line;

	 long int  id = 0;
	double coordX, coordY, pointX, pointY;
	int nLine = 0;
	while (getline(inFile, line)) {

		stringstream linestream(line);
		string data;

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

		NodeInf nn(id, pos);


		graph.addVertex(nn);

		//cout<<"--" <<graph.getVertex(nn)->getInfo().getCoordinate().getLatitude();
	}

	inFile.close();

}
vector<Road> readStreets(char filename) {

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

		long int id = atoi(optStr.c_str());

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

void readEdges(char filename) {

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("edges.txt");

	if (!inFile) {
		cerr << "Unable to open file node.txt";
		exit(1);   // call system to stop
	}

	string line;

	long int street_id;

	long int source_id, dest_id;

	vector<Road>rr = readStreets('nda');

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

	//vector<Road>rr = readStreets('nda');
	readNodes('nada');
	//cout << "pla" << endl;
	//cout << "----" << graph.getVertexSet()[0]->getInfo().getId();
	readEdges('na');

	return 0;
}
