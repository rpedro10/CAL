#include "Utilities.h"
#include "Search.h"

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
	string opt;
	cout << "1. Lixo do mesmo tipo " << "contentores cheios" << endl;
	cout << "2. Lixo de Tipos diferentes " << endl;
	cout << "3. Parte 2 " << endl;

	getline(cin, opt);
	if (opt == "1") {
		vector<Bin> lixo = readBins("bin.txt");
		cout << "Existem " << lixo.size() << " contentores cheios." << endl;
		cout << "Capacidade do camiao (em contentores)?";
		cin >> num;
		readNodes(graph, "bin.txt");
		readEdges(graph);

		Vertex<NodeInf>* source = graph.getVertexSet()[SOURCE_INDEX];
		Vertex<NodeInf>* dest = graph.getVertexSet()[DEST_INDEX];
		Vertex<NodeInf>* dest2 = graph.getVertexSet()[DEST2_INDEX];

		computePath(lixo, num, source, graph, dest, dest2);
	}
	if (opt == "2") {
		readNodes(graph, "type_bins.txt");
		readEdges(graph);
		vector<Bin> lixo = readBins("type_bins.txt");
		Vertex<NodeInf>* source = graph.getVertexSet()[SOURCE_INDEX];
		Vertex<NodeInf>* dest = graph.getVertexSet()[DEST_INDEX];
		cout << "Existem " << lixo.size() << " contentores cheios." << endl;
		computePathDifferentTypes(lixo, source, graph, dest);
	}
	if (opt == "3") {
		vector<Bin> lixo = readBins("bin.txt");

		readNodes(graph, "bin.txt");
		vector<Aresta> arestas = readEdges(graph);

		vector<Road> streets = readStreets();
		string s1;
		string s2;

		cout << "String a pesquisar?" << endl;

		getline(cin, s1);

		Search ss(s1, streets, arestas, lixo);
		vector<Bin> found = ss.hasDumpster();
		if (found.size() == 0) {
			cout << "Nao Existe contentor" << endl;
		} else {
			vector<NodeInf> path;
			displayGraph(graph, path, found);
		}

	}

	//Avenida da Associação Empresarial de Portugal

	return 0;

}

