	/*=============================================================================
 * Copyright (c) 2019, Leo <lgassman@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2019/05/16
 * Version: 1.0
 *
 * Es un superloop que maneja una esquina. Usa TDA para cada componente,
 * cada componente tiene un método xxx_cycle(tda) que debe ser llamado en el
 * superloop. Se pueden identificar 3 tipos de componentes por su responsabilidad:
 * entrada (Button, EsquinaSwitch), Modelo (Esquina, Semaforo) y Salidas
 * (SemaforoLeds y SemaforoLedsRGB
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __SEMAFORO_H__
#define __SEMAFORO_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stddef.h>

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

/*=====[Prototypes (declarations) of public functions]=======================*/

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __SEMAFORO_H__ */
