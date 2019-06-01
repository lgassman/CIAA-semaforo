/*
 * Semaforo.c
 *
 *  Created on: May 16, 2019
 *      Author: leo
 */

#include "sapi.h"
#include "Semaforo.h"
#include "Led.h"
#include <stdlib.h>

typedef void (*changeMode)(Semaforo *);

#define StatesSize 6
#define ModesSize 3


typedef enum {
	RED_STATE,
	REDYELLOW_STATE,
	YELLOW_STATE,
	GREEN_STATE,
	OFF_STATE,
	INIT_STATE,
} ModeState;

struct Semaforo {
	SemaforoMode mode;
	ModeState currentState;
	tick_t lastStateChange;
	gpioMap_t greenLed;
	gpioMap_t yellowLed;
	gpioMap_t redLed;
	uint32_t time[StatesSize];
	uint32_t nextState[StatesSize];
};


void principal(Semaforo *);
void deshabilitado(Semaforo *);
void secundario(Semaforo * semaforo);
uint32_t updateState(Semaforo *);
void handleLeds(Semaforo *);

//Para cada estado si la luz está prendida o apagada
	static uint32_t stateLeds[StatesSize][3]; //red, yellow, green: 1 o 0
//Para cada modo cual es la función que pone un semaforo en ese modo
	static changeMode changeModeFunctions[ModesSize];

void semaforo_init() {


	stateLeds[INIT_STATE][0] = 1; //red,
	stateLeds[INIT_STATE][1] = 0; //yellow,
	stateLeds[INIT_STATE][2] = 0; //green,

	stateLeds[GREEN_STATE][0] = 0; //red,
	stateLeds[GREEN_STATE][1] = 0; //yellow,
	stateLeds[GREEN_STATE][2] = 1; //green,

	stateLeds[RED_STATE][0] = 1;
	stateLeds[RED_STATE][1] = 0;
	stateLeds[RED_STATE][2] = 0;

	stateLeds[YELLOW_STATE][0] = 0;
	stateLeds[YELLOW_STATE][1] = 1;
	stateLeds[YELLOW_STATE][2] = 0;

	stateLeds[REDYELLOW_STATE][0] = 1;
	stateLeds[REDYELLOW_STATE][1] = 1;
	stateLeds[REDYELLOW_STATE][2] = 0;

	stateLeds[OFF_STATE][0] = 0;
	stateLeds[OFF_STATE][1] = 0;
	stateLeds[OFF_STATE][2] = 0;

	changeModeFunctions[semaforo_principal] = principal;
	changeModeFunctions[semaforo_deshabilitado] = deshabilitado;
	changeModeFunctions[semaforo_secundario] = secundario;
}



void semaforo_delete(Semaforo * semaforo) {
	free((void *) semaforo);
}

void semaforo_configLeds(Semaforo * semaforo, gpioMap_t red, gpioMap_t yellow,
		gpioMap_t green) {
	semaforo->redLed = red;
	semaforo->yellowLed = yellow;
	semaforo->greenLed = green;
}

Semaforo * semaforo_create() {
	Semaforo * semaforo = (Semaforo *) malloc(sizeof(Semaforo));
	if (semaforo == NULL) {
		return NULL;
	}
	semaforo_configLeds(semaforo, LED2, LED3, LED1);

	semaforo->currentState = INIT_STATE;
	semaforo->lastStateChange = tickRead();

	semaforo->currentState = INIT_STATE;

	semaforo->lastStateChange = tickRead();
	semaforo->mode = semaforo_principal;
	principal(semaforo);
	handleLeds(semaforo);

	return semaforo;
}
/* Sincronización de estados entre primario y secundario
 ----| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8  | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18  |  19 | 20 | 21
 P     R   R   R  R    R   R   R    R   RY   V    V   V     V    V    V     V    V   V   Y    Y  Y
 ----
 S     R   RY  V  V    V   V   Y    R   R    R    R   R     R    R    R     R    R   R   R    R   R
 ----
 */
void secundario(Semaforo * semaforo) {

	semaforo->nextState[INIT_STATE] = REDYELLOW_STATE;
	semaforo->nextState[RED_STATE] = REDYELLOW_STATE;
	semaforo->nextState[REDYELLOW_STATE] = GREEN_STATE;
	semaforo->nextState[YELLOW_STATE] = RED_STATE;
	semaforo->nextState[GREEN_STATE] = YELLOW_STATE;
	semaforo->nextState[OFF_STATE] = OFF_STATE;

	semaforo->time[INIT_STATE] = 1000;
	semaforo->time[RED_STATE] = 15000;
	semaforo->time[REDYELLOW_STATE] = 1000;
	semaforo->time[YELLOW_STATE] = 1000;
	semaforo->time[GREEN_STATE] = 4000;
	semaforo->time[OFF_STATE] = 0;
}

void principal(Semaforo * semaforo) {

	semaforo->nextState[INIT_STATE] = RED_STATE;
	semaforo->nextState[RED_STATE] = REDYELLOW_STATE;
	semaforo->nextState[REDYELLOW_STATE] = GREEN_STATE;
	semaforo->nextState[YELLOW_STATE] = RED_STATE;
	semaforo->nextState[GREEN_STATE] = YELLOW_STATE;
	semaforo->nextState[OFF_STATE] = OFF_STATE;

	semaforo->time[INIT_STATE] = 0;
	semaforo->time[RED_STATE] = 8000;
	semaforo->time[REDYELLOW_STATE] = 1000;
	semaforo->time[YELLOW_STATE] = 3000;
	semaforo->time[GREEN_STATE] = 9000;
	semaforo->time[OFF_STATE] = 0;

}

void deshabilitado(Semaforo * semaforo) {
	semaforo->nextState[INIT_STATE] = YELLOW_STATE;
	semaforo->nextState[RED_STATE] = RED_STATE;
	semaforo->nextState[REDYELLOW_STATE] = REDYELLOW_STATE;
	semaforo->nextState[YELLOW_STATE] = OFF_STATE;
	semaforo->nextState[GREEN_STATE] = GREEN_STATE;
	semaforo->nextState[OFF_STATE] = YELLOW_STATE;

	semaforo->time[INIT_STATE] = 1000;
	semaforo->time[RED_STATE] = 0;
	semaforo->time[REDYELLOW_STATE] = 0;
	semaforo->time[YELLOW_STATE] = 1000;
	semaforo->time[GREEN_STATE] = 0;
	semaforo->time[OFF_STATE] = 1000;
}

void semaforo_setModo(Semaforo * semaforo, SemaforoMode mode) {
	if (semaforo->mode != mode) {
		semaforo->mode = mode;
		semaforo->currentState = INIT_STATE;
		semaforo->lastStateChange = tickRead();
		changeModeFunctions[semaforo->mode](semaforo);
	}
}

void semaforo_cycle(Semaforo * semaforo) {
	if (updateState(semaforo)) {
		handleLeds(semaforo);
	}
}

uint32_t updateState(Semaforo * semaforo) {
	tick_t newTick = tickRead();

	if (newTick - semaforo->lastStateChange > semaforo->time[semaforo->currentState]) {
		semaforo->lastStateChange = newTick;
		semaforo->currentState = semaforo->nextState[semaforo->currentState];
		return 1;
	} else {
		return 0;
	}
}

void handleLeds(Semaforo * semaforo) {
	led_setValue(semaforo->redLed, stateLeds[semaforo->currentState][0]);
	led_setValue(semaforo->greenLed, stateLeds[semaforo->currentState][1]);
	led_setValue(semaforo->yellowLed, stateLeds[semaforo->currentState][2]);
}
