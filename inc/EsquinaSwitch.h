/**
 * EsquinaSwitch.h
 *
 *  Created on: Jun 1, 2019
 *      Author: leo
 *
 * Es un TAD que une dos botones (gpio) con una esquina. El primer boton funciona como un switch:
 * al relesear cambia de modo (habilitado o deshabilitado) según corresponda.
 * El segundo es un pulsador que mientras se mantiene apretado la esquina se deshabilita y al soltarlo se
 * se vuelve a habilitar
 */

#ifndef PROGRAMS_SEMAFORO_INC_ESQUINASWITCH_H_
#define PROGRAMS_SEMAFORO_INC_ESQUINASWITCH_H_

#include "Esquina.h"
#include "sapi.h"

struct EsquinaSwitch;
typedef struct EsquinaSwitch EsquinaSwitch;

EsquinaSwitch * esquinaSwitch_create(Esquina * esquina, gpioMap_t boton, gpioMap_t pulsador );
EsquinaSwitch * esquinaSwitch_delete(EsquinaSwitch *);
EsquinaSwitch * esquinaSwitch_cycle(EsquinaSwitch *);



#endif /* PROGRAMS_SEMAFORO_INC_ESQUINASWITCH_H_ */
