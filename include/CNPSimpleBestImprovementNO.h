/*
 * CNPSimpleBestImprovementNO.h
 */

#ifndef INCLUDE_CNPSIMPLEBESTIMPROVEMENTNO_H_
#define INCLUDE_CNPSIMPLEBESTIMPROVEMENTNO_H_

#include <CNPNeighExplorer.h>
#include <CNPSolution.h>
#include <CNPChangeOperation.h>
/**
 * Clase que se encarga de explorar el vecindario de una solución dada, devolviendo la mejor operación de asignación de un objeto a una mochila entre las operaciones posibles, devolverá FALSE si la operación devuelta no mejora a la solución actual
 */
class CNPSimpleBestImprovementNO : public CNPNeighExplorer{

public:

	/**
	 * Destructor
	 */
	virtual ~CNPSimpleBestImprovementNO(){

	}

	/**
	 * Función que explora el vecindario de una solución dada, devolviendo la mejor operación de asignación de un objeto a una mochila entre las operaciones posibles, devolverá FALSE si la operación devuelta no mejora a la solución actual
	 */
	virtual bool findOperation(CNPInstance &instance, CNPSolution &solution, CNPChangeOperation &operation);

};


#endif
