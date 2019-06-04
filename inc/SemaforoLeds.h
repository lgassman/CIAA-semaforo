/*
 * SemaforoLeds.h
 *
 *  Created on: Jun 3, 2019
 *      Author: leo
 *
 *  Es un TDA que renderiza un Semaforo por 3 leds, usa por default
 *  los leds 1 al 3 que son los leds rojo amarillo y verde de la EDU-CIAA.
 *  Se puede configurar otros gpio.
 *
 */

#ifndef PROGRAMS_SEMAFORO_INC_SEMAFOROLEDS_H_
#define PROGRAMS_SEMAFORO_INC_SEMAFOROLEDS_H_

#include "Semaforo.h"
#include "sapi.h"

struct SemaforoLeds;
typedef struct SemaforoLeds SemaforoLeds;


SemaforoLeds * semaforoLeds_createDefault(Semaforo* model);

SemaforoLeds * semaforoLeds_create(Semaforo* model, gpioMap_t redLed, gpioMap_t yellowLed, gpioMap_t greenLed);

void semaforoLeds_delete(SemaforoLeds *);

void semaforoLeds_cycle(SemaforoLeds *);


#endif /* PROGRAMS_SEMAFORO_INC_SEMAFOROLEDS_H_ */

