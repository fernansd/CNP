/*
 * CNPMutationOperator.h
 *
 * Fichero que define la clase CNPMutationOperator. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef INCLUDE_CNPMUTATIONOPERATOR_H_
#define INCLUDE_CNPMUTATIONOPERATOR_H_

#include <CNPSolution.h>
#include <vector>
#include <cstdlib>

using namespace std;

/**
 * Clase que define un operador de mutación para el CNP. Se basa en recorrer todos los genes de la solución y cambiarlos por un valor aleatorio según una probabilidad
 */
class CNPMutationOperator{

protected:
	/**
	 * Variables miembro de la clase
	 * _mutProb Probabilidad de mutación
	 * _numNodes Número de objetos. Se utiliza para reducir el número de consultas a la instancia
	 * _numKnapsacks Número de mochilas del problema. Se utiliza para reducir el número de consultas a la instancia
	 */
	double _mutProb;
	unsigned _numNodes;

	/**
	 * Función que muta una solución
	 * @param[in,out] sol Solución a mutar
	 */
	void mutate(CNPSolution* sol){
		CNPSolution *s = (CNPSolution*) sol;

		unsigned indexNode;
		bool aux,aux2;

		//TOD Recorrer los objetos y, según la probabilidad de mutación,
		//asignarlos a una mochila aleatoria (podrían modificarse 0, 1, o más de 1 gen)

		for(unsigned i=0;i<_numNodes;i++){
			double randSample = (((double) rand()) / RAND_MAX);
			if(_mutProb > randSample){
				aux=s->getNode(i);
				do{
					indexNode=rand()%_numNodes;
					aux2=s->getNode(indexNode);
				}while(aux==aux2);
				s->setNode(i,aux2);						//Intercambio de estados
				s->setNode(indexNode,aux);
				s->setValidFitness(false);
			}
		}
	}

public:
	/**
	 * Constructor
	 * @param[in] mutProb Probabilidad de mutación
	 * @param[in] instance Instancia del problema a abordar
	 */
	CNPMutationOperator(double mutProb, CNPInstance &instance){
		_mutProb = mutProb;
		_numNodes = instance.getNumNodes();
	}

	/**
	 * Función que muta un conjunto de soluciones
	 * @param[in,out] sols Soluciones a mutar
	 */
	void mutate(vector<CNPSolution*> &sols){

		for (CNPSolution* sol : sols){
			mutate(sol);
		}
	}
};



#endif /* INCLUDE_CNPMUTATIONOPERATOR_H_ */
