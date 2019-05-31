/*
 * Semaforo.c
 *
 *  Created on: May 16, 2019
 *      Author: leo
 */

#include "sapi.h"
#include "Semaforo.h"
#include "Led.h"

#define normalStatesSize 4

typedef enum {
	RED_STATE,
	REDYELLOW_STATE,
	YELLOW_STATE,
	GREEN_STATE,
} NormalModeState;


static SemaforoMode mode;
static NormalModeState currentState = RED_STATE;
static tick_t lastStateChange;

static gpioMap_t greenLed = LED1;
static gpioMap_t yellowLed = LED3;
static gpioMap_t redLed = LED2;



static uint32_t normalTimes[normalStatesSize];
static uint32_t normalNextState[normalStatesSize];
static uint32_t normalStateLeds[normalStatesSize][3]; //red, yellow, green,


void normal();
void disabled();
int updateNormalState();
void handleNormalLeds();


void semamoforo_init() {
	lastStateChange = tickRead();

	normalTimes[RED_STATE] = 6000;
	normalTimes[REDYELLOW_STATE] = 1000;
	normalTimes[YELLOW_STATE] = 2000;
	normalTimes[GREEN_STATE] = 4000;

	normalNextState[RED_STATE] = REDYELLOW_STATE;
	normalNextState[REDYELLOW_STATE] = GREEN_STATE;
	normalNextState[YELLOW_STATE] = RED_STATE;
	normalNextState[GREEN_STATE] = YELLOW_STATE;

	normalStateLeds[GREEN_STATE][0] = 0; //red,
	normalStateLeds[GREEN_STATE][1] = 0; //yellow,
	normalStateLeds[GREEN_STATE][2] = 1; //green,

	normalStateLeds[RED_STATE][0] = 1;
	normalStateLeds[RED_STATE][1] = 0;
	normalStateLeds[RED_STATE][2] = 0;

	normalStateLeds[YELLOW_STATE][0] = 0;
	normalStateLeds[YELLOW_STATE][1] = 1;
	normalStateLeds[YELLOW_STATE][2] = 0;

	normalStateLeds[REDYELLOW_STATE][0] = 1;
	normalStateLeds[REDYELLOW_STATE][1] = 1;
	normalStateLeds[REDYELLOW_STATE][2] = 0;

	currentState = RED_STATE;
	mode = Normal;
	handleNormalLeds();
	lastStateChange = tickRead();
}


void semamoforo_setMode(SemaforoMode _mode) {
	mode = _mode;
}



void semamoforo_cycle() {
	switch (mode) {
	case Normal: {
		normal();
		break;
	}
	case Disabled: {
		disabled();
		break;
	}
	}
}

int updateNormalState() {
	tick_t newTick = tickRead();

	if(newTick - lastStateChange > normalTimes[currentState]) {
		lastStateChange  = newTick;
		currentState = normalNextState[currentState];
		return 1;
	}
	else {
		return 0;
	}
}

void normal() {

	if(updateNormalState()) {
		handleNormalLeds();
	}
}

void handleNormalLeds() {
	led_setValue(redLed , normalStateLeds[currentState][0]);
	led_setValue(greenLed , normalStateLeds[currentState][1]);
	led_setValue(yellowLed , normalStateLeds[currentState][2]);
}

void disabled() {
	led_setValue(redLed , false );
	led_setValue(greenLed , false );
	led_setValue(yellowLed , false );
}

