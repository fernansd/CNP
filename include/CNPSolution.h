/**
 * CNPSolution.h
 *
 * Fichero que define la clase 	CNPSolution. Forma parte del código esqueleto para el problema de la búsqueda de nodos críticos, ofrecido para las prácticas de la asignatura Metaheurísticas del Grado de Ingeniería Informática de la Universidad de Córdoba
 *
 * @author Undead Corporation
 */

/*

COSAS QUE SE PUEDEN CAMBIAR(APUNTES)
-> INCLUIR _FITNESSASSIGNED QUE ESTA COMENTADO, CON EL FUNCION HASVALIDFITNESS
-> CAMBIAR DE PROTECTED A PRIVATE
-> QUITAR/PONER METODOS VIRTUALES
-> PONER EL VECTOR _SOL COMO BOOL EN VEZ DE COMO INT, NOS AHORRAMOS COMPROBACIONES
-> QUITAR INLINES Y PONERLO TODO EN CPP
-> QUITAR CONTADOR _NUMCRIT, ES PARA NO TENER QUE CONTAR LOS 1 QUE LLEVAMOS PUESTOS
-> QUITAR MAXIMO DE NODOS CRITICOS _NUMCRITMAX, ES PARA TENER UN TOPE QUE PONER
-> SI NO SE QUITA _NUMCRITMAX, HACERLE UN SETTER O NO???? REALMENTE NO SE LE VA A CAMBIAR
	EL NUMERO DE NODOS A QUITAR DE REPENTE

COSAS CAMBIADAS

*/

#ifndef CNPSOLUTION_H_
#define CNPSOLUTION_H_

#ifndef CNPINSTANCE_H_
#include "CNPInstance.h"
#else
class CNPInstance;
#endif


/**
 * Clase que representa una solución al problema
 *
 * Sobre la representación de soluciones:
 * La representación de las soluciones será un vector de booleanos: 0 a Nodos-1 con un 1 si
 * se nodo se borra y un  	* 0 se si mantiene en el grafo
 *
 */
class CNPSolution {
protected:
	/* Definir las variables miembro
	 * _sol Vector booleano que será la representación interna de la solución al problema
	 * _fitness valor double que almacena la calidad de la solución
	 * _numCrit Contador de nodos críticos
	 * _numCritMax Número máximo de nodos críticos.
	 */
	std::vector <bool> _sol;
	double _fitness;

	unsigned _numCrit;
	unsigned _numCritMax;

	// bool _fitnessAssigned; No sé si habrá que añadirla para saber qué individuos tienen
	// el fitness asignado en las del 4

public:
	/**
	 * Constructor
	 * @param[in] instance Referencia a un objeto con la información de la instancia del
	 * problema CNP
	 */
	CNPSolution(CNPInstance &instance);

	/**
	 * Destructor
	 *
	 * Añadir cuerpo si se desea usar, se cree innecesario ya que no se reserva memoria explícitamente
	virtual ~CNPSolution();*/

	/**
	 * Función que asigna un estado a un nodo del grafo
	 * @param[in] id, posicioón identificadora de un nodo dentro del vector solución
	 * @param[in] estado, 0 se mantiene, 1 se borra
	 */
	void setNode(const unsigned &id, const bool &estado);

	/**
	 * Función que devuelve el estado de un grafo
	 * @param[in] id, posición identificadora de un nodo dentro del vector solución
	 * @return estado del nodo, borrado o intacto1
	 */
	int getNode(const unsigned &id);

	/**
	 * Función que asigna el fitness de la solución
	 * @param[in] fitness Fitness de la solución
	 */
	inline void setFitness(const double &fitness){_fitness=fitness;};

	/**
	 * Función que devuelve el fitness de la solución
	 *
	 * @return fitness de la solución
	 */
	inline double getFitness() const{return _fitness;};

	/**
	 * Función que devuelve el contador de nodos críticos en la solución
	 *
	 * @return numCrit Contador de nodos críticos en la solución
	 */
	inline unsigned getNumCrit() const{return _numCrit;};

	/**
	 * Función que devuelve el máximo número de nodos críticos en la solución
	 *
	 * @return numCrit máximo número de nodos críticos en la solución
	 */
	inline unsigned getNumCritMax() const{return _numCritMax;};

	/**
	 * Función que copia la información de otra solución
	 * @param[in] solution La solución de donde copiar la información
	 *
	*/
	void copy(const CNPSolution &solution);

	/**
	 * Función que indica si el fitness de la solución es válido (deja de serlo si se
	 * cambia un objeto de mochila; y se convierte en válido cuando se le asigna)
	 *
	 * Para ahorrarnos las evaluaciones de soluciones que son copias de otras

	bool hasValidFitness(){
		return _fitnessAssigned;
	}
	*/
};

#endif /* CNPSOLUTION_H_ */
