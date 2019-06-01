/*=============================================================================
 * Copyright (c) 2019, Leo <lgassman@gmail.com>
 * All rights reserved.
 * License: gpl-3.0 (see LICENSE.txt)
 * Date: 2019/05/16
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "SemaforoMain.h"
#include "sapi.h"
#include "Semaforo.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/



int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();

   // ----- Repeat for ever -------------------------
   Semaforo * sem = semaforo_create();

   Semaforo * semSecundario = semaforo_create();
   semaforo_configLeds(semSecundario, LEDR, LEDG, LEDB);
   semaforo_setModo(semSecundario, semaforo_secundario);

   while( true ) {
	   semaforo_cycle(sem);
	   semaforo_cycle(semSecundario);
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
