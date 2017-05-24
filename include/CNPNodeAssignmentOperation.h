/* CNPNodeAssignmentOperation.h
 *
 * Fichero que declara la clase CNPNodeAssignmentOperation. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#ifndef __CNPNodeASSIGNMENTOPERATION_H__
#define __CNPNodeASSIGNMENTOPERATION_H__

#include <CNPChangeOperation.h>
#include <CNPSolution.h>

/**
 * Clase que codifica una operación de asignación de un objeto a una mochila, pudiendo ser ésta la mochila 0, es decir, sacarlo de la mochila en la que se encuentre
 */
class CNPNodeAssignmentOperation : public CNPChangeOperation {

protected:
	//las variables miembro de la clase según lo indicado en el guión de prácticas (_indexObj, _indexKnapsack, _deltaFitness)
	int _node1;
	int _node2;
	double _deltaFitness;

public:

	/**
	 * Constructor
	 */
	CNPNodeAssignmentOperation();

	/**
	 * Destructor
	 */
	virtual ~CNPNodeAssignmentOperation();

	/**
	 * Función que aplica el cambio que define el propio objeto sobre la solución que recibe como argumento.
	 * @param[in, out] solution Objeto solución sobre el que se aplicará el cambio
	 */
	virtual void apply(CNPSolution &solution);

	/**
	 * Función que asigna los valores la operación
	 * @param[in] indexNode El índice del objeto que se va a cambiar de mochila
	 * @param[in] indexKnapsack El índice de la mochila donde se insertará el objeto
	 * @param[in] deltaFitness La diferencia en fitness de aplicar dicha operación de asignación de un objeto a una mochila (siempre que la solución actual no se hubiese cambiado cuando se calculo dicha diferencia)
	 */
	void setValues(int indexNode, int indexKnapsack, double deltaFitness);

	/**
	 * Función que devuelve el objeto sujeto de la operación
	 * @return índice del objeto sujeto de la operación
	 */
	unsigned getNode1(){
		return _node1;
	}

	/**
	 * Función que devuelve la diferencia en fitness de la operación,
	 * @return Diferencia en fitness de la operación (siempre que la solución actual no se hubiese cambiado cuando se calculo dicha diferencia)
	 */
	double getDeltaFitness(){
		return _deltaFitness;
	}

	/**
	 * Función que devuelve la mochila objeto de la operación
	 * @return mochila objeto de la operación
	 */
	unsigned getNode2(){
		return _node2;
	}
};

#endif
