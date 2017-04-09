#ifndef NODEINF_H_
#define NODEINF_H_
#include <string>
#include "Position.h"
using namespace std;


/**
 * Classe qua guarda informa��o pertinente aos n�s.
 *
 */
class NodeInf {
	/**
	 * Id do n�.
	 */
	long long id;
	/**
	 * Localiza�ao do n� usando latitude e longitude.
	 */
	Position coordinate;
	/**
	 * Determina se este n� � um contentor ou n�o.
	 */
	bool contentor;

public:
	/**
	 * Construtor da informa��o de um n�.
	 *
	 * @param id id do n�
	 * @param coordinates latitude e longitude do n�
	 * @param bin verdadeiro se este n� for um caixote do lixo, contr�rio se n�o
	 */
	NodeInf(long long id, Position coordinates, bool bin);
	/**
	 * Constutor simples da informa��o de um n�. Usado para poder encontrar n�s a partir de apenas do id.
	 *
	 * @param id id do n�
	 */
	NodeInf(long long id);

	/**
	 * Overload para determinar quando a informa��o dos n�s igual, que depois � usado para comparar n�s.
	 *
	 * @param nf1 informa��o do n� com que se quer comparar
	 */
	bool operator==(const NodeInf &nf1) const;

	/**
	 * Overload para determinar quando a informa��o dos n�s � diferente, que depois � usado para comparar n�s.
	 *
	 * @param nf1 informa��o do n� com que se quer comparar
	 */
	bool operator!=(const NodeInf &nf1) const;
	/**
	 * Retorna o id da informa��o do n�, que coincide com o id do n�.
	 *
	 */
	long long getId();
	/**
	 * Retorna as coordenadas do n�.
	 */
	Position getCoordinate();
	/**
	 * Verdadeiro se n� for um contentor, contr�rio se n�o.
	 */
	bool isContentor() const;
	/**
	 * Muda o estado deste n� para conter ou n�o um contentor.
	 *
	 * @param contentor estado para qual se quer mudar este contentor
	 */
	void setContentor(bool contentor);
};

#endif
