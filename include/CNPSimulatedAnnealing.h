/*
 * CNPSimulatedAnnealing.h
 *
 * Fichero que define la clase de CNPSimulatedAnnealing.
 *
 * @author: Chacal anónimo
 */

#ifndef CNPSIMULATEDANNEALING_H_
#define CNPSIMULATEDANNEALING_H_

#include <CNPMetaheuristic.h>
#include <CNPSolution.h>
#include <CNPInstance.h>
#include <vector>
#include <CNPStopCondition.h>
#include <cstdlib>

/**
 * Clase que implementa el Enfriamiento Simulado para el CNP.
 */
class CNPSimulatedAnnealing : public CNPMetaheuristic {

protected:
	/**
	 * Variables:
	 * _T - Temperatura actual del sistema.
	 * _initialProb - Probabilidad inicial con la que se aceptan en media los cambios a peores soluciones.
	 * _annealingFactor - Factor con el que se enfría la temperatura.
	 * _itsPerAnnealing - Número de iteraciones entre dos enfriamientos de la temperatura.
	 * _solution - Solución al CNP sobre la que trabaja el Enfriamiento Simulado.
	 * _instance - Instancia del problema que se está abordando.
	 */
	double _T;
	double _initialProb;
	double _annealingFactor;
	unsigned _itsPerAnnealing;
	CNPSolution *_solution;
	CNPInstance *_instance;

	/**
	 * Vector de doubles donde almacena la calidad de la última solución aceptada.
	 */
	vector<double> _results;

	/**
	 * Función que indica si se acepta la nueva solución según su diferencia en fitness con respecto a la actual.
	 * @param[in] deltaFitness diferencia en fitnees de la nueva soluciÃ³n con respecto a la actual.
	 * @return true si se acepta la nueva solución, false en otro caso.
	 */
	bool accept(double deltaFitness);

public:
	/**
	 * Constructor
	 */
	CNPSimulatedAnnealing(){
		_T = 0;
		_initialProb = 0;
		_annealingFactor = 0;
		_itsPerAnnealing = 0;
		_solution = NULL;
		_instance = NULL;
	}

	/**
	 * Destructor
	 */
	virtual ~CNPSimulatedAnnealing(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	};

	/**
	 * Función que ejecuta la metaheurística hasta alcanzar la condición de parada.
	 * @param[in] stopCondition Condición de parada para la metaheurística.
	 */
	virtual void run(CNPStopCondition &stopCondition);

	/**
	 * Función que asigna la solución inicial para la metaheurística.
	 * @param[in] solution Solución inicial a partir de la cual aplicar el enfriamiento simulado.
	 */
	void setSolution(CNPSolution* solution);

	/**
	 * Función que inicializa ciertos parámetros de la metaheurística, en particular, se calcula la temperatura inicial del sistema según la probabilidad con la que se desean aceptar los primeros cambios a peores soluciones.
	 * @param[in] initialProb Probabilidad con la que se desean aceptar en media los primeros cambios a peor.
	 * @param[in] numInitialEstimates Número de soluciones iniciales sobre las que se estima la temperatura necesaria para aceptar cambios a peores soluciones con la probabilidad indicada.
	 * @param[in] annealingFactor Factor con el cual se enfría la temperatura.
	 * @param[in] itersPerAnnealing Número de iteraciones entre dos enfriamientos de la temperatura.
	 * @param[in] instance Instancia del problema que se va a abordar.
	 */
	void initialise(double initialProb, int numInitialEstimates, double annealingFactor, unsigned itsPerAnnealing, CNPInstance &instance);

	/**
	 * Función que devuelve el vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local.
	 *
	 * @return Vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local.
	 */
	vector<double>& getResults() {
		return _results;
	}
};

#endif /* CNPSIMULATEDANNEALING_H_ */
