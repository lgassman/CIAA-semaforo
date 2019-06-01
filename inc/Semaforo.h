/*
 * Semaforo.h
 *
 *  Created on: May 16, 2019
 *      Author: leo
 */

#ifndef PROGRAMS_SEMAFORO_INC_SEMAFORO_H_
#define PROGRAMS_SEMAFORO_INC_SEMAFORO_H_


	struct Semaforo;
	typedef struct Semaforo Semaforo;

	typedef enum {
		semaforo_principal,
		semaforo_deshabilitado,
		semaforo_secundario
	} SemaforoMode;


	void semaforo_configLeds(Semaforo *, gpioMap_t red, gpioMap_t yellow, gpioMap_t green);
	void semaforo_setModo(Semaforo *, SemaforoMode);
	void semaforo_cycle(Semaforo *);
	Semaforo  * semaforo_create();
	void semaforo_delete (Semaforo *);


#endif /* PROGRAMS_SEMAFORO_INC_SEMAFORO_H_ */
