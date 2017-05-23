/*
 * CNPSolGenerator.cpp
 *
 * Fichero que define los métodos de la clase CNPSolGenerator. 
 * Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, 
 * ofrecido para las prácticas de la asignatura Metaheurísticas del 
 * Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Undead Corporation (vep1940)
 */

#include "CNPSolGenerator.h"
#include "CNPInstance.h"
#include "CNPSolution.h"
#include <stdlib.h>

void CNPSolGenerator::genRandomSol(CNPInstance &instance, CNPSolution &solution){

	unsigned numNodes=instance.getNumNodes();
	unsigned numMaxCrit=instance.getNumCritMax();
	solution.setNumCrit(0);

	while(solution.getNumCrit()!=numMaxCrit){
		solution.setNode(rand()%numNodes,true);
	}
}
