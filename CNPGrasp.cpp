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

using namespace std;

void CNPGrasp::chooseOperation(CNPNodeAssignmentOperation& operation) {

	int bestNode1=0,bestNode2=0;
	double bestDeltaFitness = 0;
	bool initialised=false;
	unsigned numNodes = _instance->getNumNodes();
	//unsigned numCriticalNodes = _instance->getNumCritMax();


	/**
	 * Calcular el nÃºmero de intentos como el porcentaje _alpha por el nÃºmero de posibilidades, que es el nÃºmero de objetos por el nÃºmero de mochilas.
	 *
	 * En este paso no se considerarÃ¡ que ya haya objetos asignados a alguna mochila, la mochila 0 que representa objetos sin asignar a ninguna mochila, ni que haya mochilas ya completamente llenas
	 */
	unsigned numTries = ((unsigned)(numNodes * _alpha));  /***COMPROBAR***/

	/**
	 * hecho
	 * Generar alternativas de objeto y mochila aleatorias (no se considera la mochila 0) y quedarse con la alterantiva de mejor densidad
	 */

	unsigned indexNode,indexNode2;
	bool aux;

	for (unsigned i = 0; i < numTries; i++) {

		CNPSolution newSol(*_sol);

		indexNode = rand()%numNodes;
		indexNode2= rand()%numNodes;

		while(_sol->getNode(indexNode)==_sol->getNode(indexNode2)){
			indexNode = rand()%numNodes;
			indexNode2= rand()%numNodes;
		}

		//Intercambio de estados
		aux=newSol.getNode(indexNode);
		newSol.setNode(indexNode,newSol.getNode(indexNode2));
		newSol.setNode(indexNode2,aux);

		double deltaFitness = CNPEvaluator::computeFitness(*_instance,newSol)-_sol->getFitness(); //hecho obtener la mejora en fitness de dicha operaciÃ³n

		//hecho actualizar si resulta ser la mejor
		if (bestDeltaFitness < deltaFitness||initialised==false) {
			initialised=true;
			bestNode1 = indexNode;
			bestNode2 = indexNode2;
			bestDeltaFitness = deltaFitness;
		}
	}

	operation.setValues(bestNode1,bestNode2,bestDeltaFitness);
}


void CNPGrasp::buildInitialSolution() {

	/**
	 * hecho
	 * Vaciar la soluciÃ³n _sol asignÃ¡ndole un fitness de 0 y poniendo todos los objetos en la mochila 0
	 */
	unsigned numNodes = _instance->getNumNodes();

	_sol->setFitness(0);
	for (unsigned i = 0; i < numNodes; i++) {
		_sol->setNode(i, false);
	}

	/** Seleccionar la primera operaciÃ³n */
	CNPNodeAssignmentOperation operation;
	chooseOperation(operation);

	/**
	 * hecho
	 * Mientras la operaciÃ³n tenga un incremento de fitness positivo, operation.getDeltaFitness(),
	 *  1. aplicar la operaciÃ³n en _sol
	 *  2. Almacenar el fitness de la soluciÃ³n en _result (para las grÃ¡ficas)
	 *  3. seleccionar una nueva operaciÃ³n
	 */
	while (operation.getDeltaFitness() > 0) {
		operation.apply(*_sol);
		_results.push_back(_sol->getFitness());
		chooseOperation(operation);
	}
}


void CNPGrasp::initialise(double alpha, CNPInstance& instance) {

	_sol = new CNPSolution(instance);
	_bestSolution = new CNPSolution(instance);
	_bestSolution->copy(*_sol);
	_instance = &instance;
	_alpha = alpha;
}

void CNPGrasp::run(CNPStopCondition& stopCondition) {

	if (_sol == NULL) {
		cerr << "GRASP was not initialised" << endl;
		exit(-1);
	}

	CNPSolGenerator::genRandomSol(*_instance,*_sol);
	double fitness = CNPEvaluator::computeFitness(*_instance,*_sol);
	_sol->setFitness(fitness);

	/**
	 * hecho
	 * Mientras no se alcance el criterio de parada
	 *   1. Generar una soluciÃ³n inicial invocando al metodo correspondiente
	 *   2. Almacenar el fitness de la soluciÃ³n en _results
	 *   3. Optimizar _sol con la bÃºsqueda local y el operador de vecindario de la metaheurÃ­stica
	 *   4. Actualizar la mejor soluciÃ³n
	 */
	while (stopCondition.reached() == false) {
		buildInitialSolution();
		_results.push_back(_sol->getFitness());

		if ((_sol->getFitness()-_bestSolution->getFitness()) > 0)
			_bestSolution->copy(*_sol);

		stopCondition.notifyIteration();
	}
}
