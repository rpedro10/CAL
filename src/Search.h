/*
 * Search.h
 *
 *  Created on: 03/05/2017
 *      Author: rpedr
 */

#ifndef SRC_SEARCH_H_
#define SRC_SEARCH_H_

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <map>
#include "Bin.h"
#include "Aresta.h"

#include "Graph.h"
#include "NodeInf.h"
#include "graphviewer.h"
#include "Road.h"
#include "Position.h"
using namespace std;



/**
 * Classe que consiste em encontrar a rua pedida e verificar se algum dos nodes encontrados nessa rua é contentor
 */

class Search {
	/**
	* String da rua a ser procurada.
	*/
	string street1;
	/**
	* Vector que contem todas as ruas.
	*/
	vector<Road>roads;
	/**
	* Vector que guarda arestas e a sua informacao.
	*/
	vector<Aresta>arestas;
	/**
	* Vector que guarda a informacao sobre todos os contentores.
	*/
	vector<Bin>bins;

public:

	/**
	 * Construtor para uma pesquisa dando os parâmetros.
	 *
	 * @param st1 rua a procurar
	 * @param roads vector que contem todas as ruas
	 * @param ar vector que contem todos os nodes
	 * @param bins vector que contem todos os contentores
	 */
	Search(string st1, vector<Road>roads,vector<Aresta>ar,vector<Bin>bins);
	/**
	 * Algoritmo para pesquisa exata.
	 *
	 * @param pattern pattern to be checked
	 * @param target string to be analised
	 */
	bool KMP(string pattern, string target);
	/**
	 * Algoritmo auxiliar para pesquisa exata.
	 *
	 * @param pattern pattern to be checked
	 */
	void preKMP(string pattern, int f[]);
	/**
	 * Retorna ruas existentes.
	 *
	 */
	const vector<Road>& getRoads() const;
	/**
	 * Retorna string a ser procurada.
	 *
	 */
	const string& getStreet1() const;
	/**
	 * Verifica se no com o id dado se existe um contentor.
	 *
	 * @param id id do node
	 */
	bool isDumpster(long long id);
	/**
	 * Algoritmo para encontrar uma rua usando pesquisa exata.
	 *
	 */
	vector<long long> findRoad();
	/**
	 * Verifica se a rua contem contentores.
	 *
	 */
	vector<Bin> hasDumpster();
	/**
	 * Calcula distancia entre uma pattern e string.
	 *
	 * @param pattern pattern
	 * @param text string 
	 */
	unsigned int editDistance( string &pattern, string &text);
	/**
	 * Algoritmo para pesquisa aproximada.
	 */
	vector<long long> aproxSearch();
	/**
	 * Devolve rua dado id da aresta.
	 *
	 * @param edege_id id da aresta a ser procurada
	 */
	Road getRoad(long long edge_id);


};


#endif /* SRC_SEARCH_H_ */
