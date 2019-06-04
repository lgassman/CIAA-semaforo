/*
 * SemaforoLedsRGB.h
 *
 *  Created on: Jun 4, 2019
 *      Author: leo
 *
 *  Es un TDA que renderiza un Semaforo por un set de 3 leds RGB
 *  los leds R, G y B de la EDU-CIAA.
 *  Se puede configurar otros gpio.
 *
 *  El estado REDYELLOW se renderiza como amarillo.
 */

#ifndef PROGRAMS_SEMAFORO_INC_SEMAFOROLEDSRGB_H_
#define PROGRAMS_SEMAFORO_INC_SEMAFOROLEDSRGB_H_

#include "Semaforo.h"
#include "sapi.h"

struct SemaforoLedsRGB;
typedef struct SemaforoLedsRGB SemaforoLedsRGB;

SemaforoLedsRGB * semaforoLedsRGB_createDefault(Semaforo* model);

SemaforoLedsRGB * semaforoLedsRGB_create(Semaforo* model, gpioMap_t rLed, gpioMap_t gLed, gpioMap_t bLed);

void semaforoLedsRGB_delete(SemaforoLedsRGB *);

void semaforoLedsRGB_cycle(SemaforoLedsRGB *);


#endif /* PROGRAMS_SEMAFORO_INC_SEMAFOROLEDSRGB_H_ */
