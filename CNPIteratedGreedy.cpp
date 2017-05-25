/*
 * MQKPIteratedGreedy.cpp
 */

#include <CNPIteratedGreedy.h>
#include <CNPObjectAssignmentOperation.h>
#include <CNPSolution.h>
#include <CNPSolGenerator.h>
#include <CNPEvaluator.h>
#include <iostream>
#include <cmath>

using namespace std;

void CNPIteratedGreedy::chooseOperation(CNPObjectAssignmentOperation& operation,
		std::vector<double>& centrls) {

	unsigned newNode = -1;
	//unsigned oldNode = -1;
    //double bestCentrality = 0;

	double newDeltaFitness = 0;
    //bool initialisedBestCentrality = false;
    unsigned numNodes = _instance->getNumNodes();
    unsigned chosenNodes = 1/*(unsigned)floor(numNodes*0.1)*/; // Elige el 10 % mejor
    //unsigned numCriticalNodes = _instance->getNumCritMax();
    std::vector<int> topNodes; // Vector que guarda los nodos elegidos como mejores
    for (unsigned i = 0; i < numNodes; i++) {

   		int indexNode = i;
   		//vector<bool> currentSol=_sol->getSolution();
		//comprobar que no ha sido eliminado 0 es no eliminado / 1 es eliminado
   		if (_sol->getNode(indexNode)==false) {

   			// NO se guardan en todos los casos los N mejores, se garantiza sólo elegir varios de los buenos
   			// Si ya no se pueden añadir nodos nuevos se sustituye uno
   			if (topNodes.size() == chosenNodes) {
				for (size_t j = 0; j < chosenNodes; j++) {
					if (centrls[indexNode] > centrls[topNodes[j]]) {
						topNodes[j] = indexNode;
					}
				}
   			} else {
   				topNodes.push_back(indexNode);
   			}

   			/*//double deltaFitness = CNPEvaluator::computeDeltaFitness(*_instance,*_sol, indexNode);
			double deltaFitness = CNPEvaluator::computeFitness(*_instance,*_sol);
			//double centrality = deltaFitness/centrls[indexNode];
			if (bestCentrality > centrality || initialisedBestCentrality == false) {
				initialisedBestCentrality = true;
				bestCentrality = centrality;
				bestNode = indexNode;
				newDeltaFitness = deltaFitness;
			}*/
   	 	}
    }
    unsigned selected = (unsigned)rand()%chosenNodes;
    if (selected >= chosenNodes) {
    	std::cerr << "Valor no válido --> " << selected << std::endl;
    }
    newNode = topNodes[selected];
    /*
    CNPSolution aux(*_sol);
    aux.setNode(newNode, true);
    newDeltaFitness = CNPEvaluator::computeFitness(*_instance, *_sol);*/

    operation.setValues(newNode, newDeltaFitness);
}

void CNPIteratedGreedy::rebuild() {

	/** Seleccionar la primera operación */
	CNPObjectAssignmentOperation operation;
	std::vector<double> centrls = _sol->getVectorFitness();

	while (_sol->getNumCritMax() != _sol->getNumCrit()){
		chooseOperation(operation, centrls);
		operation.apply(*_sol);
		_sol->setFitness(CNPEvaluator::computeFitness(*_instance, *_sol));
		_results.push_back(_sol->getFitness());
	}

}

void CNPIteratedGreedy::destroy() {

	unsigned numNodes = _instance->getNumNodes();
    //vector <bool> currentSol=_sol->getSolution();

    for (unsigned i = 0; i < numNodes; i++){   
   		if(_sol->getNode(i)==true){	// Se hace sobre soluciones que vayan a eliminarse
	   		double randSample = ((double)(rand())) / RAND_MAX;
	   	 	// Quita un nodo de la solución con probabilidad _alpha
	   		if (randSample < _alpha){
	   			_sol->setNode(i, 0);
	   		}
   	 	}
    }

    double fitness = CNPEvaluator::computeFitness(*_instance, *_sol);
    _sol->setFitness(fitness);
    _results.push_back(_sol->getFitness());
}

void CNPIteratedGreedy::initialise(double alpha, CNPInstance& instance) {
	_sol = new CNPSolution(instance);
	_bestSolution = new CNPSolution(instance);
	_bestSolution->copy(*_sol);
	_instance = &instance;
	_alpha = alpha;

}

void CNPIteratedGreedy::run(CNPStopCondition& stopCondition) {

	if (_sol == NULL) {
		cerr << "IG was not initialised" << endl;
		exit(-1);
	}
	CNPSolGenerator::genRandomSol(*_instance, *_sol);
	CNPEvaluator::computeFitness(*_instance,*_sol);
	_results.push_back(_sol->getFitness());

	/** Crear la primera solución */
	rebuild();

	//if (CNPEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0)
	if(_bestSolution->getFitness()< _sol->getFitness())
		_bestSolution->copy(*_sol);


	while (stopCondition.reached() == false) {
		destroy();
		rebuild();
		_results.push_back(_sol->getFitness());

		//if (CNPEvaluator::compare(_sol->getFitness(), _bestSolution->getFitness()) > 0)
		if(_bestSolution->getFitness()< _sol->getFitness())
			_bestSolution->copy(*_sol); // Actualiza la mejor solución
		else
			_sol->copy(*_bestSolution); // Restaura la solución anterior


		stopCondition.notifyIteration();
	}
}
