/*
 * Esquina.h
 *
 *  Created on: Jun 1, 2019
 *      Author: leo
 */

#ifndef PROGRAMS_SEMAFORO_INC_ESQUINA_H_
#define PROGRAMS_SEMAFORO_INC_ESQUINA_H_

struct Esquina;
typedef struct Esquina Esquina;

Esquina * esquina_create();
void esquina_delete(Esquina * esquina);
void esquina_habilitar(Esquina * esquina);
void esquina_deshabilitar(Esquina * esquina);
void esquina_cambiarModo(Esquina * esquina);
void esquina_cycle(Esquina * esquina);

#endif /* PROGRAMS_SEMAFORO_INC_ESQUINA_H_ */
