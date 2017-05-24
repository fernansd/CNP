/*
 * CNPEvaluator.cpp
 *
 *  Created on: 30/03/2017
 *      Author: i42sadef
 */

/*

COSAS QUE SE PUEDEN CAMBIAR(APUNTES)
-> AÑADIR UN CONSTRUCTOR DE COPIA A CNPINSTANCE, SE USA EN COMPUTEFITNESS
-> QUE HACER CON EL VECTOR_CENTRALITY???? AGREGAR A INSTANCE???? A SOLUTION????
YO APUESTO POR AGREGARLO A SOLUTION MAS QUE A INSTANCE HAY QUE HABLARLO
-> Cambiar nodosConectados EN INSTANCE POR getLado

COSAS CAMBIADAS
-> HE QUITADO LA NORMALIZACIÓN DEL CENTRALITY

*/

#include <CNPEvaluator.h>
#include <CNPInstance.h>
#include <iostream>
#include <queue>
#include <stack>

// Es necesario inicializarla aquí ya que es una variable estática
unsigned CNPEvaluator::_numEvaluations = 0;

void CNPEvaluator::getNeighbours(CNPInstance& instance,
		int nodo, std::vector<int>& vecinos)
{
	CNPInstance::Grafo& grafo = instance.getGrafo();
	vecinos.clear();
	for (unsigned i = 0; i < grafo.size(); i++) {
		// Comprueba si nodo está conectado con i
		if (instance.getLado(nodo, i)) {
			vecinos.push_back(i);
		}
	}
}

std::vector<double> CNPEvaluator::computeBetweennessCentrality(
		CNPInstance &instance)
{
	CNPInstance::Grafo& grafo = instance.getGrafo();
	std::vector<double> Cb(grafo.size(), 0.0); // Betweenness centrality

	// Se recorren todos los nodos del grafo, siendo s el nodo actual
	for (int s = 0; s < (int)grafo.size(); s++) {

		std::stack<int> S; // Pila vacía
		std::vector<std::vector<int>> P(grafo.size(), std::vector<int>());
		std::vector<double> sigma(grafo.size(), 0.0);
		sigma[s] = 1;
		std::vector<int> d(grafo.size(), -1);
		d[s] = 0;
		std::queue<int> Q; // Cola vacía
		Q.push(s);

		while (not Q.empty()) {
			int v = Q.front();
			Q.pop();
			S.push(v);
			std::vector<int> neighbours;
			getNeighbours(instance, v, neighbours);

			for (int i = 0; i < (int)neighbours.size(); i++) {
				int w = neighbours[i];

				// Es la primera vez que se encuentra a w?
				if (d[w] < 0) {
					Q.push(w);
					d[w] = d[v] + 1;
				}
				// Camino más corto a w a través de v
				if (d[w] == d[v]+1) {
					sigma[w] = sigma[w] + sigma[v];
					P[w].push_back(v);
				}
			}
		}

		std::vector<double> delta(grafo.size(), 0.0);
		// S devuelve los vértices en orden de distancia no creciente desde s
		while (not S.empty()) {
			int w = S.top();
			S.pop();
			for (int i = 0; i < (int)P[w].size(); i++) {
				int v = P[w][i];
				delta[v] = delta[v] + (sigma[v]/sigma[w]) * (1+delta[w]);
				if (w != s) {
					Cb[w] += delta[w];
				}
			}
		}
	}
	/*
	// Normalización de los valores de Betweenness centrality
	double sum = 0;
	for (int i = 0; i < Cb.size(); i++) {
		sum += Cb[i];
	}
	for (int i = 0; i < Cb.size(); i++) {
		Cb[i] /= sum;
	}
	*/

	return Cb;
}

double CNPEvaluator::computeFitness(CNPInstance& instance, CNPSolution& solution)
{
	unsigned tam=instance.getNumNodes();
	CNPInstance aux(tam, instance.getNumCritMax());
	std::vector <double>v_centrality;
	double sum = 0;// HECHO definir un valor por defecto razonable, 0 es temporal

	//Recorremos la parte superior derecha de la matriz
	for(unsigned i=0;i<tam-1;i++){
		aux.setLado(i,i,false);										//Consideramos que ninguno se enlaza consigo
		for(unsigned j=i+1;j<tam;j++){
			if((solution.getNode(j)==1)||(solution.getNode(i)==1)){ //Si el nodo es borrado, todas conexiones a 0
				aux.setLado(i,j,false);
				aux.setLado(j,i,false);																		//Igualamos su simetrico
			}else{
				aux.setLado(i,j,instance.getLado(i,j));
				aux.setLado(j,i,instance.getLado(i,j)); 	//Igualamos su simetrico
			}

		}
	}
	aux.setLado(tam-1,tam-1,false);																	//Ponemos a 0 la conexion del último nodo consigo mismo

	v_centrality=computeBetweennessCentrality(aux);
	solution.setVectorFitness(v_centrality);

	for(unsigned i=0;i<tam;i++){
			sum+=v_centrality[i];
	}

	double fitness = instance.getSuma() - sum;
	solution.setFitness(fitness);

	_numEvaluations++;

	return fitness;
}
