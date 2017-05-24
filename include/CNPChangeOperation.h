/*
 * CNPChangeOperation.h
 */

#ifndef __CNPCHANGEOPERATION_H__
#define __CNPCHANGEOPERATION_H__

#include <CNPSolution.h>


/**
 * Clase abstracta para representar cualquier operación de modificación sobre una solución.
 */
class CNPChangeOperation{

public:

	/**
	 * Destructor
	 */
	virtual ~CNPChangeOperation(){

	}

	/**
	 * Función que aplica el cambio que define el objeto sobre la solución que recibe como argumento
	 * @param[in,out] solution Objeto solución sobre el que se aplicará el cambio
	 */
	virtual void apply(CNPSolution &solution) = 0;
};

#endif

