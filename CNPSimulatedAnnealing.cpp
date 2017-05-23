/*
 * CNPSimulatedAnnealing.cpp
 *
 * Fichero que define las funciones de la clase CNPSimulatedAnnealing.
 *
 * @author: Chacal an髇imo
 */

#include <CNPSimulatedAnnealing.h>
#include <CNPSolution.h>
#include <CNPSolGenerator.h>
#include <CNPEvaluator.h>
#include <cmath>
#include <iostream>
#include <cstdlib>


using namespace std;


void CNPSimulatedAnnealing::setSolution(CNPSolution* solution) {
	if (_T <= 0 || _annealingFactor <= 0){
		cerr << "Simulated annealing has not been initialised" << endl;
		exit(-1);
	}

	if (_solution != NULL){
		cerr << "No se debe invocar m醩 de una vez el m閠odo CNPSimulatedAnnealing::setSolution" << endl;
		exit(1);
	}

	this->_solution = solution;

	if (_bestSolution == NULL){
		_bestSolution = new CNPSolution(*_instance);
	}

	_bestSolution->copy(*solution);
}


void CNPSimulatedAnnealing::run(CNPStopCondition& stopCondition) {

	if (_T <= 0 || _annealingFactor <= 0){
		cerr << "Simulated annealing has not been initialised" << endl;
		exit(-1);
	}

	if (_solution == NULL){
		cerr << "Simulated annealing has not been given an initial solution" << endl;
		exit(-1);
	}

	_results.clear();
	unsigned numNodes = _instance->getNumNodes();
	unsigned numIterations = 0;
	CNPSolution newSol;

	/**
	 * hecho
	 * Mientras que no se alcance la condici贸n de parada
	 *   1. Generar aleatoriamente un objeto y una mochila (incluida la mochila 0)
	 *   2. Calcular la diferencia en fitness de aplicar dicho cambio sobre _solution
	 *   3. Consultar si se acepta el cambio
	 *   4. Actualizar la mejor soluci贸n hasta el momento.
	 *   5. Si se llevan _itsPerAnnealing tras el 煤ltimo enfriamiento, entonces enfriar
	 */
	while (stopCondition.reached() == false){
		unsigned indexNode = rand()%numNodes;
		unsigned indexNode2= rand()%numNodes;

		//Se controla debido al alto coste de evaluar el fitness
		while(_solution->getNode(indexNode)==_solution->getNode(indexNode2)){
			indexNode = rand()%numNodes;
			indexNode2= rand()%numNodes;
		}

		//Intercambio de estados
		newSol.copy(*_solution);
		newSol.setNode(indexNode,newSol.getNode(indexNode2));
		newSol.setNode(indexNode2,newSol.getNode(indexNode));

		//evaluacion fitness, ACTUAL-ANTERIOR
		double deltaFitness=CNPEvaluator::computeFitness(*_instance,newSol)-_sol->getFitness();

		if (accept(deltaFitness)){
			_solution->copy(newSol);

			if (_solution->getFitness()-_bestSolution->getFitness() < 0){
				_bestSolution->copy(*_solution);
			}
		}
		numIterations++;
		_results.push_back(_solution->getFitness());

		if (numIterations % _itsPerAnnealing == 0 ){
			_T *= _annealingFactor;
		}

		stopCondition.notifyIteration();
	}
}


bool CNPSimulatedAnnealing::accept(double deltaFitness) {
	/**
	 * hecho
	 * .Calcular la probabilidad de aceptar el cambio, que ser谩 la exponencial de (la diferencia de fitness dividido por la temperatura)
	 *
	 * .Si el problema es de minimizaci贸n, entonces un delta fitness negativo es bueno. Hay que modificar "un poco" la funci贸n de aceptaci贸n para producir una probabilidad de aceptaci贸n superior a 1
	 *
	 * .Generar un aleatorio entre 0 y 1
	 * .Devolver true si el aleatorio es inferior a la probabilidad de aceptaci贸n.
	 *
	 * (piensa qu茅 ocurre cuando la diferencia de fitness es positiva o cuando es negativa)
	 */
	double auxDeltaFitness = deltaFitness;

//	if (MQKPEvaluator::isToBeMinimised()){
		if(auxDeltaFitness<=0)
			return true;
//	}

	double prob = exp(auxDeltaFitness/_T);
	double randSample = (((double)rand()) / RAND_MAX);
	if(randSample < prob){
	return (true);
	}
	return false;
}


void CNPSimulatedAnnealing::initialise(double initialProb, int numInitialEstimates, double annealingFactor, unsigned itsPerAnnealing, CNPInstance &instance) {
	_initialProb = initialProb;
	_annealingFactor = annealingFactor;
	_instance = &instance;
	_itsPerAnnealing = itsPerAnnealing;
	int numObjs = instance.getNumNodes();
	double averageFDiffs = 0.;

	/**
	 * Inicializaci髇 de la temperatura.
	 * Para ello, se generan una serie de soluciones iniciales y de vecinos. Se calcula la diferencia media de fitness hacia peores soluciones y se despeja la temperatura de la funci髇 de aceptaci髇.
	 */

	for (int i=0; i<numInitialEstimates; i++){
		CNPSolution sol(instance);
		CNPSolGenerator::genRandomSol(instance, sol);
		sol.setFitness(CNPEvaluator::computeFitness(instance, sol));

		unsigned indexNode = rand()%numNodes;
		unsigned indexNode2= rand()%numNodes;

		while(_solution->getNode(indexNode)==_solution->getNode(indexNode2)){
			indexNode = rand()%numNodes;
			indexNode2= rand()%numNodes;
		}

		//Intercambio de estados
		newSol.copy(*_solution);
		newSol.setNode(indexNode,newSol.getNode(indexNode2));
		newSol.setNode(indexNode2,newSol.getNode(indexNode));

		//evaluacion fitness, ACTUAL-ANTERIOR
		double deltaFitness=CNPEvaluator::computeFitness(*_instance,newSol)-_sol->getFitness();

		averageFDiffs += max(fabs(deltaFitness),10.); //He puesto una diferencia m铆nima de 10 para evitar cambios en el fitness demasiado peque帽os (por ejemplo, cuando se modifica una mochila que no es la de la m谩xima violaci贸n (este m茅todo se podr铆a mejorar)
	}

	averageFDiffs /= numInitialEstimates;

	_T = -1. * averageFDiffs / log(initialProb);
}
