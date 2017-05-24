/*
 * CNPNodeAssignmentOperation.cpp
 *
 * Fichero que define las funciones de la clase CNPNodeAssignmentOperation. Forma parte del código esqueleto para el problema de las múltiples mochilas cuadráticas, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Carlos García cgarcia@uco.es
 */

#include <CNPNodeAssignmentOperation.h>

CNPNodeAssignmentOperation::CNPNodeAssignmentOperation(){
	_node2 = 0;
	_node1 = 0;
	_deltaFitness = 0;
}

CNPNodeAssignmentOperation::~CNPNodeAssignmentOperation() {
}

void CNPNodeAssignmentOperation::apply(CNPSolution& solution) {
	/*
	 * 1. Asigna el objeto de índice _indexObj a la mochila _indexKnapsack en solution
	 * 2. Actualiza el fitness de solution sumándole _deltaFitness
	 */

	bool aux=solution.getNode(_node1);
	solution.setNode(_node1,solution.getNode(_node2));
	solution.setNode(_node2,aux);

	double actualFitness = solution.getFitness();
	double newFitness = actualFitness + _deltaFitness;
	solution.setFitness(newFitness);
}

void CNPNodeAssignmentOperation::setValues(int node1,
		int node2, double deltaFitness) {
	/*
	 * Guarda los valores pasados como argumentos en las variables miembro
	 */
	_node2 = node2;
	_node1 = node1;
	_deltaFitness = deltaFitness;
}

