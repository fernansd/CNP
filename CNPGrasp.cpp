/*
 * CNPGrasp.cpp
 *
 * Fichero que define las funciones de la clase CNPGrasp.
 *
 * @author: Chacal anónimo
 */

#include <CNPGrasp.h>
#include <CNPSolGenerator.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

void CNPGrasp::chooseOperation(CNPObjectAssignmentOperation& operation,
		std::vector<double>& centrls) {

	unsigned newNode = -1;
	//unsigned oldNode = -1;
    //double bestCentrality = 0;

	double newDeltaFitness = 0;
    //bool initialisedBestCentrality = false;
    unsigned numNodes = _instance->getNumNodes();
    unsigned chosenNodes = (unsigned)floor(numNodes*0.3); // Elige el 10 % mejor
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


void CNPGrasp::buildInitialSolution() {

	/**
	 * hecho
	 * Vaciar la soluciÃ³n _sol asignÃ¡ndole un fitness de 0 y poniendo todos los objetos en la mochila 0
	 */

	//CNPSolGenerator::genRandomSol(*_instance, *_sol);

	/** Seleccionar la primera operaciÃ³n */
	CNPObjectAssignmentOperation operation;
	std::vector<double> centrls = _sol->getVectorFitness();
	chooseOperation(operation, centrls);

	/**
	 * hecho
	 * Mientras la operaciÃ³n tenga un incremento de fitness positivo, operation.getDeltaFitness(),
	 *  1. aplicar la operaciÃ³n en _sol
	 *  2. Almacenar el fitness de la soluciÃ³n en _result (para las grÃ¡ficas)
	 *  3. seleccionar una nueva operaciÃ³n
	 */
	while (_sol->getNumCrit()!=_sol->getNumCritMax()) {
		operation.apply(*_sol);
		_sol->setFitness(CNPEvaluator::computeFitness(*_instance, *_sol));
		_results.push_back(_sol->getFitness());
		chooseOperation(operation, centrls);
	}
}


void CNPGrasp::initialise(double alpha, CNPInstance& instance) {

	_sol = new CNPSolution(instance);
	_bestSolution = _sol;
	_bestSolution->copy(*_sol);
	_instance = &instance;
	_alpha = alpha;
}

void CNPGrasp::run(CNPStopCondition& stopCondition) {

	if (_sol == NULL) {
		cerr << "GRASP was not initialised" << endl;
		exit(-1);
	}

	//CNPSolGenerator::genRandomSol(*_instance,*_sol);
	//double fitness = CNPEvaluator::computeFitness(*_instance,*_sol);
	//_sol->setFitness(fitness);
	CNPSolution emptySol(*_instance);


	/**
	 * hecho
	 * Mientras no se alcance el criterio de parada
	 *   1. Generar una soluciÃ³n inicial invocando al metodo correspondiente
	 *   2. Almacenar el fitness de la soluciÃ³n en _results
	 *   3. Optimizar _sol con la bÃºsqueda local y el operador de vecindario de la metaheurÃ­stica
	 *   4. Actualizar la mejor soluciÃ³n
	 */
	while (stopCondition.reached() == false) {
		_sol->copy(emptySol);
		_results.push_back(_sol->getFitness());
		buildInitialSolution();
		_results.push_back(_sol->getFitness());
		if ((_sol->getFitness()-_bestSolution->getFitness()) > 0)
			_bestSolution->copy(*_sol);

		stopCondition.notifyIteration();
	}
}
