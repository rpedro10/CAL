/*
 * Edge.h
 *
 *  Created on: 03/05/2017
 *      Author: rpedr
 */

#ifndef SRC_ARESTA_H_
#define SRC_ARESTA_H_

using namespace std;

/**
 * Classe para guarda informacao sobre arestas.
 */
class Aresta {
	/**
	 * Id da aresta.
	 */
	long long edge_id;
	/**
	 * Id do node source.
	 */
	long long source_id;
	/**
	 * Id do node dest.
	 */
	long long dest_id;


public:
	/**
	 * Construtor para a informacao sobre arestas.
	 *
	 * @param edge_id id da aresta
	 * @param source_id id do node source
	 * @param dest_id id do node source
	 */
	Aresta(long long edge_id,long long source_id,long long dest_id);
	/**
	 * Retorna Id do node dest.
	 */
	long long getDestId() const;
	/**
	 * Retorna Id da aresta.
	 */
	long long getEdgeId() const;
	/**
	 * Retorna Id do node source.
	 */
	long long getSourceId() const;
};


#endif /* SRC_ARESTA_H_ */
