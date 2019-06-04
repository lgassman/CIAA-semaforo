/*
 * SemaforoLeds.c
 *
 *  Created on: Jun 3, 2019
 *      Author: leo
 */

#include "SemaforoLeds.h"
#include "Led.h"
#include <stdlib.h>


struct SemaforoLeds {
	Semaforo* model;
	gpioMap_t greenLed;
	gpioMap_t yellowLed;
	gpioMap_t redLed;
};


SemaforoLeds * semaforoLeds_createDefault(Semaforo* model) {
	return semaforoLeds_create(model, LED2, LED1 , LED3);
}

SemaforoLeds * semaforoLeds_create(Semaforo* model, gpioMap_t redLed, gpioMap_t yellowLed, gpioMap_t greenLed) {
	SemaforoLeds * semaforoLeds = (SemaforoLeds *)malloc(sizeof (SemaforoLeds));
	if(semaforoLeds == NULL ) {
		return NULL;
	}
	semaforoLeds->model = model;
	semaforoLeds->redLed= redLed;
	semaforoLeds->yellowLed = yellowLed;
	semaforoLeds->greenLed = greenLed;
	return semaforoLeds;
}

void semaforoLeds_delete(SemaforoLeds * semaforoLeds) {
	free((void *)semaforoLeds);
}

void semaforoLeds_cycle(SemaforoLeds * semaforoLeds) {
	bool_t * luces = semaforo_getLuces(semaforoLeds->model);
	led_setValue(semaforoLeds->redLed, luces[0]);
	led_setValue(semaforoLeds->yellowLed, luces[1]);
	led_setValue(semaforoLeds->greenLed, luces[2]);
}
