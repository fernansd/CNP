/*
 * CNPSimulatedAnnealing.cpp
 *
 * Fichero que define las funciones de la clase CNPSimulatedAnnealing.
 *
 * @author: Chacal an�nimo
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
		cerr << "No se debe invocar m�s de una vez el m�todo CNPSimulatedAnnealing::setSolution" << endl;
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
	CNPSolution newSol(*_solution);

	/**
	 * hecho
	 * Mientras que no se alcance la condición de parada
	 *   1. Generar aleatoriamente un objeto y una mochila (incluida la mochila 0)
	 *   2. Calcular la diferencia en fitness de aplicar dicho cambio sobre _solution
	 *   3. Consultar si se acepta el cambio
	 *   4. Actualizar la mejor solución hasta el momento.
	 *   5. Si se llevan _itsPerAnnealing tras el último enfriamiento, entonces enfriar
	 */

	unsigned indexNode;
	unsigned indexNode2;
	bool aux;

	while (stopCondition.reached() == false){

		indexNode = rand()%numNodes;
		indexNode2= rand()%numNodes;

		//Se controla debido al alto coste de evaluar el fitness
		while(_solution->getNode(indexNode)==_solution->getNode(indexNode2)){
			indexNode = rand()%numNodes;
			indexNode2= rand()%numNodes;
		}

		//Intercambio de estados
		newSol.copy(*_solution);
		aux=newSol.getNode(indexNode);
		newSol.setNode(indexNode,newSol.getNode(indexNode2));
		newSol.setNode(indexNode2,aux);

		//evaluacion fitness, ACTUAL-ANTERIOR
		double deltaFitness=CNPEvaluator::computeFitness(*_instance,newSol)-_solution->getFitness();

		if (accept(deltaFitness)){
			_solution->copy(newSol);

			if (_solution->getFitness()-_bestSolution->getFitness() > 0){
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
	 * .Calcular la probabilidad de aceptar el cambio, que será la exponencial de (la diferencia de fitness dividido por la temperatura)
	 *
	 * .Si el problema es de minimización, entonces un delta fitness negativo es bueno. Hay que modificar "un poco" la función de aceptación para producir una probabilidad de aceptación superior a 1
	 *
	 * .Generar un aleatorio entre 0 y 1
	 * .Devolver true si el aleatorio es inferior a la probabilidad de aceptación.
	 *
	 * (piensa qué ocurre cuando la diferencia de fitness es positiva o cuando es negativa)
	 */
	double auxDeltaFitness = deltaFitness;

//	if (MQKPEvaluator::isToBeMinimised()){
		if(auxDeltaFitness>0)
			return true;
//	}

	double prob = exp(auxDeltaFitness/_T);
	double randSample = (((double)rand()) / RAND_MAX);
	if(randSample < prob){
		return true;
	}
	return false;
}


void CNPSimulatedAnnealing::initialise(double initialProb, int numInitialEstimates, double annealingFactor, unsigned itsPerAnnealing, CNPInstance &instance) {
	_initialProb = initialProb;
	_annealingFactor = annealingFactor;
	_instance = &instance;
	_itsPerAnnealing = itsPerAnnealing;
	int numNodes = instance.getNumNodes();
	double averageFDiffs = 0.;

	/**
	 * Inicializaci�n de la temperatura.
	 * Para ello, se generan una serie de soluciones iniciales y de vecinos. Se calcula la diferencia media de fitness hacia peores soluciones y se despeja la temperatura de la funci�n de aceptaci�n.
	 */

	unsigned indexNode;
	unsigned indexNode2;
	bool aux;

	for (int i=0; i<numInitialEstimates; i++){
		CNPSolution sol(instance);
		CNPSolution newSol(sol);
		CNPSolGenerator::genRandomSol(instance, sol);
		CNPEvaluator::computeFitness(instance, sol);

		indexNode = rand()%numNodes;
		indexNode2= rand()%numNodes;

		while(sol.getNode(indexNode)==sol.getNode(indexNode2)){
			indexNode = rand()%numNodes;
			indexNode2= rand()%numNodes;
		}

		//Intercambio de estados
		aux=newSol.getNode(indexNode);
		newSol.setNode(indexNode,newSol.getNode(indexNode2));
		newSol.setNode(indexNode2,aux);

		//evaluacion fitness, ACTUAL-ANTERIOR
		double deltaFitness=CNPEvaluator::computeFitness(instance,newSol)-sol.getFitness();

		averageFDiffs += max(fabs(deltaFitness),10.); //He puesto una diferencia mínima de 10 para evitar cambios en el fitness demasiado pequeños (por ejemplo, cuando se modifica una mochila que no es la de la máxima violación (este método se podría mejorar)
	}

	averageFDiffs /= numInitialEstimates;

	_T = -1. * averageFDiffs / log(initialProb);
}
