/*
 * CNPNeighExplorer.h
 */

#ifndef INCLUDE_CNPNEIGHEXPLORER_H_
#define INCLUDE_CNPNEIGHEXPLORER_H_

#include <CNPSolution.h>
#include <CNPInstance.h>
#include <CNPChangeOperation.h>

/**
 * clase abstracta que define las operaciones de cualquier operador que explora la vecindad de una solución dada.
 */
class CNPNeighExplorer {
public:

	/**
	 * Destructor
	 */
	virtual ~CNPNeighExplorer(){}

	/**
	 * Función que busca una operación que aplicada a la solución devuelva otra solución vecina. Se utilizará para buscar una solución vecina que la mejore, o la mejor de las soluciones vecinas.
	 */
	virtual bool findOperation(CNPInstance &instance, CNPSolution &solution, CNPChangeOperation &operation) = 0;
};

#endif
