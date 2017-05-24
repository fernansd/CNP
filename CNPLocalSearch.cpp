/*
 * CNPLocalSearch.cpp
 */

#include <CNPLocalSearch.h>
#include <CNPInstance.h>
#include <CNPSolution.h>
#include <CNPNeighExplorer.h>
#include <CNPNodeAssignmentOperation.h>

#include <iostream>
using namespace std;

CNPLocalSearch::CNPLocalSearch() {
}

CNPLocalSearch::~CNPLocalSearch() {
}

void CNPLocalSearch::optimise(CNPInstance& instance, CNPNeighExplorer& explorer, CNPSolution& solution) {

	_results.clear();
	_results.push_back(solution.getFitness());
	CNPNodeAssignmentOperation operation;

	bool ok;
	ok=explorer.findOperation(instance,solution,operation);

	while(ok){
		operation.apply(solution);
		setResults(solution.getFitness());
	ok=explorer.findOperation(instance,solution,operation);

	}

}
