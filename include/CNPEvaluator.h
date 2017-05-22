/*
 * CNPEvaluator.h
 *
 *  Created on: 30/03/2017
 *      Author: i42sadef
 */

/*

COSAS QUE SE PUEDEN CAMBIAR(APUNTES)
-> AÑADIR/O NO VECTOR DE FITNESS DE LOS NODOS CON ESA SOLUCION, LA RAZÓN ES QUE EN MOCHILAS
	PODEMOS CALCULAR COMO CAMBIA EL INTRODUCIR UN OBJETO EN OTRO, PERO AQUI ESO HACERLO NODO
	POR NODO PODRIA SER COSTOSO, POR LO QUE CALCULAMOS FITNESS CON UNA SOLUCION COMPLETA,
	POR ELLO, PARA DECIDIR QUE NODO RETIRAR, DEBEMOS GUARDAR AL MENOSESE VECTOR, O REDEFINIR
	LA FORMA DE CALCULAR EL FITNESS, SOBRE LA SOLUCION O SOBRE UN NODO AÑADIDO A LA SOLUCION.
	PENSAD EN LAS METAS QUE VAMOS A APLICAR, EN COMO FUNCIONAN

COSAS CAMBIADAS

*/

#ifndef CNPEVALUATOR_H_
#define CNPEVALUATOR_H_

#include <vector>

#include <CNPInstance.h>
#include <CNPSolution.h>

/**
 * Clase que calcula el fitness de una solución al problema CNP
 */
class CNPEvaluator {
protected:
	/**
	 * Variable donde se contabiliza el número de soluciones que se evalúan a través de  computeFitness o computeDeltaFitness
	 */
	static unsigned _numEvaluations;

	// Función que guarda en neighbours los nodos vecinos del nodo pasado por parámetro
	static void getNeighbours(CNPInstance& instance, int nodo, std::vector<int>& neighbours);

	// Función que obtiene la betweenness centrality para todos los nodos del grafo
	static std::vector<double> computeBetweennessCentrality(CNPInstance& instance);

public:

	/**
	 * Función que resetea la variable interna que contabiliza el número de evaluaciones
	 */
	static void resetNumEvaluations(){_numEvaluations=0;};

	/**
	 * Función que devuelve el número de veces que se ha evaluado alguna solución
	 */
	static double getNumEvaluations() {return _numEvaluations;}

	/**
	// Función que calcula el fitness de la solución para una instacia del problema
	 * @param[in] instance Referencia a un objeto con la información de la instancia del problema CNP
	 * @param[in] solution Referencia a un objeto que representa una solución al problema.
	 *
	 * @return Fitness de la solución. SE calcula mediante la aplicación de la BetweennessCentrality
	 */
	static double computeFitness(CNPInstance &instance, CNPSolution &solution);
};

#endif /* CNPEVALUATOR_H_ */
