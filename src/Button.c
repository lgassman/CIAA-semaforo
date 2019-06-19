/*
 * Button.c
 *
 *  Created on: Jun 1, 2019
 *      Author: leo
 */

#include "Button.h"
#include <stdlib.h>


typedef enum {
	UP, FALLING, DOWN, RISING,
} ButtonState;

struct Button {
	void * model;
	gpioMap_t gpio;
	EventHandler onPress;
	EventHandler onRelease;
	ButtonState state;
	delay_t delay;
};

void nullHandler(void *);
void initDelayCounter(Button * button);
void changeState(Button * button, ButtonState state);


Button * button_create(gpioMap_t gpio, void * model) {

	Button * button = malloc(sizeof(Button));
	if(button == NULL) {
		return NULL;
	}
	button->model = model;
	button->gpio = gpio;
	button->onPress = nullHandler;
	button->onRelease = nullHandler;
	button->state = UP;

	return button;
}


void nullHandler(void * model){
}

void button_delete(Button * button) {
	free (button);
}

void button_onPress(Button * button, EventHandler eventHandler) {
	button->onPress = eventHandler;
}

void button_onRelease(Button * button, EventHandler eventHandler) {
	button->onRelease = eventHandler;
}

void changeState(Button * button, ButtonState state) {
	button->state = state;
}
void initDelayCounter(Button * button) {
	delayInit(&button->delay, 40);
}

void button_cycle(Button * button) {
	bool_t readed = gpioRead( button->gpio );

	bool_t pressed = !readed;
	switch(button->state) {

		case UP : {
			if(pressed) {
				changeState(button, FALLING);
				initDelayCounter(button);
			}
			break;
		};
		case DOWN : {
			if(!pressed) {
				changeState(button, RISING);
				initDelayCounter(button);
			}
			break;
		};
		case FALLING : {
			if(delayRead(&button->delay)) {
				if(pressed) {
					changeState(button, DOWN);
					button->onPress(button->model);
				}
				else {
					changeState(button, UP);
				}
			}
			break;
		}
		case RISING : {
			if(delayRead(&button->delay)) {
				if(!pressed) {
					changeState(button, UP);
					button->onRelease(button->model);
				}
				else {
					changeState(button, DOWN);
				}
			}
			break;
		}
		default : {
			//error
			changeState(button, pressed ? DOWN : UP);
		}

	}
}

