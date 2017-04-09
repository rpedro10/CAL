#ifndef POSITION_H_
#define POSITION_H_
#include <string>
#include <math.h>
using namespace std;
/**
 * Classe que representa um ponto usando longitude e latitude.
 */
class Position{
	/**
	 * Longitude e latitude do ponto.
	 */
	double longitude,latitude;

public:
	/**
	 *Construtor de um ponto recebendo as coordenadas.
	 *
	 *@param longitude longitude do ponto
	 *@param latitude latitude do ponto
	 */
	Position(double longitude, double latitude);
	/**
	 * Construtor de um ponto vazio.
	 */
	Position();
	/**
	 * Retorna longitude.
	 */
	double getLongitude();
	/**
	 * Retorna latitude.
	 */
	double getLatitude();
	/**
	 * Retorna distância a outro ponto.
	 *
	 * @param long1 longitude do ponto ao qual se quer calcular a distância.
	 * @param lat1  latitude do ponto ao qual se quer calcular a distância.
	 */
	double getDistance(double long1,double lat1);
};

#endif
