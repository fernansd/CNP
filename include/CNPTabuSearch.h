/*	CNPTabuSearch.h
 *
 * Fichero que define la clase CNPTabuSearch. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_CNPTABUSEARCH_H_
#define INCLUDE_CNPTABUSEARCH_H_

#include <CNPSolution.h>
#include <CNPInstance.h>
#include <CNPMetaheuristic.h>
#include <CNPStopCondition.h>
#include <cstdlib>
#include <queue>
#include <set>

using namespace std;

/**
 * Clase que implementa una Búsqueda Tabú para el problema CNP. Utiliza únicamente la memoria a corto plazo que impide cualquier operación sobre un nodo sobre el cual se aplicó una operación recientemente
 */

class CNPTabuSearch : public CNPMetaheuristic{
protected:

	/**
	 * Variables miembro
	 * _solution Solución al CNP sobre la que trabaja la búsqueda tabú
	 * _instance Instancia del problema que aborda la metaheurística
	 * _shortTermMem cola que implementa la memoria a corto plazo de la búsqueda tabú
	 * _shortTermMem_aux estructura auxiliar para hacer más eficiente el comprobar que un elemento se encuentra en la memoria tabú
	 * _tabuTennure Tenencia tabú de la metaheurística
	 */
	CNPSolution *_solution;
	CNPInstance *_instance;
	queue<unsigned> _shortTermMem;
	set<unsigned> _shortTermMem_aux;
	unsigned _tabuTennure;

	/**
	 * vector de doubles donde almacena la calidad de la última solución aceptada
	 */
	vector<double> _results;

public:
	/**
	 * Constructor
	 */
	CNPTabuSearch(){
		_solution = NULL;
		_instance = NULL;
		_tabuTennure = 0;
	}

	/**
	 * Destructor
	 */
	virtual ~CNPTabuSearch(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	}

	/**
	 * Función que inicializa la metaheurística
	 * @param[in] instance Instancia del problema a abordar
	 * @param[in] tabuTennure Tenencia tabú de la metaheurística
	 */
	void initialise(CNPInstance * instance, unsigned tabuTennure);

	/**
	 * Función que asigna la solución sobre la cual trabajará la búsqueda tabú
	 * @param[in] solution Solución inicial sobre la que trabajará la búsqueda tabú
	 */
	void setSolution(CNPSolution* solution);

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

#endif
