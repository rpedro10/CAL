/*
 * road.h
 *
 *  Created on: 29/03/2017
 *      Author: rpedr
 */

#ifndef SRC_ROAD_H_
#define SRC_ROAD_H_

#include <string>
#include "Position.h"
using namespace std;
/**
 * Classe que  guarda informação sobre uma rua.
 */
class Road{
	/**
	 * Id da rua.
	 */
	long long id;
	/**
	 * Nome da rua.
	 */
	string name;
	/**
	 * Booleano que determina se rua apresenta dois sentidos.
	 */
	bool both_ways;

public:
	/**
	 * Construtor para uma rua dando os parâmetros.
	 *
	 * @param _id id da rua
	 * @param b_ways verdadeiro se a rua tem dois sentidos
	 */
	Road(long long _id,string _name,bool b_ways);
	/**
	 * Verdadeiro caso a rua apresente dois sentidos.
	 */
	bool isBothWays() const;
	/**
	 * Muda a para rua para uma de dois sentidos ou não.
	 *
	 *@param bothWays verdadeiro para mudar rua para apresentar dois sentidos
	 */
	void setBothWays(bool bothWays);
	/**
	 * Retorna id da rua.
	 */
	long long getId() const;
	/**
	 * Muda id da rua.
	 *
	 *@param id Novo id da rua.
	 */
	void setId(long long id);
	/**
	 * Retorna nome associado à rua.
	 */
	const string& getName() const;
	/**
	 * Muda nome da rua.
	 *
	 * @param name Novo nome da rua.
	 */
	void setName(const string& name);
};

#endif /* SRC_ROAD_H_ */
