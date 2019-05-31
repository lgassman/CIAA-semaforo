/*
 * Led.c
 *
 *  Created on: May 16, 2019
 *      Author: leo
 */

#include "Led.h"


void led_setValue(gpioMap_t led, bool_t value)
{
	gpioWrite(led, value);
}


