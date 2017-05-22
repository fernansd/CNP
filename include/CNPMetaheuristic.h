/* CNPMetaheuristic.h*/

#ifndef INCLUDE_CNPMETAHEURISTIC_H_
#define INCLUDE_CNPMETAHEURISTIC_H_

#include <CNPSolution.h>
#include <CNPStopCondition.h>
#include <cstdlib>

class CNPMetaheuristic {

protected:
	CNPSolution *_bestSolution;

public:
	/**
	 * Constructor
	 */
	CNPMetaheuristic(){
		_bestSolution = NULL;
	}

	/**
	 * Destructor
	 */
	virtual ~CNPMetaheuristic(){

		if (_bestSolution != NULL){
			delete _bestSolution;
			_bestSolution = NULL;
		}
	};

	/**
	 * Función que ejecuta la metaheurística hasta alcanzar la condición de parada
	 */
	virtual void run (CNPStopCondition &stopCondition) = 0;


	/**
	 * Función que devuelve la mejor solución encontrada hasta el momento.
	 */
	CNPSolution*& getBestSolution(){
		return _bestSolution;
	}
};



#endif /* INCLUDE_CNPMETAHEURISTIC_H_ */
