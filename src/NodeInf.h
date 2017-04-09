#ifndef NODEINF_H_
#define NODEINF_H_
#include <string>
#include "Position.h"
using namespace std;


/**
 * Classe qua guarda informação pertinente aos nós.
 *
 */
class NodeInf {
	/**
	 * Id do nó.
	 */
	long long id;
	/**
	 * Localizaçao do nó usando latitude e longitude.
	 */
	Position coordinate;
	/**
	 * Determina se este nó é um contentor ou não.
	 */
	bool contentor;

public:
	/**
	 * Construtor da informação de um nó.
	 *
	 * @param id id do nó
	 * @param coordinates latitude e longitude do nó
	 * @param bin verdadeiro se este nó for um caixote do lixo, contrário se não
	 */
	NodeInf(long long id, Position coordinates, bool bin);
	/**
	 * Constutor simples da informação de um nó. Usado para poder encontrar nós a partir de apenas do id.
	 *
	 * @param id id do nó
	 */
	NodeInf(long long id);

	/**
	 * Overload para determinar quando a informação dos nós igual, que depois é usado para comparar nós.
	 *
	 * @param nf1 informação do nó com que se quer comparar
	 */
	bool operator==(const NodeInf &nf1) const;

	/**
	 * Overload para determinar quando a informação dos nós é diferente, que depois é usado para comparar nós.
	 *
	 * @param nf1 informação do nó com que se quer comparar
	 */
	bool operator!=(const NodeInf &nf1) const;
	/**
	 * Retorna o id da informação do nó, que coincide com o id do nó.
	 *
	 */
	long long getId();
	/**
	 * Retorna as coordenadas do nó.
	 */
	Position getCoordinate();
	/**
	 * Verdadeiro se nó for um contentor, contrário se não.
	 */
	bool isContentor() const;
	/**
	 * Muda o estado deste nó para conter ou não um contentor.
	 *
	 * @param contentor estado para qual se quer mudar este contentor
	 */
	void setContentor(bool contentor);
};

#endif
