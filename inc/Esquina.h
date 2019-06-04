/**
 * Esquina.h
 *
 *  Created on: Jun 1, 2019
 *      Author: leo
 *
 *
 * Es un TAD que modela una esqina que tiene dos semaforos, uno principal y otro
 * secundario, funcionando de forma sincronizada. Al deshabilitarlo ambos
 * semaforos pasan a modo deshabilitado. Los semaforos son creados y liberados
 * por este TAD
 *
 */


#ifndef PROGRAMS_SEMAFORO_INC_ESQUINA_H_
#define PROGRAMS_SEMAFORO_INC_ESQUINA_H_

struct Esquina;
typedef struct Esquina Esquina;

#include "Semaforo.h"

Esquina * esquina_create();
void esquina_delete(Esquina * esquina);
void esquina_habilitar(Esquina * esquina);
void esquina_deshabilitar(Esquina * esquina);
void esquina_cambiarModo(Esquina * esquina);
void esquina_cycle(Esquina * esquina);
Semaforo * esquina_getPrincipal(Esquina * esquina);
Semaforo * esquina_getSecundario(Esquina * esquina);


#endif /* PROGRAMS_SEMAFORO_INC_ESQUINA_H_ */
