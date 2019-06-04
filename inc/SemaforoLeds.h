/*
 * SemaforoLeds.h
 *
 *  Created on: Jun 3, 2019
 *      Author: leo
 */

#ifndef PROGRAMS_SEMAFORO_INC_SEMAFOROLEDS_H_
#define PROGRAMS_SEMAFORO_INC_SEMAFOROLEDS_H_

#include "Semaforo.h"
#include "sapi.h"

struct SemaforoLeds;
typedef struct SemaforoLeds SemaforoLeds;


SemaforoLeds * semaforoLeds_createDefault(Semaforo* model);

SemaforoLeds * semaforoLeds_create(Semaforo* model, gpioMap_t greenLed, gpioMap_t yellowLed, gpioMap_t redLed);

void semaforoLeds_delete(SemaforoLeds *);

void semaforoLeds_cycle(SemaforoLeds *);


#endif /* PROGRAMS_SEMAFORO_INC_SEMAFOROLEDS_H_ */

