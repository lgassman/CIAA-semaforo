/*
 * Esquina.c
 *
 *  Created on: Jun 1, 2019
 *      Author: leo
 */

#include "Esquina.h"
#include "Semaforo.h"
#include "sapi.h"
#include <stdlib.h>

struct Esquina {
	Semaforo * principal;
	Semaforo * secundario;
	bool_t habilitado;
};


Esquina * esquina_create() {
	Esquina * esquina = (Esquina *) malloc(sizeof(Esquina));
	if (esquina == NULL) {
		return NULL;
	}
	esquina->principal = semaforo_create();
	if(esquina->principal == NULL) {
		esquina_delete(esquina);
		return NULL;
	}

	esquina->secundario = semaforo_create();
	if(esquina->secundario == NULL) {
		esquina_delete(esquina);
		return NULL;
	}

	esquina_habilitar(esquina);
	return esquina;
}

void esquina_delete(Esquina * esquina) {
	if(esquina->principal) {
		semaforo_delete(esquina->principal);
	}
	if(esquina->secundario) {
		semaforo_delete(esquina->secundario);
	}
	free(esquina);
}

void esquina_cambiarModo(Esquina * esquina) {
	if(esquina->habilitado) {
		esquina_deshabilitar(esquina);
	}
	else {
		esquina_habilitar(esquina);
	}
}

void esquina_habilitar(Esquina * esquina) {
	esquina->habilitado = true;
	semaforo_setModo(esquina->principal, semaforo_principal);
	semaforo_setModo(esquina->secundario, semaforo_secundario);
}

void esquina_deshabilitar(Esquina * esquina) {
	esquina->habilitado = false;
	semaforo_setModo(esquina->principal, semaforo_deshabilitado);
	semaforo_setModo(esquina->secundario, semaforo_deshabilitado);
}

void esquina_cycle(Esquina * esquina) {
	semaforo_cycle(esquina->principal);
	semaforo_cycle(esquina->secundario);
}

Semaforo * esquina_getPrincipal(Esquina * esquina) {
	return esquina->principal;
}
Semaforo * esquina_getSecundario(Esquina * esquina) {
	return esquina->secundario;
}








