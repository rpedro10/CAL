#ifndef BIN_H_
#define BIN_H_
#include <string>
using namespace std;

/**
 * Classe que permite guardar a informação de caixotes de lixo.
 *
 */
class Bin{
	/**
	 * ID da caixote lixo, corresponde a um ID de um nó no mapa.
	 */
	int id;
	/**
	 * Tipo de lixo guardado neste caixote.
	 */
	string type;

public:
	/**
	 * Construtor para um caixote do lixo.
	 * @param id Número único deste caixote.
	 * @param type Tipo do lixo que guarda.
	 */
	Bin(int id,string type);
	/**
	 * Retorna id do caixote.
	 */
	int getId();
	/**
	 * Retorna tipo de lixo.
	 */
	string getType();

};

#endif
