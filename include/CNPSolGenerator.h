/*
 * CNPSolGenerator.h
 *
 *  Created on: May 22, 2017
 *      Author: fernando
 */

#ifndef CNPSOLGENERATOR_H_
#define CNPSOLGENERATOR_H_

#include <CNPInstance.h>
#include <CNPSolution.h>

class CNPSolGenerator {
public:
	/**
	 * Función que genera una solución aleatoria para el problema de los nodos críticos
	 * @param[in] instance Referencia a un objeto con la información de la instancia del problema CNP
	 * @param[out] solution Referencia a un objeto que representa una solución al problema. IMPORTANTE: debe estar correctamente inicializado. En particular, su vector interno debe haber sido reservado previamente.
	 */
	static void genRandomSol(CNPInstance &instance, CNPSolution &solution);
};

#endif /* CNPSOLGENERATOR_H_ */
