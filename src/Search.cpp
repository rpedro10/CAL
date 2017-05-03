/*
 * Search.cpp
 *
 *  Created on: 03/05/2017
 *      Author: rpedr
 */

#include "Search.h"

Search::Search(string st1,string st2, vector<Road>roads,vector<Aresta>arestas,vector<Bin>bins) {
	this->street1=st1;
	this->street2=st2;
	this->roads=roads;
	this->arestas=arestas;
	this->bins=bins;
}

const vector<Road>& Search::getRoads() const {
	return roads;
}

const string& Search::getStreet1() const {
	return street1;
}

const string& Search::getStreet2() const {
	return street2;
}

void Search::preKMP(string pattern, int f[])
{
    int m = pattern.length(), k;
    f[0] = -1;
    for (int i = 1; i < m; i++)
    {
        k = f[i - 1];
        while (k >= 0)
        {
            if (pattern[k] == pattern[i - 1])
                break;
            else
                k = f[k];
        }
        f[i] = k + 1;
    }
}

//check whether target string contains pattern
bool Search::KMP(string pattern, string target)
{
    int m = pattern.length();
    int n = target.length();
    int f[m];
    preKMP(pattern, f);
    int i = 0;
    int k = 0;
    while (i < n)
    {
        if (k == -1)
        {
            i++;
            k = 0;
        }
        else if (target[i] == pattern[k])
        {
            i++;
            k++;
            if (k == m)
                return 1;
        }
        else
            k = f[k];
    }
    return 0;
}

bool Search::isDumpster(long long id){

	for(unsigned int j=0;j<bins.size();j++){
		if(id==bins[j].getId()){
			return true;

		}

	}
	return false;
}


int Search::findRoad(string street){

	for(unsigned int i=0;i<roads.size();i++){
		if(KMP(roads[i].getName(),street)==1){
			cout<<roads[i].getId()<<"-----"<<endl;
			return roads[i].getId();
		}
	}
	cout<<"A rua: "<< street<<" nao existe"<<endl;
	return -1;
}

bool Search::hasDumpster(){
	long long id1 = findRoad(street1);
	long long id2 = findRoad(street2);
	cout<<"id1:"<<id1<<endl;
	cout<<"id2:"<<id2<<endl;

	int index1;
	int index2;

	if((id1=!-1) &&( id2!=-1)){
		for(unsigned int i=0;i<arestas.size();i++){
				if(id1==arestas[i].getEdgeId()){
					index1=i;
					cout<<index1<<endl;
				}
				if(id2==arestas[i].getEdgeId()){
					cout<<index2<<endl;
				}
			}
	}
	else
		return false;

	if((arestas[index1].getDestId()==arestas[index2].getDestId())&& isDumpster(arestas[index1].getDestId())){
		cout<<"Os destinos sao iguais e é contentor"<<endl;
		return true;


	}
	if((arestas[index1].getSourceId()==arestas[index2].getSourceId())&& isDumpster(arestas[index1].getSourceId()))
			return true;
	//if((arestas[index1].getSourceId()==arestas[index2].getSourceId())&& isDumpster(arestas[index1].getSourceId()))
	//			return true;

}





