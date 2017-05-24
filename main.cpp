//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Programa principal del proyecto de Metaheurísticas
//============================================================================

//Definición de algunos parámetros de la experimentación
#define MAX_SECONDS_PER_RUN 10
#define MAX_SOLUTIONS_PER_RUN 100000
#define NUM_RUNS 5

#include <CNPInstance.h>
#include <CNPEvaluator.h>
#include <CNPSolGenerator.h>
#include <CNPSolution.h>
#include <Timer.h>
#include <CNPSimulatedAnnealing.h>
#include <CNPStopCondition.h>
#include <CNPIteratedGreedy.h>
#include <CNPTabuSearch.h>
#include <CNPGrasp.h>
#include <CNPGeneticAlgorithm.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cfloat>

using namespace std;


//Definición externa de las semillas para el generador de números aleatorios (en seeds.cpp)
extern unsigned int numSeeds;
extern unsigned int seeds[];

/**
 * Función que realiza la generación de soluciones aleatorias, durante MAX_SECONS_PER_RUN segundos y un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] results vector donde se almacenarán los valores fitness de las soluciones aleatorias que se generen
 * @param[in] insstance Instancia del problema de la mochila cuadrática múltiple
 */
void runARandomSearchExperiment(vector<double> &results, CNPInstance &instance){

	CNPSolution currentSolution(instance);
	Timer t;
	unsigned int numSolutions = 0;

	//Mientras no se acabe el tiempo y no se generen demasiadas soluciones, generar solución aleatoria y guardar el resultado
	while (t.elapsed_time(Timer::VIRTUAL) <= MAX_SECONDS_PER_RUN && numSolutions < MAX_SOLUTIONS_PER_RUN){
		CNPSolGenerator::genRandomSol(instance, currentSolution);
		double currentFitness = CNPEvaluator::computeFitness(instance, currentSolution);
		results.push_back(currentFitness);
		numSolutions++;
	}
}

/**
 * Función que ejecuta el enfriamiento simulado, durante MAX_SECONS_PER_RUN segundos, un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] currentResults vector donde se almacenarán los valores fitness de las soluciones que va aceptando el enfriamiento simulado.
 * @param[out] bestSoFarResults vector donde se almacenarán los mejores valores fitness generados hasta el momento
 * @param[in] instance Instancia del problema de la mochila cuadrática múltiple
 */
void runASAExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, CNPInstance &instance) {

	//Inicialización
	CNPSolution initialSolution(instance);
	CNPSimulatedAnnealing sa;
	CNPStopCondition stopCond;
	CNPEvaluator::resetNumEvaluations();
	sa.initialise(0.9, 10, 0.98888, 10, instance); //cambiado el segundo 10 antes ponia un 50 lo digo el de practicas
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONDS_PER_RUN);

	//Generar solución aleatoria
	CNPSolGenerator::genRandomSol(instance, initialSolution);
	double currentFitness = CNPEvaluator::computeFitness(instance,
			initialSolution);
	initialSolution.setFitness(currentFitness);
	double bestFitness = currentFitness;
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);
	sa.setSolution(&initialSolution);

	//Aplicar SA
	sa.run(stopCond);

	//Almacenar los resultados
	vector<double> &resultsSA = sa.getResults();

	for (auto aResult : resultsSA) {
		currentResults.push_back(aResult);
		bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
	}
}

/**
 * Función que realiza la generación de soluciones aleatorias, durante MAX_SECONS_PER_RUN segundos y un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] results vector donde se almacenarán los valores fitness de las soluciones aleatorias que se generen
 * @param[in] insstance Instancia del problema de la mochila cuadrática múltiple
 */
void runAIGExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, CNPInstance &instance) {

	//Inicialización
	CNPSolution initialSolution(instance);
	CNPIteratedGreedy ig;
	CNPStopCondition stopCond;
	CNPEvaluator::resetNumEvaluations();
	ig.initialise(0.25, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONDS_PER_RUN);


	//Generar solución aleatoria para inicialiar la mejor solución
	//CNPSolGenerator::genRandomSol(instance, initialSolution);

	double currentFitness = CNPEvaluator::computeFitness(instance,initialSolution);

	initialSolution.setFitness(currentFitness);
	double bestFitness = currentFitness;
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);


	//Aplicar IG
	ig.run(stopCond);

	//Almacenar los resultados
	vector<double> &resultsIG = ig.getResults();

	for (auto aResult : resultsIG) {
		currentResults.push_back(aResult);
		bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
	}
}

/**
 * Función que ejecuta la búsqueda tabú, durante MAX_SECONS_PER_RUN segundos, un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] currentResults vector donde se almacenarán los valores fitness de las soluciones que va aceptando el enfriamiento simulado.
 * @param[out] bestSoFarResults vector donde se almacenarán los mejores valores fitness generados hasta el momento
 * @param[in] instance Instancia del problema de la mochila cuadrática múltiple
 */
void runATSExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, CNPInstance &instance) {

	//Inicialización
	CNPSolution initialSolution(instance);
	CNPTabuSearch ts;
	CNPStopCondition stopCond;
	CNPEvaluator::resetNumEvaluations();
	ts.initialise(&instance, ((unsigned)(instance.getNumNodes() / 10)));
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONDS_PER_RUN);

	//Generar solución aleatoria
	CNPSolGenerator::genRandomSol(instance, initialSolution);
	double currentFitness = CNPEvaluator::computeFitness(instance,
			initialSolution);
	initialSolution.setFitness(currentFitness);
	double bestFitness = currentFitness;
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);
	ts.setSolution(&initialSolution);

	//Aplicar TS
	ts.run(stopCond);

	//Almacenar los resultados
	vector<double> &resultsTS = ts.getResults();

	for (auto aResult : resultsTS) {
		currentResults.push_back(aResult);
		bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
	}
}

/**
 * Función que ejecuta la búsqueda GRASP, durante MAX_SECONS_PER_RUN segundos, un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] currentResults vector donde se almacenarán los valores fitness de las soluciones que va aceptando el enfriamiento simulado.
 * @param[out] bestSoFarResults vector donde se almacenarán los mejores valores fitness generados hasta el momento
 * @param[in] instance Instancia del problema de la mochila cuadrática múltiple
 */
void runAGraspExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, CNPInstance &instance) {

	//Inicialización
	CNPSolution initialSolution(instance);
	CNPGrasp grasp;
	CNPStopCondition stopCond;
	CNPEvaluator::resetNumEvaluations();
	grasp.initialise(0.25, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONDS_PER_RUN);

	//Generar solución aleatoria para inicialiar la mejor solución
	CNPSolGenerator::genRandomSol(instance, initialSolution);
	double currentFitness = CNPEvaluator::computeFitness(instance,
			initialSolution);
	initialSolution.setFitness(currentFitness);
	double bestFitness = currentFitness;
	currentResults.push_back(currentFitness);
	bestSoFarResults.push_back(bestFitness);

	//Aplicar GRASP
	grasp.run(stopCond);

	//Almacenar los resultados
	vector<double> &resultsGRASP = grasp.getResults();

	for (auto aResult : resultsGRASP) {
		currentResults.push_back(aResult);
		bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
	}
}

/**
 * Función que ejecuta el algoritmo evolutivo, durante MAX_SECONS_PER_RUN segundos, un máximo de MAX_SOLUTIONS_PER_RUN, para la instancia proporcionada
 * @param[out] currentResults vector donde se almacenarán los valores fitness de las soluciones que se van generando.
 * @param[out] bestSoFarResults vector donde se almacenarán los mejores valores fitness generados hasta el momento
 * @param[out] bestPerIterations vector donde se almacenarán los mejores valores fitness de cada generación
 * @param[out] popMean vector donde se almacenarán los valores fitness medios de cada generación
 * @param[out] offMean vector donde se almacenarán los valores fitness medios de la población de descendientes
 * @param[in] instance Instancia del problema de la mochila cuadrática múltiple
 */
void runAGAExperiment(vector<double> &currentResults,
		vector<double> &bestSoFarResults, vector<double> &bestPerIterations,
		vector<double> &popMean, vector<double> &offMean,
		CNPInstance &instance) {

	//Inicialización
	CNPGeneticAlgorithm ga;
	CNPStopCondition stopCond;
	CNPEvaluator::resetNumEvaluations();
	ga.initialise(60, instance);
	stopCond.setConditions(MAX_SOLUTIONS_PER_RUN, 0, MAX_SECONDS_PER_RUN);

	//Ejecutar el GA
	ga.run(stopCond);

	//Almacenar los resultados
	vector<double> &resultsGA = ga.getResults();

	for (double aResult : resultsGA) {
		currentResults.push_back(aResult);

		if (bestSoFarResults.size() > 0)
			bestSoFarResults.push_back(max(bestSoFarResults.back(), aResult));
		else
			bestSoFarResults.push_back(aResult);
	}

	bestPerIterations = ga.getBestsPerIterations();
	popMean = ga.getPopMeanResults();
	offMean = ga.getOffMeanResults();
}

/**
 * Función que ejecuta todos los experimentos para los argumentos pasados al programa principal, en particular NUM_RUNS experimentos para cada instancia
 * @param[out] results matriz 3D donde se almacenarán los resultados. El primer índice será para la instancia considerada. El segundo para el experimento sobre dicha instancia. El tercero para la solución generada en dicho experimento
 * @param[in] mainArgs Argumentos de la función main (argv). En los argumentos vienen, desde el índice 1, <nombre del fichero de la instancia 1> <número de mochilas> <nombre del fichero de la instancia 2> <número de mochilas>...
 * @param[in] numMainArgs Número de argumentos de la función main (argc)
 */
void runExperiments(vector< vector< vector< double>* >* > &results, char **mainArgs, unsigned int numMainArgs){

	//Para cada instancia del problema
	for (unsigned int iInstance = 1; iInstance < numMainArgs; iInstance += 2){

		//Leer la instancia y crear la estructuras de datos necesarias para guardar los resultados
		CNPInstance instance;
		vector< vector < double >* >* resultsOnThisInstance = new vector< vector< double >* >;
		results.push_back(resultsOnThisInstance);
		char *instanceName = mainArgs[iInstance];
		unsigned int numNodes = atoi(mainArgs[iInstance + 1]);
		instance.readInstance(instanceName, numNodes);

		/* Ejecutar aleatorio
		//Lanzar NUM_RUNS ejecuciones sobre dicha instancia
		for (unsigned int r = 1; r <= NUM_RUNS && r < numSeeds; r++){
			srand(seeds[r]); //Inicialización del generador de números aleatorios al inicio de cada ejecución
			vector<double> *theseResults = new vector<double>;
			resultsOnThisInstance->push_back(theseResults);
			runARandomSearchExperiment(*theseResults, instance);
		}*/

		vector<double> *theseFirstResults;
		vector<double> *bestFirstResults;

		/*//Ejecutar el enfriamientoSimulado
		theseFirstResults = new vector<double>;
		bestFirstResults = new vector<double>;
		resultsOnThisInstance->push_back(theseFirstResults);
		resultsOnThisInstance->push_back(bestFirstResults);
		runASAExperiment(*theseFirstResults, *bestFirstResults, instance);*/

		/*//Ejecutar la búsqueda tabú *
		theseFirstResults = new vector<double>;
		bestFirstResults = new vector<double>;
		resultsOnThisInstance->push_back(theseFirstResults);
		resultsOnThisInstance->push_back(bestFirstResults);
		runATSExperiment(*theseFirstResults, *bestFirstResults, instance);*/

		/*//Ejecutar la búsqueda GRASP */
		theseFirstResults = new vector<double>;
		bestFirstResults = new vector<double>;
		resultsOnThisInstance->push_back(theseFirstResults);
		resultsOnThisInstance->push_back(bestFirstResults);
		runAGraspExperiment(*theseFirstResults, *bestFirstResults, instance);

		/*//Ejecutar la búsqueda Iterated Greedy
		theseFirstResults = new vector<double>;
		bestFirstResults = new vector<double>;
		resultsOnThisInstance->push_back(theseFirstResults);
		resultsOnThisInstance->push_back(bestFirstResults);
		runAIGExperiment(*theseFirstResults, *bestFirstResults, instance);*/

		//Ejecutar el algoritmo evolutivo
		vector<double> *theseResults = new vector<double>;
		vector<double> *bestResults = new vector<double>;
		vector<double> *bestPerIterations = new vector<double>;
		vector<double> *popMeanResults = new vector<double>;
		vector<double> *offMeanResults = new vector<double>;
		resultsOnThisInstance->push_back(theseResults);
		resultsOnThisInstance->push_back(bestResults);
		resultsOnThisInstance->push_back(bestPerIterations);
		resultsOnThisInstance->push_back(popMeanResults);
		resultsOnThisInstance->push_back(offMeanResults);
		runAGAExperiment(*theseResults, *bestResults, *bestPerIterations,
				*popMeanResults, *offMeanResults, instance);
	}
}

/**
 * Función que devuelve el número de soluciones en la ejecución con más soluciones
 * @param[in] results Matriz 2D con los resultados de las distintas ejecuciones. El primer índice es para las ejecuciones. El segundo es para las soluciones de una misma ejecución
 * @return Número de soluciones en la ejecución con más soluciones.
 */
unsigned int getLongestRunLength(vector< vector< double >* > &results){

	unsigned int maxLength = 0;
	unsigned int numRuns = (unsigned)results.size();

	for (unsigned int iRun = 0; iRun < numRuns; iRun++){

		unsigned int length = (unsigned)results.at(iRun)->size();
		if (length > maxLength){
			maxLength = length;
		}
	}

	return maxLength;
}

/**
 * Estructura para calcular y almacenar los datos de salida del programa, media de las soluciones de la iteración actual y media de las mejores soluciones desde el inicio hasta la iteración actual
 */
struct currentBestPair{
	double current;
	double best;
};

/**
 * Función que calcula las medidas de los resultados de varias ejecuciones.
 * @param[in] results Matriz 2D con los resultados de las distintas ejecuciones. El primer índice es para las ejecuciones. El segundo es para las soluciones de una misma ejecución
 * @param[out] means Vector donde se almacenan los resultados medios en datos de tipo currentBestPair, es decir, con la media de las soluciones generadas en la iteración actual y la media de las mejores soluciones generadas desde el inicio hasta la iteración actual
 * @return Devuelve el número de elementos en el vector de salida means
 */
unsigned int computeMeans(vector< vector<double>* > &results, vector<currentBestPair> &means){
	//Obtener el número de soluciones en la ejecución más larga
	unsigned int longestRunLength = getLongestRunLength(results);
	unsigned int numRuns = (unsigned)results.size();
	currentBestPair previousMean;
	previousMean.best = -DBL_MAX;

	//Calcular la media
	for (unsigned int iSolutions = 0; iSolutions < longestRunLength; iSolutions++){
		currentBestPair currentMean;
		currentMean.current = 0;
		currentMean.best = 0;
		double value;

		if (iSolutions == 0){

			for (unsigned int iRun = 0; iRun < numRuns; iRun++){

				unsigned int length = (unsigned)results.at(iRun)->size();
				if (length <= iSolutions){
					value = results.at(iRun)->back();
					currentMean.current += value;
				}else{
					value = results.at(iRun)->at(iSolutions);
					currentMean.current += value;
				}

				currentMean.best += value;
			}
		}
		else {
			for (unsigned int iRun = 0; iRun < numRuns; iRun++){

				unsigned int length = (unsigned)results.at(iRun)->size();
				if (length <= iSolutions){
					value = results.at(iRun)->back();
					currentMean.current += value;
				}else{
					value = results.at(iRun)->at(iSolutions);
					currentMean.current += value;
				}

				currentMean.best += max(value, previousMean.best);
			}
		}

		currentMean.current /= numRuns;
		currentMean.best /= numRuns;
		means.push_back(currentMean);
		previousMean.best = currentMean.best;
	}

	return longestRunLength;
}

/**
 * Función que libera la memoria de un vector 2D
 * @param[in] array vector 2D que se va a liberar de memoria
 */
template <typename T>
void free2Darray(vector< vector<T>* > &array){

	unsigned int numVectors = (unsigned)array.size();

	for (unsigned i = 0; i < numVectors; i++){
		array.at(i)->clear();
		delete (array.at(i));
	}

	array.clear();
}

/**
 * Función que libera la memoria de un vector 3D
 * @param[in] array matriz 3D que se va a liberar de memoria
 */
template <typename T>
void free3Darray(vector< vector <vector<T>*>*> &array){

	unsigned int numArrays = (unsigned)array.size();

	for (unsigned i = 0; i < numArrays; i++){
		free2Darray(*(array.at(i)));
		delete (array.at(i));
	}

	array.clear();
}

/**
 * Función main que ejecuta la experimentación. Generación de soluciones aleatorias para las instancias
 *
 * Finalmente se escribe en la salida estandar los resultados generados en forma de matriz. Por cada instancia se generan dos columnas, una con los resultados
 * medios de las soluciones generadas en cada iteración y otra con los resultados medios de las mejores soluciones generadas desde el inicio hasta dicha iteración
 */
int main(int argc, char **argv) {

	if (argc < 3 || (argc % 2) != 1){
		cout << argv[0] << " (<problem instance files> <numNodes>)+" << endl;
		return 0;
	}



	//////////////////////////
	//Ejecución de experimentos
	//////////////////////////
	unsigned int numInstances = (argc - 1) / 2;
	vector< vector< vector< double >* >* > allTheResults;
	srand(seeds[0]);
	//En la matriz allTheResults se almacenarán todos los valores de fitness generados
	//Es tridimensional
	//El primer índice recorre las instancias de los problemas que se han abordado
	//El segundo índice recorre las ejecuciones que se han hecho sobre la misma instancia
	//El tercer índice recorre las soluciones que se han generado en la misma ejecución

	runExperiments(allTheResults, argv, argc);



	/*//Aleatorio
	////////////////////////////
	//Calculo de los valores medios
	////////////////////////////
	unsigned int overallMaxNumResults = 0;
	vector< vector< currentBestPair>* > meanResults;
	//En la matriz meanResults se almacenarán los resultados pero haciendo la media en cada iteración de la búsqueda (Media de las primeras soluciones de las diferentes ejecuciones, igual de las segundas soluciones, etc.)
	//Es bidimensional
	//El primer índice recorre las instancias de los problemas que se han abordado
	//El segundo índice recorre los valores medios calculados por cada iteración del método

	//Para cada instancia del problema, calcular sus medias
	for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++){

		vector< vector< double >* > *resultsThisInstance = allTheResults.at(iInstance);
		vector< currentBestPair > *theseMeans = new vector<currentBestPair>;
		meanResults.push_back(theseMeans);
		unsigned int numResults = computeMeans(*resultsThisInstance, *theseMeans);

		if (numResults > overallMaxNumResults){
			overallMaxNumResults = numResults;
		}
	}*/



	//////////////////////
	// Impresión de resultados
	//////////////////////
	/*// Aleatorio
	for (int iInstance = 1; iInstance < argc; iInstance += 2){
		cout << argv[iInstance] << "_" << argv[iInstance + 1] << "_bestRand\t";
		cout << argv[iInstance] << "_" << argv[iInstance + 1] << "_currentRand\t";
	}
	cout << endl;

	for (unsigned int iIteration = 0; iIteration < overallMaxNumResults; iIteration++){
		for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++){
			cout << meanResults.at(iInstance)->at(iIteration).best << "\t";
			cout << meanResults.at(iInstance)->at(iIteration).current << "\t";
		}
		cout << endl;
	}*/

	// SA, TS, IG
	vector<double> lastResults;
	for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++){
		/*cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_currentSA\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_bestSA\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_currentTS\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_bestTS\t";*/
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_currentGrasp\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_bestGrasp\t";
		/*cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_currentIG\t";
		cout << argv[iInstance*2+1] << "_" << argv[iInstance*2+2] << "_bestIG\t";*/
		lastResults.push_back(allTheResults.at(iInstance)->at(0)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(1)->at(0));
		/*lastResults.push_back(allTheResults.at(iInstance)->at(2)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(3)->at(0));*/
		/*lastResults.push_back(allTheResults.at(iInstance)->at(4)->at(0));
		lastResults.push_back(allTheResults.at(iInstance)->at(5)->at(0));*/
	}
	cout << endl;
	bool allResultsPrinted = false;
	unsigned int iIteration = 0;
	unsigned int indexColumn = 0;

	while (allResultsPrinted == false){
		allResultsPrinted = true;
		for (unsigned int iInstance = 0; iInstance < numInstances; iInstance++){

			// 1 Metaheurística
			if (allTheResults.at(iInstance)->at(0)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(0)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(0)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;

			if (allTheResults.at(iInstance)->at(1)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(1)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(1)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;

			/*// 2 Metaheurísticas
			if (allTheResults.at(iInstance)->at(2)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(2)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(2)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;

			if (allTheResults.at(iInstance)->at(3)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(3)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(3)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;*/
			/*
			// 3 Metaheurísticas
			if (allTheResults.at(iInstance)->at(4)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(4)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(4)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;

			if (allTheResults.at(iInstance)->at(5)->size() > iIteration){
				allResultsPrinted = false;
				cout << allTheResults.at(iInstance)->at(5)->at(iIteration) << "\t";
				lastResults[indexColumn] = allTheResults.at(iInstance)->at(5)->at(iIteration);
			} else {
				cout << lastResults[indexColumn] << "\t";
			}
			indexColumn++;
			*/
		}
		cout << endl;
		iIteration++;
		indexColumn = 0;
	}




	//////////////////////
	// Liberar memoria
	//////////////////////
	free3Darray(allTheResults);
	/*// Aleatorio
	free2Darray(meanResults);*/

	return 0;
}
