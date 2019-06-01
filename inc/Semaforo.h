/*
 * Semaforo.h
 *
 *  Created on: May 16, 2019
 *      Author: leo
 */

#ifndef PROGRAMS_SEMAFORO_INC_SEMAFORO_H_
#define PROGRAMS_SEMAFORO_INC_SEMAFORO_H_

	#include "sapi.h"

	struct Semaforo;
	typedef struct Semaforo Semaforo;

	typedef enum {
		semaforo_principal,
		semaforo_deshabilitado,
		semaforo_secundario
	} SemaforoMode;

	/**
	 * Inicializa la librería de semáforo
	 * */
	void semaforo_init();
	/**
	 * Crea un semaforo
	 */
	Semaforo  * semaforo_create();
	/**
	 * Elimina un semaforo
	 */
	void semaforo_delete (Semaforo *);

	/**
	 * Configura los gpio para los leds, por default usa Led 1, 2 y 3
	 */
	void semaforo_configLeds(Semaforo *, gpioMap_t red, gpioMap_t yellow, gpioMap_t green);

	/**
	 * Cambia el modo del semáforo. Por defaul es primario
	 */
	void semaforo_setModo(Semaforo *, SemaforoMode);

	/**
	 * Función a ser llamada desde el superloop
	 */
	void semaforo_cycle(Semaforo *);


#endif /* PROGRAMS_SEMAFORO_INC_SEMAFORO_H_ */
