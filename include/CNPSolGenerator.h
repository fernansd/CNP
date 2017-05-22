/**
 * CNPSolution.h
 *
 * Fichero que define la clase 	CNPSolGenerator. 
 * Forma parte del código esqueleto para el problema de la búsqueda de nodos críticos, 
 * ofrecido para las prácticas de la asignatura Metaheurísticas del 
 * Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Undead Corporation
 */

/*

COSAS QUE SE PUEDEN CAMBIAR(APUNTES)

COSAS CAMBIADAS

*/


#ifndef __CNPSOLGENERATOR_H__
#define __CNPSOLGENERATOR_H__

#include "CNPInstance.h"
#include "CNPSolution.h"

/**
 * Clase que genera una solución aleatoria al problema CNP
 *
 * Sobre la representación de soluciones:
 * La representación de las soluciones será un vector de booleano de tamaño
 * Nodos-1, donde true significará que el nodo es retirado y false que no es retirado.
 */
class CNPSolGenerator {

public:

	/**
	 * Función que genera una solución aleatoria para el problema de las múltiples mochilas cuadráticas
	 * @param[in] instance Referencia a un objeto con la información de la instancia del problema CNP
	 * @param[out] solution Referencia a un objeto que representa una solución al problema. 
	 */
	void genRandomSol(CNPInstance &instance, CNPSolution &solution);
};
