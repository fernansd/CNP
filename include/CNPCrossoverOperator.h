/*
 * CNPCrossoverOperator.h
 *
 * Fichero que define la clase CNPCrossoverOperator. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Undead Corp
 */

#ifndef INCLUDE_CNPCROSSOVEROPERATOR_H_
#define INCLUDE_CNPCROSSOVEROPERATOR_H_

#include <CNPSolution.h>
#include <Solution.h>
#include <CNPInstance.h>
#include <vector>

using namespace std;

/**
 * Clase que implementa un operador de cruce uniforme para el problema CNP. Su idea es la misma que la de un cruce uniforme para codificación entera
 */
class CNPCrossoverOperator {

protected:
	/**
	 * Variables miembro de la clase:
	 *  - _instance Instancia de problema abordada. Se utiliza únicamente para crear nuevos objetos CNPSolution
	 *  - _numNodes almacena el número de objetos de la instancia abordada para reducir el número de consultas a la instancia
	 *  - _crossProb probabilidad de cruce
	 */
	CNPInstance *_instance;
	unsigned _numNodes;
	double _crossProb;

	/**
	 * Función que cruza dos soluciones según su probabilidad de cruce. En caso de que no haya crucce, la solución devuelta será igual al primer padre
	 * @param[in] s1 primer padre
	 * @param[in] s2 segundo padre
	 * @return Nuevo objeto solución descendiente de haber cruzado s1 y s2. La solución se reserva dinámicamente en memoria. Es responsabilidad del invocador de gestionarla correctamente.
	 */
	CNPSolution * cross(Solution *s1, Solution *s2) {
		CNPSolution * sol = new CNPSolution(*_instance);
		CNPSolution * sol1 = (CNPSolution *) s1;
		CNPSolution * sol2 = (CNPSolution *) s2;

		int prob=0;
		int indexNode;

		double randSample = (((double) rand()) / RAND_MAX);

		if (randSample < _crossProb) {

			while(sol->getNumCrit()<sol->getNumCritMax()){
				indexNode=rand()%_numNodes;														//No hay control de repetidos ya que se tarda menos generando incluso ya cogidos y setNode no incrementa NumCrit si ya estaba a true

				if((sol1->getNode(i)==true)&&(sol2->getNode(i)==true)){							//Ambos son 1
					prob=85;
				}else if(!((sol1->getNode(i)==false)&&(sol2->getNode(i)==false))){				//Ambos distintos
					prob=50;
				}

				if((rand()%100)+1<=prob){
					sol->setNode(indexNode,true);
				}

			}

		} else {
			//Si no hay cruce, copiar el primer padre
			sol->copy(*sol1);
			sol->setValidFitness(true); 		//Evitamos evaluar de nuevo
		}

		return sol;
	}

public:

	/**
	 * Constructor
	 * @param[in] crossProb Probabilidad de cruce
	 * @param[in] instance Instancia del problema abordada
	 */
	CNPCrossoverOperator(double crossProb, CNPInstance &instance) {
		_instance = &instance;
		_numNodes = instance.getNumNodes();
		_crossProb = crossProb;
	}

	/**
	 * Función que aplica el cruce a una población de padres.
	 * @param[in] parents Vector de padres. El cruce se aplica entre cada dos padres consecutivos (1,2), (3,4)...
	 * @param[out] offspring Vector donde se almacenan los descendientes generados. IMPORTANTE: Esta función reserva memoria dinámicamente para las nuevas soluciones en offspring, por lo que es responsabilidad de quien la invoque de gestionar la memoria adecuadamente.
	 */
	void cross(vector<Solution*> &parents, vector<Solution*> &offspring) {

		unsigned numParents = (unsigned) parents.size();

		//TODO aplicar cruce entre cada dos padres consecutivos (1,2), (3,4), ...
		for (unsigned i=0;i<numParents;i=i+2) {
			CNPSolution *sol = cross(parents[i],parents[i+1]);
			offspring.push_back(sol);
		}
	}
};

#endif /* INCLUDE_CNPCROSSOVEROPERATOR_H_ */
