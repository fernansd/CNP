/*
 * CNPGrasp.h
 *
 * Fichero que define la clase CNPGrasp. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Undead Corp.
 */

#ifndef INCLUDE_CNPGRASP_H_
#define INCLUDE_CNPGRASP_H_

#include <CNPMetaheuristic.h>
#include <CNPInstance.h>
#include <CNPSolution.h>
#include <CNPLocalSearch.h>
#include <CNPSimpleFirstImprovementNO.h>
#include <CNPNodeAssignmentOperation.h>
#include <vector>

using namespace std;

/**
 * Clase que implementa la metaheurística GRASP, en la variante de construcción de una solución greedy mediante selección de la mejor opción entre una serie de alternativas aleatorias
 */
class CNPGrasp : public CNPMetaheuristic{

protected:

	/**
	 * Variables miembro de la clase
	 * _alpha será un valor en (0,1), que indica el porcentaje de alternativas a evaluar para seleccionar la mejor opción para añadir a la solución que se está construyendo
	 * _instance es un puntero a la instancia del problema
	 * _sol almacena la solución sobre la que trabaja GRASP, durante las construcciones y la aplicación de la búsqueda local
	 * _ls es el método de búsqueda local interno para refinar la solucioes que genera
	 * _no es el operador de vecindario que utiliza la búsqueda local interna
	 */
	double _alpha;
	CNPInstance *_instance;
	CNPSolution *_sol;
	CNPLocalSearch _ls;
	CNPSimpleFirstImprovementNO _no;

	/**
	 * vector de doubles donde almacena la calidad de la última solución aceptada
	 */
	vector<double> _results;

	/**
	 * Función que devuelve la mejor operación de asignación de un objeto sin asignar a una mochila de entre una serie de alternativas seleccionadas de forma aleatoria
	 * @param[out] operation Operación de asignación de un objeto a mochila seleccionada
	 */
	void chooseOperation(CNPNodeAssignmentOperation &operation);

	/**
	 * Función que crea una solución desde la mochila vacía. Para ello, invoca repetidamente a la función chooseOperation hasta que llega un momento en el que no encuentra ninguna otra operación de asignación que mejore la solución actual (de entre las seleccionadas aleatoriamente).
	 * Los cambios se van almacenando en la variable miembro _sol.
	 */
	void buildInitialSolution();

public:
	/**
	 * Constructor
	 */
	CNPGrasp(){
		_sol = NULL;
		_instance = NULL;
		_alpha = 0;
	}

	/**
	 * Destructor
	 */
	virtual ~CNPGrasp(){

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
	 * En particular, las variables miembro _sol y _bestSolution y el porcentaje alpha
	 * @param[in] alpha Porcentaje entre 0 y 1 del número de alternativas aleatorias a evaluar cada vez que escoge la siguiente operación de asignación de un objeto a una mochila para aplicar sobre _sol
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
	 * @return vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 */
	vector<double>& getResults() {
		return _results;
	}
};

#endif /* INCLUDE_CNPGRASP_H_ */
