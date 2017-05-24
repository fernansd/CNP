/*
 * CNPIteratedGreedy.h
 */

#ifndef INCLUDE_CNPITERATEDGREEDY_H_
#define INCLUDE_CNPITERATEDGREEDY_H_

#include <CNPMetaheuristic.h>
#include <CNPSolution.h>
#include <CNPObjectAssignmentOperation.h>


class CNPIteratedGreedy : public CNPMetaheuristic{
protected:

	/**
	 * Variables miembro de la clase
	 * _alpha guarda la probabilidad.
	 * _instance tiene un puntero a la instancia del problema abordada
	 * _sol tiene la solución sobre la que trabaja Iterated Greedy durante las destrucciones y construcciones
	 */
	double _alpha;
	CNPInstance *_instance;
	CNPSolution *_sol;

	/**
	 * vector de doubles donde almacena la calidad de la última solución aceptada
	 */
	vector<double> _results;

	/**
	 * Función que devuelve la mejor operación 
	 */
	void chooseOperation(CNPObjectAssignmentOperation &operation, std::vector<double>& centrls);

	/**
	 * Función que reconstruye la solución _sol. Para ello, invoca repetidamente a la función chooseOperation hasta que no encuentra ninguna otra operación de asignación que mejore la solución actual.
	 * Los cambios se van almacenando en la variable miembro _sol.
	 */
	void rebuild();

	/**
	 * Función que destruye parcialmente la solución _sol. 
	 */
	void destroy();

public:
	/**
	 * Constructor
	 */
	CNPIteratedGreedy(){
		_alpha = 0.;
		_instance = NULL;
		_sol = NULL;
	}

	/**
	 * Destructor
	 */
	virtual ~CNPIteratedGreedy(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}

		if (_sol != NULL){
			delete _sol;
			_sol = NULL;
		}
	}

	/**
	 * Función que inicializa ciertos parámetros de la metaheurística.
	 * En particular, las variables miembro _sol y _bestSolution y la probabilidad alpha
	 * @param[in] alpha Probabilidad entre 0 y 1 de sacar objetos de sus mochilas en la fase de destrucción
	 * @param[in] instance Instancia del problema que se va a abordar
	 */
	void initialise(double alpha, CNPInstance &instance);

	/**
	 * Función que ejecuta la metaheurística hasta alcanzar la condición de parada
	 * @param[in] stopCondition Condición de parada para la metaheurística
	 */
	virtual void run(CNPStopCondition &stopCondition);

	/**
	 * Función que devuelve el vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 *
	 * @return vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 */
	vector<double>& getResults() {
		return _results;
	}
};



#endif /* INCLUDE_CNPITERATEDGREEDY_H_ */
