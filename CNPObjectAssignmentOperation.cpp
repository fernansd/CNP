/*
 * MQKPObjectAssignmentOperation.cpp
 *
 * Fichero que define las funciones de la clase MQKPObjectAssignmentOperation. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <CNPObjectAssignmentOperation.h>

CNPObjectAssignmentOperation::CNPObjectAssignmentOperation(){
	//_nodeOld = -1;
	_nodeNew = -1;
	_deltaFitness = 0;
}

CNPObjectAssignmentOperation::~CNPObjectAssignmentOperation() {
}

void CNPObjectAssignmentOperation::apply(CNPSolution& solution) {

	solution.setNode(_nodeNew, true);
	//solution.setFitness(_deltaFitness);
}

void CNPObjectAssignmentOperation::setValues(unsigned nodeNew, //unsigned nodeOld,
		double deltaFitness) {
	/*
	 * Guarda los valores pasados como argumentos en las variables miembro
	 */
	_nodeNew = nodeNew;
	//_nodeOld = nodeOld;
	_deltaFitness = deltaFitness;
}
