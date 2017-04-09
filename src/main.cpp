#include "Utilities.h"


#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>

#define SOURCE_INDEX 15
#define DEST_INDEX 5760
#define DEST2_INDEX 2597


using namespace std;

int main() {
	Graph<NodeInf> graph;

	int num;
	int opt;
	cout << "1. Lixo do mesmo tipo " << "contentores cheios" << endl;
	cout << "2. Lixo de Tipos diferentes " << endl;
	cin >> opt;
	if (opt == 1) {
		vector<Bin> lixo = readBins("bin.txt");
		cout << "Existem " << lixo.size() << " contentores cheios." << endl;
		cout << "Capacidade do camiao (em contentores)?";
		cin >> num;
		readNodes(graph, "bin.txt");
		readEdges(graph);

		Vertex<NodeInf>* source = graph.getVertexSet()[SOURCE_INDEX];
		Vertex<NodeInf>* dest = graph.getVertexSet()[DEST_INDEX];
		Vertex<NodeInf>* dest2 = graph.getVertexSet()[DEST2_INDEX];

		computePath(lixo, num, source, graph, dest,dest2);
	}
	if (opt == 2) {
		readNodes(graph, "type_bins.txt");
		readEdges(graph);
		vector<Bin> lixo = readBins("type_bins.txt");
		Vertex<NodeInf>* source = graph.getVertexSet()[SOURCE_INDEX];
		Vertex<NodeInf>* dest = graph.getVertexSet()[DEST_INDEX];
		cout << "Existem " << lixo.size() << " contentores cheios." << endl;
		computePathDifferentTypes(lixo, source, graph, dest);
	}

	return 0;
}
