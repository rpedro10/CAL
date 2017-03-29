#include "Graph.h"
#include "NodeInf.h"
#include "Position.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;
/*vector<Vertex<NodeInf>*>*/
void readNodes(char filename) {

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("node.txt");

	if (!inFile) {
		cerr << "Unable to open file node.txt";
		exit(1);   // call system to stop
	}

	string line;

	long long id = 0;
	double coordX,coordY,pointX,pointY;
	int nLine=0;
	while (getline(inFile, line)) {

		stringstream linestream(line);
		string data;

		++nLine;
		cout <<"Linha número:" << nLine<< endl;

		linestream >> id;

		getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> coordX;

		getline(linestream, data, ';');
		linestream >> coordY;

		getline(linestream, data, ';');
		linestream >> pointX;

		getline(linestream, data, ';');
		linestream >> pointY;

		cout << "id: " << id << " x1: " << coordX << " y1: " << coordY << " x2: " << pointX << " y2: " << pointY << endl;
	}

	inFile.close();

}


int main(){
	readNodes('nada');
	return 0;
}
