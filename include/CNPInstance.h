/*
 * CNPInstance.h
 *
 *  Created on: 30/03/2017
 *      Author: i42sadef
 */

#ifndef CNPINSTANCE_H_
#define CNPINSTANCE_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class CNPInstance {
private:
	/* Matriz de adyacencias para los nodos del vector
	 * El índice de cada posición representa el identificador del nodo
	 * El valor almacenado será 1 si están conectados y 0 si no lo están
	 * Al ser un grafo no dirigido, se cumple matriz[i][j] == matriz[j][i]
	 */
	std::vector< std::vector<bool> > _lados;

	/* NO es necesario // Indica si el miembro vector_centrality está actualizado
	bool _centralityValido = false;*/

	double _sumaCentrality = 0;

	// Número que indica la cantidad de nodos a retirar en esta instancia del problema
	unsigned _numCritMax;

public:

	CNPInstance() {_numCritMax=-1;}

	CNPInstance(int numNodes, unsigned numCritMax);

	// Se define el tipo el tipo Grafo como una matriz de booleanos
	typedef std::vector < std::vector<bool> > Grafo;

	unsigned getNumNodes() {return (unsigned)_lados.size();}

	Grafo& getGrafo() { return _lados; }

	// Devuelve si dos nodos están conectados
	bool getLado(int n1, int n2) {return _lados[n1][n2];}

	// Permite cambiar el estado de un lado para los nodos parámetro
	void setLado(int n1, int n2, bool estado);

	unsigned getNumCritMax() {return _numCritMax;}

	/**
	 * Función que genera una permutación de los enteros de 0 a (size - 1)
	 * @param[in] size Tamaño de la permutación
	 * @param[out] perm Vector donde se almacenará la permutación
	 */
	static void randomPermutation(int size, vector<int> &perm);

	void readInstance(char* instanceName, int numCritMax);

	double getSuma() {return _sumaCentrality;}
};

#endif /* CNPINSTANCE_H_ */
