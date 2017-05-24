/**
 * CNPLocalSearch.h
 */

#ifndef INCLUDE_CNPLOCALSEARCH_H_
#define INCLUDE_CNPLOCALSEARCH_H_

#include <CNPInstance.h>
#include <CNPSolution.h>
#include <CNPNeighExplorer.h>
#include <vector>

/**
 * Clase que implementa la optimización local repetitiva de una solución dada.
 */
class CNPLocalSearch{

	/**
	 * vector de doubles donde almacena la calidad de la última solución aceptada
	 */
	std::vector<double> _results;

public:
	/**
	 * Constructor
	 */
	CNPLocalSearch();

	/**
	 * Destructor
	 */
	~CNPLocalSearch();

	/**
	 * Función que optimiza una solución aplicado repetidamente la exploración de su vecindario hasta alcanzar un óptimo local.
	 * @param[in] instance Instancia del problema
	 * @param[in] explorer Operador de exploración del vecindario. La idea es que reciba un operador que bien explore el vecindario devolviendo la primera solución que mejora a la actual, o devolviendo el mejor cambio posible sobre la solución actual
	 * @param[in,out] solution Solución inicial que se optimiza localmente. El resultado final se devuelve en ella.
	 */
	void optimise(CNPInstance &instance, CNPNeighExplorer &explorer, CNPSolution &solution);

	/**
	 * Función que devuelve el vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 *
	 * @return vector con los resultados de las soluciones aceptadas, en cada paso, por la búsqueda local
	 */
	std::vector<double>& getResults() {
		return _results;
	}

	void setResults(double results) { _results.push_back(results); }
};



#endif
