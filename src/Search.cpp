/*
 * Search.cpp
 *
 *  Created on: 03/05/2017
 *      Author: rpedr
 */

#include "Search.h"

Search::Search(string st1, vector<Road> roads, vector<Aresta> arestas,
		vector<Bin> bins) {
	this->street1 = st1;
	this->roads = roads;
	this->arestas = arestas;
	this->bins = bins;
}

const vector<Road>& Search::getRoads() const {
	return roads;
}

const string& Search::getStreet1() const {
	return street1;
}

void Search::preKMP(string pattern, int f[]) {
	int m = pattern.length(), k;
	f[0] = -1;
	for (int i = 1; i < m; i++) {
		k = f[i - 1];
		while (k >= 0) {
			if (pattern[k] == pattern[i - 1])
				break;
			else
				k = f[k];
		}
		f[i] = k + 1;
	}
}

//check whether target string contains pattern
bool Search::KMP(string pattern, string target) {


	int m = pattern.length();
	int n = target.length();
	int f[m];
	preKMP(pattern, f);
	int i = 0;
	int k = 0;
	while (i < n) {
		if (k == -1) {
			i++;
			k = 0;
		} else if (target[i] == pattern[k]) {
			i++;
			k++;
			if (k == m)
				return 1;
		} else
			k = f[k];
	}
	return 0;
}

bool Search::isDumpster(long long id) {

	for (unsigned int j = 0; j < bins.size(); j++) {
		if (id == bins[j].getId()) {
			cout<<"id do contentor:"<<bins[j].getId()<<endl;
			return true;

		}

	}
	return false;
}

vector<Road> Search::findRoad() {

	vector<Road> roads_found;


	for (unsigned int i = 0; i < roads.size(); i++) {
		if (KMP(street1,roads[i].getName()) == 1) {
			 bool found=false;

			Road rr(roads[i].getId(),roads[i].getName(),true);
		//	cout << roads[i].getName() << "-----" << endl;

			for(int k=0;k<roads_found.size();k++){
				if(roads[i].getName()==roads_found[k].getName()){
					found=true;

				}
			}
			if(!found){
				roads_found.push_back(rr);
				cout << roads[i].getName() << "-----" << endl;

			}


			//return roads[i].getId();
		}
	}

	return roads_found;
}

bool Search::hasDumpster() { //TODO dizer em que rua o contentor foi encontrado (no caso de "Dinis" existem 5 ruas diferentes)
	vector<Road> streets = findRoad();

	if(streets.size()==0){
			cout << "A rua: " << street1 << " nao existe" << endl;

			// todo funcao que faz a pesquisa aproximada  ( algoritmo dado nos slides ja feito ,
				// falta funcao que compara com todas as ruas e encontra a mais parecida
			return false;
		}


	cout << "existem x ruas : " << streets.size() << endl;

	vector<long long> indexes;



	for (unsigned int i = 0; i < arestas.size(); i++) {
		for(unsigned int j=0 ;j<streets.size();j++){
			if (streets[j].getId() == arestas[i].getEdgeId()) {
						//cout << "aqui1---" << index1 << endl;
						indexes.push_back(i);

					}
		}
	}

	for (unsigned int j = 0; j < indexes.size(); j++) {

		int pos = indexes[j];

		if (isDumpster(arestas[pos].getSourceId()) ||  isDumpster(arestas[pos].getDestId()) ) {
			cout<<"pos: "<<pos<<endl;
			cout<<" Encontrado na aresta com id:"<< arestas[pos].getEdgeId()<< " -- "<<endl;
				//	"Nome da rua: "<< streets[pos].getName()<<endl;
			return true;
		}

	}

}

unsigned int Search::editDistance(string &pattern, string &text){   // algoritmo para pesquisa aproximada
	unsigned int distance[text.length()+1];
	unsigned int oldDistance, newDistance;

	for(unsigned int i=0;i<pattern.length();i++){
		distance[i]=i;
	}
	for(unsigned int i=1;i<=pattern.length();i++){
		oldDistance=distance[0];
		distance[0]=i;

		for(unsigned int j=1;j<text.length();j++){
			if(tolower(pattern[i-1])==tolower(text[j-1]))
				newDistance=oldDistance;
			else{
				newDistance =  min(oldDistance,min(distance[j],distance[j-1]));
				newDistance++;
			}
			oldDistance=distance[j];
			distance[j]=newDistance;
		}
	}
	return distance[text.length()];
}

