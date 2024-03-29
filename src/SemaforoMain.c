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
#include "Esquina.h"
#include "EsquinaSwitch.h"
#include "SemaforoLeds.h"
#include "SemaforoLedsRGB.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/



int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();
   semaforo_init();


   Esquina * esquina = esquina_create();
   if(!esquina ) {
	   return 1;
   }

   EsquinaSwitch * esquinaSwitch = esquinaSwitch_create(esquina, TEC1, TEC2);
   SemaforoLeds * semaforoPrincipalRender = semaforoLeds_createDefault( esquina_getPrincipal(esquina));
   SemaforoLedsRGB * semaforoSecundarioRender = semaforoLedsRGB_createDefault( esquina_getSecundario(esquina));
   if(!esquinaSwitch || !semaforoPrincipalRender || !semaforoSecundarioRender ) {
	   return 1;
   }


   // ----- Repeat for ever -------------------------
   while( true ) {
	   //entradas
	   esquinaSwitch_cycle(esquinaSwitch);
	   //modelo
	   esquina_cycle(esquina);
	   //salida
	   semaforoLeds_cycle(semaforoPrincipalRender);
	   semaforoLedsRGB_cycle(semaforoSecundarioRender);
	   sleepUntilNextInterrupt();
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
