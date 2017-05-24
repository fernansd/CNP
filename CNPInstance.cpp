/*
 * CNPInstance.cpp
 *
 *  Created on: 30/03/2017
 *      Author: i42sadef
 */

#include "CNPInstance.h"
#include <CNPEvaluator.h>

CNPInstance::CNPInstance(int numNodes, unsigned numCritMax)
{
	_numCritMax = numCritMax;
	_lados.resize(numNodes);

	// Se usa numNodes en vez de .size() ya que es preferible segfault que no inicializar
	for (int i = 0; i < numNodes; i++) {
		_lados[i].resize(numNodes);
	}
	_sumaCentrality = 0;
}

void CNPInstance::setLado(int n1, int n2, bool estado)
{
	if (estado == true) {
		// Conecta los nodos
		_lados[n1][n2] = true;
		_lados[n2][n1] = true;
	} else {
		// Desconecta los nodos
		_lados[n1][n2] = false;
		_lados[n2][n1] = false;
	}
}

void CNPInstance::randomPermutation(int size, std::vector<int>& perm) {

	/** HECHO
	 * 1. Vacía el vector perm
	 * 2. Llénalo con la permutación identidad
	 * 3. Recórrelo intercambiando cada elemento con otro escogido de forma aleatoria.
	 */

	int aux,pos;
	perm.clear();
	for(int i=0;i<size;i++){
		perm.push_back(i);
	}
	for(int i=0;i<size;i++){
		pos=rand()%size;
		aux=perm[pos];
		perm[pos]=perm[i];
		perm[i]=aux;}
}



void CNPInstance::readInstance(char* instanceName, int numCritMax)
{
	_numCritMax = numCritMax;

	std::string nombre = instanceName;
	std::ifstream fichero(nombre);
	int numNodes;

	// En la primera línea del fichero estaá el número de nodos
	fichero >> numNodes;

	// Redimensiona la matriz grafo
	_lados.resize(numNodes);
	for (size_t i = 0; i < _lados.size(); i++) {
		_lados[i].resize(numNodes);
	}

	int lado;
	for (int i = 0; i < numNodes; i++) {
		for (int j = 0; j < numNodes; j++) {
			fichero >> lado;
			if (lado == 1){
				_lados[i][j] = true;
			} else if (lado == 0) {
				_lados[i][j] = false;
			} else {
				std::cerr << "Detectado valor (" << lado << ") inválido en la lectura"
						  << " del fichero " << nombre << std::endl;
			}
		}
	}
	double suma = 0;
	std::vector<double> centrality = CNPEvaluator::computeBetweennessCentrality(*this);
	for (size_t i = 0; i < centrality.size(); i++) {
		suma += centrality[i];
	}
	_sumaCentrality = suma;
}
