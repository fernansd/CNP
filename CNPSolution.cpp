/**
 * CNPSolution.cpp
 *
 * Fichero que define la clase 	CNPSolution. Forma parte del código esqueleto para el
 * problema de la búsqueda de nodos críticos, ofrecido para las prácticas de la asignatura
 * Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Undead Corporation
 */

/*

COSAS QUE SE PUEDEN CAMBIAR(APUNTES)
-> INCLUIR _FITNESSASSIGNED QUE ESTA COMENTADO, CON EL FUNCION HASVALIDFITNESS
-> PONER EL VECTOR _SOL COMO BOOL EN VEZ DE COMO INT, NOS AHORRAMOS COMPROBACIONES

COSAS CAMBIADAS

*/

#include <CNPSolution.h>

#include <vector>
#include <iostream>

/**
 * Codificación de funciones de la clase que representa una solución al problema, CNPSolution
 *
 * Sobre la representación de soluciones:
 * La representación de las soluciones será un vector de número enteros: de 1 a M para objetos
 * que están en alguna de las M mochilas y 0 para objetos que no están en ninguna mochilas
 */

CNPSolution::CNPSolution(CNPInstance &instance){

	unsigned numNodes=instance.getNumNodes();
	_fitness = 0;
	_numCrit=0;
	_numCritMax=instance.getNumCritMax();
	_sol.resize(numNodes);
	/*if (!_sol) {
		cerr << "No se ha reservado memoria correctamente para _sol" << endl;
		exit(-1);
	}*/
	_vectorCentrality.resize(numNodes);
	/*if (!_vectorCentrality) {
		cerr << "No se ha reservado memoria correctamente para _vectorCentrality" << endl;
		exit(-1);
	}*/

	for (unsigned i = 0; i < numNodes; i++) {
		_sol[i] = false;
		_vectorCentrality[i]=0;
	}

_fitnessAssigned=false;

}

CNPSolution::CNPSolution(CNPSolution &solution){
	unsigned numNodes=(unsigned)solution._sol.size();

	_fitness = solution.getFitness();
	_numCrit=solution.getNumCrit();
	_numCritMax=solution.getNumCritMax();
	_sol.resize(numNodes);
	/*if (!_sol) {
		cerr << "No se ha reservado memoria correctamente para _sol" << endl;
		exit(-1);
	}*/
	_vectorCentrality.resize(numNodes);
	/*if (!_vectorCentrality) {
		cerr << "No se ha reservado memoria correctamente para _vectorCentrality" << endl;
		exit(-1);
	}*/

	for (unsigned i = 0; i < numNodes; i++) {
		_sol[i] = solution.getNode(i);
		_vectorCentrality[i]=solution.getNodeFitness(i);
	}
	_fitnessAssigned=solution.hasValidFitness();
}


/**
 * Función que asigna un estado a un nodo del grafo
 * @param[in] id, posición identificadora de un nodo dentro del vector solución
 * @param[in] estado, 0 se mantiene, 1 se borra
 */
void CNPSolution::setNode(const unsigned &id, const bool &estado){
	if(id>=_sol.size()){
		std::cerr << "No existe nodo con tal id" << std::endl;
		exit(-1);
	}

	if(getNode(id) != estado){
		if(estado==0){
			_numCrit--;
		}else{
			_numCrit++;
		}
		_sol[id]=estado;
	}
}

/**
 * Función que devuelve el estado de un grafo
 * @param[in] id, posicioón identificadora de un nodo dentro del vector solución
 * @return estado del nodo, borrado o intacto
 */
bool CNPSolution::getNode(const unsigned &id){
	if(id>=_sol.size()){
		std::cerr << "No existe nodo con tal id" << std::endl;
		exit(-1);
	}

	return _sol[id];
}

void CNPSolution::setVectorFitness(std::vector<double> vecFit){
	unsigned numNodes=(unsigned)_sol.size();
	if(vecFit.size()!=(size_t)numNodes){
		std::cerr << "Ese vector no es del problema." << std::endl;
		exit(-1);
	}
	for(unsigned i=0;i<numNodes;i++){
		_vectorCentrality[i]=vecFit[i];
	}
}

double CNPSolution::getNodeFitness(unsigned &id){
	if(id>=_sol.size()){
		std::cerr << "No existe nodo con tal id" << std::endl;
		exit(-1);
	}
	return _vectorCentrality[id];

}

void CNPSolution::resetSolution()
{
	for (size_t i = 0; i < _sol.size(); i++) {
		_sol[i] = false;
	}
	_numCrit = 0;
	_fitness = 0;
}

/**
 * Función que copia la información de otra solución
 * @param[in] solution La solución de donde copiar la información
 *
*/
void CNPSolution::copy(CNPSolution &solution){

/*
 * 1. Copiar las asignaciones de objetos a mochilas
 * 2. copiar el fitness
 */
	unsigned numNodes=(unsigned)_sol.size();
	_sol.resize(numNodes);
	_vectorCentrality.resize(numNodes);

	for (unsigned i = 0; i < numNodes; i++){
		_sol[i] = solution.getNode(i);
		_vectorCentrality[i]=solution.getNodeFitness(i);
	}

	setFitness(solution.getFitness());
	setNumCrit(solution.getNumCrit());
	_numCritMax = solution.getNumCritMax();

	setValidFitness(solution.hasValidFitness());
}

void CNPSolution::splitNodes(std::vector<unsigned>& setTrue, std::vector<unsigned>& setFalse)
{
	setTrue.resize(_numCrit);
	setFalse.resize(_sol.size()-_numCrit);
	unsigned truePos = 0;
	unsigned falsePos = 0;
	for (unsigned i = 0; i < (unsigned)_sol.size(); i++) {
		if (_sol[i] == true) {
			setTrue[truePos] = i;
			truePos++;
		} else {
			setFalse[falsePos] = i;
			falsePos++;
		}
	}
}


