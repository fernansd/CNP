/*
 * CNPInstance.cpp
 *
 *  Created on: 30/03/2017
 *      Author: i42sadef
 */

#include "CNPInstance.h"

void CNPInstance::setLado(int n1, int n2, bool estado)
{
	if (estado == true) {
		// Conecta los nodos
		_lados[n1][n2] = _lados[n2][n1] = 1;
	} else {
		// Desconecta los nodos
		_lados[n1][n2] = _lados[n2][n1] = 0;
	}
}
