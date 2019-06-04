/*
 * SemaforoLedsRGB.c
 *
 *  Created on: Jun 4, 2019
 *      Author: leo
 */
#include "SemaforoLedsRGB.h"
#include "Led.h"
#include <stdlib.h>

struct SemaforoLedsRGB {
	Semaforo* model;
	gpioMap_t rLed;
	gpioMap_t gLed;
	gpioMap_t bLed;
};

void prenderRojo(SemaforoLedsRGB *);
void prenderAmarillo(SemaforoLedsRGB *);
void prenderVerde(SemaforoLedsRGB *);
void apagar(SemaforoLedsRGB *);

SemaforoLedsRGB * semaforoLedsRGB_createDefault(Semaforo* model) {
	return semaforoLedsRGB_create(model, LEDR, LEDG , LEDB);
}

SemaforoLedsRGB * semaforoLedsRGB_create(Semaforo* model, gpioMap_t rLed, gpioMap_t gLed, gpioMap_t bLed) {
	SemaforoLedsRGB * semaforoLedsRGB = (SemaforoLedsRGB *)malloc(sizeof (SemaforoLedsRGB));
	if(semaforoLedsRGB == NULL ) {
		return NULL;
	}
	semaforoLedsRGB->model = model;
	semaforoLedsRGB->rLed= rLed;
	semaforoLedsRGB->gLed = gLed;
	semaforoLedsRGB->bLed = bLed;
	return semaforoLedsRGB;
}

void semaforoLedsRGB_delete(SemaforoLedsRGB * semaforoLedsRGB) {
	free((void *)semaforoLedsRGB);
}

void semaforoLedsRGB_cycle(SemaforoLedsRGB * semaforoLedsRGB) {
	bool_t * luces = semaforo_getLuces(semaforoLedsRGB->model);

	if(luces[1]) {
		prenderAmarillo(semaforoLedsRGB);
	}
	else if(luces[0]) {
		prenderRojo(semaforoLedsRGB);
	}
	else if(luces[2]) {
		prenderVerde(semaforoLedsRGB);
	}
	else {
		apagar(semaforoLedsRGB);
	}
}

void prenderRojo(SemaforoLedsRGB * semaforoLedsRGB) {
	led_setValue(semaforoLedsRGB->rLed, true);
	led_setValue(semaforoLedsRGB->gLed, false);
	led_setValue(semaforoLedsRGB->bLed, false);
}

void prenderVerde(SemaforoLedsRGB * semaforoLedsRGB) {
	led_setValue(semaforoLedsRGB->rLed, false);
	led_setValue(semaforoLedsRGB->gLed, true);
	led_setValue(semaforoLedsRGB->bLed, false);
}

void prenderAmarillo(SemaforoLedsRGB * semaforoLedsRGB) {
	led_setValue(semaforoLedsRGB->rLed, true);
	led_setValue(semaforoLedsRGB->gLed, true);
	led_setValue(semaforoLedsRGB->bLed, false);
}

void apagar(SemaforoLedsRGB * semaforoLedsRGB) {
	led_setValue(semaforoLedsRGB->rLed, false);
	led_setValue(semaforoLedsRGB->gLed, false);
	led_setValue(semaforoLedsRGB->bLed, false);
}
