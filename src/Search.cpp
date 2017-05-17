/*
 * Search.cpp
 *
 *  Created on: 03/05/2017
 *      Author: rpedr
 */

#include "Search.h"

#include "Algorithm"

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
			cout << "ID Contentor:" << bins[j].getId() << endl;
			return true;

		}

	}
	return false;
}

vector<long long> Search::findRoad() {

	vector<long long> street_ids;
	vector<Road> roads_found;

	for (unsigned int i = 0; i < roads.size(); i++) {
		if (KMP(street1, roads[i].getName()) == 1) {
			bool found = false;

			Road rr(roads[i].getId(), roads[i].getName(), true);
			street_ids.push_back(roads[i].getId());
			//	cout << roads[i].getName()  << endl;

			for (int k = 0; k < roads_found.size(); k++) {
				if (roads[i].getName() == roads_found[k].getName()) {
					found = true;
				}
			}
			if (!found) {
				roads_found.push_back(rr);
				//cout << roads[i].getName() << endl;

			}
			//return roads[i].getId();
		}
	}
	if(roads_found.size()>0){
	cout<<"Ruas encontradas com a Pesquisa Exata:"<<endl<<"-----------------------"<<endl;
		for(unsigned int i=0;i<roads_found.size();i++){
			cout<<roads_found[i].getName()<<endl;
		}
		cout<<"---------------------"<<endl;
	}
	return street_ids;
}

vector<long long> Search::aproxSearch() {

	vector<long long> street_ids;

	vector<pair<string,int>> roads_found;
	string found_aprox;

	for (unsigned int i = 0; i < roads.size(); i++) {
		// para cada partir em palavras e pesquisar cada uma delas pelo edit distance
		string temp = roads[i].getName();
		int min = 99;
		for (unsigned j = 0; j < 6; j++) {
			string optStr = temp.substr(0, temp.find(" "));
			temp = temp.substr(temp.find(" ") + 1, string::npos);
			//	cout << optStr << endl;
			if (optStr != "de" && optStr != "do" && optStr != "da") {
				if (editDistance(street1, optStr) < min) {
					min = editDistance(street1, optStr);

				}
			}
		}
		//cout << min << endl;
		if (min <= 4) {
			bool found = false;
			street_ids.push_back(roads[i].getId());
			for (int k = 0; k < roads_found.size(); k++) {
				string ss=roads_found[k].first;
				if (roads[i].getName() == ss) {
					found = true;
				}
			}
			if (!found) {
				//Road rr(roads[i].getId(), roads[i].getName(), true);
				string name=roads[i].getName();
				roads_found.push_back(make_pair(name,min));
				//cout << roads[i].getName() << endl;
			}
		}

	}
	sort(roads_found.begin(), roads_found.end(), [](const std::pair<string,int> &left, const std::pair<string,int> &right) {
	    return left.second < right.second;
	});

	cout<<"Ruas encontradas com a Pesquisa Aproximada:"<<endl<<"-----------------------"<<endl;
	for(unsigned int i=0;i<roads_found.size();i++){
		cout<<roads_found[i].first<< " -- dist:"<<roads_found[i].second<<endl;

	}
	cout<<endl;


	return street_ids;
}

bool Search::hasDumpster() { //TODO dizer em que rua o contentor foi encontrado (no caso de "Dinis" existem 5 ruas diferentes)
	vector<long long> streets = findRoad();

	if (streets.size() == 0) {
		cout << "---------------------"<<endl<<"Pesquisa exata falhou com: " << street1 << endl<<"----------------"<<endl;

		streets = aproxSearch();

		// todo funcao que faz a pesquisa aproximada  ( algoritmo dado nos slides ja feito ,
		// falta funcao que compara com todas as ruas e encontra a mais parecida
		//return false;

		if (streets.size() == 0) {
			cout << "Pesquisa aproximada falhou !!(<5)" << endl;
			return false;
		}

	}
	bool found =false;

	//cout << "existem x Edge-ids : " << streets.size() << endl;

	for (unsigned int i = 0; i < arestas.size(); i++) {
		for (unsigned int j = 0; j < streets.size(); j++) {
			if ((streets[j] == arestas[i].getEdgeId())
					&& (isDumpster(arestas[i].getSourceId()) == true
							|| isDumpster(arestas[i].getDestId() == true))) {
				Road rr = getRoad(arestas[i].getEdgeId());
				cout << "Foi encontrado: " << rr.getName()
						<< endl;
				cout << "Aresta com id:" << arestas[i].getEdgeId() << endl<<endl;
				found =true;
				//return true;
			}
		}
	}
	return found;

}

unsigned int Search::editDistance(string &pattern, string &text) { // algoritmo para pesquisa aproximada
	int n = text.length();
	vector<int> d(n + 1);
	int old, neww;
	for (int j = 0; j <= n; j++)
		d[j] = j;
	int m = pattern.length();
	for (int i = 1; i <= m; i++) {
		old = d[0];
		d[0] = i;
		for (int j = 1; j <= n; j++) {
			if (pattern[i - 1] == text[j - 1])
				neww = old;
			else {
				neww = min(old, d[j]);
				neww = min(neww, d[j - 1]);
				neww = neww + 1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}

Road Search::getRoad(long long edge_id) {
	for (unsigned int i = 0; i < roads.size(); i++) {
		if (edge_id == roads[i].getId())
			return roads[i];
	}

}

