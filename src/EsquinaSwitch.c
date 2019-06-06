/*
 * EsquinaSwitch.c
 *
 *  Created on: Jun 1, 2019
 *      Author: leo
 */

#include "EsquinaSwitch.h"
#include "Button.h"
#include <stdlib.h>


void pulsadorPress( void * esquina);
void pulsadorRelease( void * esquina);
void botonRelease( void * esquina);

struct EsquinaSwitch  {
	Button * boton;
	Button * pulsador;
};

EsquinaSwitch * esquinaSwitch_create(Esquina * esquina, gpioMap_t boton, gpioMap_t pulsador ) {
	EsquinaSwitch * esquinaSwitch = (EsquinaSwitch *)malloc(sizeof(EsquinaSwitch));
	if(esquinaSwitch == NULL) {
		return NULL;
	}
	esquinaSwitch->boton = button_create(boton, esquina);
	esquinaSwitch->pulsador= button_create(pulsador, esquina);
	if(esquinaSwitch->boton == NULL || esquinaSwitch->pulsador == NULL) {
		esquinaSwitch_delete(esquinaSwitch);
		return NULL;
	}
	button_onRelease(esquinaSwitch->boton, botonRelease);
	button_onRelease(esquinaSwitch->pulsador, pulsadorRelease);
	button_onPress(esquinaSwitch->pulsador, pulsadorPress);

	return esquinaSwitch;
}

EsquinaSwitch * esquinaSwitch_delete(EsquinaSwitch * esquinaSwitch) {

	if(esquinaSwitch->boton) {
		button_delete(esquinaSwitch->boton);
	}
	if(esquinaSwitch->pulsador) {
		button_delete(esquinaSwitch->pulsador);
	}
	free(esquinaSwitch);
}

EsquinaSwitch * esquinaSwitch_cycle(EsquinaSwitch * esquinaSwitch) {
	button_cycle(esquinaSwitch->boton);
	button_cycle(esquinaSwitch->pulsador);
}


void pulsadorPress( void * esquina) {
	esquina_deshabilitar((Esquina *) esquina );
}
void pulsadorRelease( void * esquina) {
	esquina_habilitar((Esquina *) esquina );
}
void botonRelease( void * esquina) {
	esquina_cambiarModo((Esquina *) esquina );
}
