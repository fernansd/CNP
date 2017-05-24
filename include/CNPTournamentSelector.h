/*
 * TournamentSelector.h
 *
 * Fichero que define la clase MQKPTournamentSelector. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_TOURNAMENTSELECTOR_H_
#define INCLUDE_TOURNAMENTSELECTOR_H_

#include <Solution.h>
#include <SelectionOperator.h>
#include <vector>

using namespace std;

/**
 * Clase que implementa el operador de selección por torneo
 */
class TournamentSelector : public SelectionOperator{

protected:
	/**
	 * Variables miembro de la clase
	 * _k número de participantes en el torneo
	 */
	unsigned _k;

	/**
	 * Función que selecciona una solución del conjunto mediante torneo
	 * @param[in] set Vector de soluciones
	 * @result Solución seleccionada
	 */
	Solution* selectOne (vector<Solution*> &set){

		/**
		 * Hecho
		 * 1. Seleccionar una solución aleatoria como la actualmente ganadora
		 *
		 * 2. Repetir (_k-1) veces la selección de otra solución aleatoria y el torneo con la actualmente ganadora (mantener la mejor)
		 */
		Solution* best;

		unsigned int tam = (unsigned int)set.size();

		int i = rand()%tam;
		best = set[i];

		for(unsigned j=0;j<_k-1;j++){
			int i = rand()%tam;

			if(best->getFitness()<set[i]->getFitness()){
				best = set[i];
			}
		}
		return best;
	}

public:

	/**
	 * Constructor
	 * @param[in] k Número de participantes en el torneo
	 */
	TournamentSelector(unsigned k){
		_k = k;
	}

	/**
	 * Destructor
	 */
	virtual ~TournamentSelector(){}

	/**
	 * Función que selecciona tantas parejas de padres de un vector como elementos hay en dicho vector
	 * @param[in] orig Vector de soluciones sobre el que aplicar la selección
	 * @param[out] result Vector donde se almacenan las parejas de padres seleccionadas
	 */
	virtual void select(vector<Solution*> &orig, vector<Solution*> &result){

		//HECHO utilizando le método propio selectOne, seleccionar tantas parejas
		//de padres como elementos hay en orig

		//****Preguntar****//
		///Puede que sea meter por cada iteracion dos Solution en result

		//Solution* aux;
		for(int i=0;i<(int)orig.size();i++){
			//aux=selectOne(orig);
			result.push_back(selectOne(orig));
			//aux=selectOne(orig);
			result.push_back(selectOne(orig));
		}
	}
};



#endif /* INCLUDE_TOURNAMENTSELECTOR_H_ */