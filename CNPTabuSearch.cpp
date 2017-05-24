/*
 * CNPTabuSearch.cpp
 *
 * Fichero que define las funciones de la clase CNPTabuSearch. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <CNPTabuSearch.h>
#include <CNPEvaluator.h>
#include <CNPObjectAssignmentOperation.h>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>

using namespace std;

void CNPTabuSearch::initialise(CNPInstance* instance, unsigned tabuTennure) {
	_instance = instance;
	_tabuTennure = tabuTennure;
}

void CNPTabuSearch::setSolution(CNPSolution* solution) {

	if (_solution != NULL){
		cerr << "No se debe invocar más de una vez el método CNPTabuSearch::setSolution" << endl;
		exit(1);
	}

	this->_solution = solution;

	if (_bestSolution == NULL) {
		_bestSolution = new CNPSolution(*_instance);
	}

	_bestSolution->copy(*solution);
}

void CNPTabuSearch::run(CNPStopCondition& stopCondition) {
	if (_solution == NULL) {
		cerr << "Tabu search has not been given an initial solution" << endl;
		exit(-1);
	}

	_results.clear();
	//unsigned numNodes = _instance->getNumNodes();
	//unsigned numCritMax = _instance->getNumCritMax();
	unsigned numIterations = 0;

	/**
	 * Hecho
	 * Mientras no se alcance la condición de parada
	 *  1. Generar una permutación de objetos
	 *  2. Buscar la mejor operación no tabú de asignación de un objeto a una mochila (incluida la 0)
	 *  3. Aplicar la operación
	 *  4. Insertar el índice del objeto afectado en la memoria tabú
	 *  5. Actualizar la mejor solución hasta el momento
	 */

	while (stopCondition.reached() == false) {

		double bestFitness = 0;
		bool initialisedBestFitness = false;
		CNPSolution auxSol(*_solution);
		CNPSolution bestSol(auxSol);
		unsigned bestNode = 0;

		vector<unsigned> activated;
		vector<unsigned> deactivated;
		_solution->splitNodes(activated, deactivated);

		// Elegimos un nodos a quitar de la solución
		unsigned removed = (unsigned)(rand() % activated.size());
		auxSol.setNode(removed, false);

		//Buscar la mejor operación no tabú, es decir, qué nodo añadir
		for (unsigned i = 0; i < (unsigned)deactivated.size(); i++) {
			unsigned indexNode = deactivated[i];

			//Si el objeto no es tabú (utilizar _shortTermMem_aux.find)
			if ( _shortTermMem_aux.end() == _shortTermMem_aux.find(indexNode)) {
				// La operación a probar es activar el nodo indexNode
				auxSol.setNode(indexNode, true);

				//Obtener la diferencia de fitness de aplicar dicha operación
				double newFitness = CNPEvaluator::computeFitness(*_instance, auxSol);

				//Si la diferencia de fitness es la mejor hasta el momento, apuntarla para aplicarla después
				if (newFitness > bestFitness
						|| initialisedBestFitness == false) {
					initialisedBestFitness = true;
					bestFitness = newFitness;
					bestSol.copy(auxSol);
					bestNode = indexNode;
				}
				auxSol.setNode(indexNode, false);
			}
		}
		if (bestSol.getNumCrit() > bestSol.getNumCritMax()) {
			std::cerr << "Excedido límite de nodos: " << bestSol.getNumCrit() << std::endl;
		}

		//Hecho Aplicar la operación y almacenarla en la memoria a corto plazo
		_solution->copy(bestSol);
		_shortTermMem.push(bestNode);
		_shortTermMem_aux.insert(bestNode);

		//hecho Si hay demasiados elementos en la memoria, según la tenencia tabú, eliminar el más antiguo
		if (_shortTermMem.size() > _tabuTennure) {
			unsigned value = _shortTermMem.front();
			_shortTermMem.pop();
			_shortTermMem_aux.erase(value);

		}

		//Actualizar la mejor solución
		if (_solution->getFitness() > _bestSolution->getFitness()) {
			_bestSolution->copy(*_solution);
		}

		numIterations++;
		_results.push_back(_solution->getFitness());

		stopCondition.notifyIteration();
	}
}
