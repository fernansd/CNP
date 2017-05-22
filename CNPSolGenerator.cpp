/*
 * CNPSolGenerator.cpp
 *
 *  Created on: May 22, 2017
 *      Author: fernando
 */

#include <CNPSolGenerator.h>
#include <CNPInstance.h>
#include <CNPSolution.h>

void CNPSolGenerator::genRandomSol(CNPInstance &instance, CNPSolution &solution)
{
	int numNodes = instance.getNumNodes();
	int numCritMax = instance.getNumCritMax();

	// Se está suponiendo que solution tiene su vector solución entero a false
	// Se van a poner a true numCriMax número de nodos que se eliminen del grafo
	for (int i = 0; i < numCritMax; i++){
		int randomNode = rand() % numNodes;
		if (solution.getNode(randomNode) == true) {
			i--; // Esto hace que se repita la iteración i
		} else {
			solution.setNode(randomNode, true);
		}
	}
}

