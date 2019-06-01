/*
 * Button.h
 *
 *  Created on: Jun 1, 2019
 *      Author: leo
 */

#ifndef PROGRAMS_SEMAFORO_INC_BUTTON_H_
#define PROGRAMS_SEMAFORO_INC_BUTTON_H_

#include "sapi.h"

struct Button;
typedef struct Button Button;
typedef void (*EventHandler)(void *);


Button * button_create(gpioMap_t gpio, void * model);
void button_delete(Button * button);

void button_onPress(Button * button, EventHandler handler);
void button_onRelease(Button * button, EventHandler handler);
void button_cycle(Button * button);


#endif /* PROGRAMS_SEMAFORO_INC_BUTTON_H_ */
