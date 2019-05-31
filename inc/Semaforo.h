/*
 * Semaforo.h
 *
 *  Created on: May 16, 2019
 *      Author: leo
 */

#ifndef PROGRAMS_SEMAFORO_INC_SEMAFORO_H_
#define PROGRAMS_SEMAFORO_INC_SEMAFORO_H_

	typedef enum {
		Normal = 0,
		Disabled = 1
	} SemaforoMode;

	void semamoforo_setMode(SemaforoMode mode);
	void semamoforo_cycle();
	void semamoforo_init();


#endif /* PROGRAMS_SEMAFORO_INC_SEMAFORO_H_ */
