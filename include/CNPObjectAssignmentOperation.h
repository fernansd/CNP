/* MQKPObjectAssignmentOperation.h
 */

#ifndef __CNPOBJECTASSIGNMENTOPERATION_H__
#define __CNPOBJECTASSIGNMENTOPERATION_H__

#include <CNPChangeOperation.h>
#include <CNPSolution.h>

/**
 * Clase que codifica una operación de asignación de un objeto a una mochila, pudiendo ser ésta la mochila 0, es decir, sacarlo de la mochila en la que se encuentre
 */
class CNPObjectAssignmentOperation : public CNPChangeOperation {

protected:
	//las variables miembro de la clase según lo indicado en el guión de prácticas (_indexObj, _indexKnapsack, _deltaFitness)
	//unsigned _nodeOld;
	unsigned _nodeNew;
	double _deltaFitness;

public:

	/**
	 * Constructor
	 */
	CNPObjectAssignmentOperation();

	/**
	 * Destructor
	 */
	virtual ~CNPObjectAssignmentOperation();

	/**
	 * Función que aplica el cambio que define el propio objeto sobre la solución que recibe como argumento.
	 * @param[in, out] solution Objeto solución sobre el que se aplicará el cambio
	 */
	virtual void apply(CNPSolution &solution);

	/**
	 * Función que asigna los valores la operación
	 * @param[in] indexObject El índice del objeto que se va a cambiar de mochila
	 * @param[in] indexKnapsack El índice de la mochila donde se insertará el objeto
	 * @param[in] deltaFitness La diferencia en fitness de aplicar dicha operación de asignación de un objeto a una mochila (siempre que la solución actual no se hubiese cambiado cuando se calculo dicha diferencia)
	 */
	void setValues(unsigned nodeNew, /*unsigned nodeOld,*/ double deltaFitness);

	
	unsigned getNewNode() { return _nodeNew;}
	//unsigned getOldNode() { return _nodeOld;}

	/**
	 * Función que devuelve la diferencia en fitness de la operación,
	 * @return Diferencia en fitness de la operación (siempre que la solución actual no se hubiese cambiado cuando se calculo dicha diferencia)
	 */
	double getDeltaFitness(){
		return _deltaFitness;
	}

	
};

#endif
