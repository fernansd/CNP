/**
 * CNPSimpleBestImprovementNO.cpp
 */

#include <CNPSimpleBestImprovementNO.h>
#include <CNPInstance.h>
#include <CNPSolution.h>
#include <CNPNodeAssignmentOperation.h>
#include <CNPEvaluator.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
using namespace std;

bool CNPSimpleBestImprovementNO::findOperation(CNPInstance& instance, CNPSolution& solution, CNPChangeOperation& operation) {

	CNPNodeAssignmentOperation *oaOperation = dynamic_cast<CNPNodeAssignmentOperation*>(&operation);
	if (oaOperation == NULL){
		cerr << "CNPSimpleBestImprovementNO::findOperation recibió un objeto operation que no es de la clase CNPObjectAssignmentOperation" << endl;
		exit(1);
	}

	//Crear una permutación de los índices de los objetos e inicializar algunas variables

	CNPSolution newSol(solution);
	bestFitness=solution.getFitness();

	vector<int> perm;
	vector<int> perm2;
	int numNodo = instance.getNumNodes();

	instance.randomPermutation(numNodo,perm);
	instance.randomPermutation(numNodo,perm2);
	

	bool initialised = false;
	bool aux;
	double bestFitness = 0;

	double fitness=0.0,deltaFitness=0;

	for(int i=0;i<numNodo;i++){
		for(int j=0;j<numNodo;j++){
			newSol.copy(solution);


			if(newSol.getNode(perm[i])!=newSol.getNode(perm[j])){
				aux=newSol.getNode(perm[i]);

				newSol.setNode(perm[i],newSol.getNode(perm[j]));
				newSol.setNode(perm[j],aux);
				fitness = CNPEvaluator::computeFitness(instance, newSol);
			}
			if(deltaFitness=fitness-bestFitness>0  /*|| initialised == false*/){
				/*initialised = true;*/
				bestFitness=fitness;
				oaOperation->setValues(perm[i],perm[j], deltaFitness);
			}
		}
	}
	if(bestFitness>0){
		return true;
	}else{return false;}

}

