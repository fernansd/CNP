/*
 * CNPSimpleFirstImprovementNO.h
 */

#ifndef INCLUDE_CNPSIMPLEFIRSTIMPROVEMENTNO_H_
#define INCLUDE_CNPSIMPLEFIRSTIMPROVEMENTNO_H_

#include <CNPNeighExplorer.h>
#include <CNPSolution.h>
#include <CNPChangeOperation.h>
/**
 * Clase que se encarga de explorar el vecindario de una solución dada, devolviendo la primera operación de asignación de un objeto a una mochila que encuentre que mejore la calidad de la solución recibida. En caso de que no exista ninguna operación que mejore la calidad de la solución recibida, entonces devolverá FALSE
 */
class CNPSimpleFirstImprovementNO : public CNPNeighExplorer{

public:

	/**
	 * Destructor
	 */
	virtual ~CNPSimpleFirstImprovementNO(){

	}

	/**
	 * Función que explora el vecindario de una solución dada, devolviendo la primera operación de asignación de un objeto a una mochila que encuentre que mejora la solución actual, devolverá FALSE si la operación devuelta no mejora a la solución actual
	 */
	virtual bool findOperation(CNPInstance &instance, CNPSolution &solution, CNPChangeOperation &operation);
};


#endif
