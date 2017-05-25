/*
 * CNPSimpleFirstImprovementNO.cpp
 */

#include <CNPSimpleFirstImprovementNO.h>
#include <CNPInstance.h>
#include <CNPEvaluator.h>
#include <CNPNodeAssignmentOperation.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

using namespace std;

bool CNPSimpleFirstImprovementNO::findOperation(CNPInstance &instance, CNPSolution &solution, CNPChangeOperation &operation) {

	CNPNodeAssignmentOperation *oaOperation = dynamic_cast<CNPNodeAssignmentOperation*>(&operation);
	if (oaOperation == NULL){
		cerr << "MQKPSimpleFirstImprovementNO::findOperation recibió un objeto operation que no es de la clase CNPObjectAssignmentOperation" << endl;
		exit(1);
	}

	CNPSolution newSol(solution);
	//Crear una permutación de los índices de los objetos e inicializar algunas variables
	vector<int> perm;
	int numNodo = instance.getNumNodes();
	int indexNode;
	bool aux;


	instance.randomPermutation(numNodo, perm);

	// Probamos con todos los objetos
	for (int i = 0; i < (int)perm.size(); i++) {

			newSol.copy(solution);
			indexNode=rand()%numNodo;
			while(solution.getNode(indexNode)!=solution.getNode(perm[i])){
				indexNode=rand()%numNodo;
			}

			aux=newSol.getNode(indexNode);
			newSol.setNode(indexNode,solution.getNode(perm[i]));
			newSol.setNode(perm[i],aux);
			


			double Fitness = CNPEvaluator::computeFitness(instance, newSol);
			double deltaFitness=Fitness-solution.getFitness();

			if (deltaFitness>0) {
			   oaOperation->setValues(perm[i],indexNode, deltaFitness);
				return true;
			}

	}

	// Si llega aquí no se han encontrado soluciones mejores a la actual
	return false;
}
