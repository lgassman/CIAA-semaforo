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
   EsquinaSwitch * esquinaSwitch = esquinaSwitch_create(esquina, TEC1, TEC2);

   if(!esquina) {
	   return 1;
   }

   // ----- Repeat for ever -------------------------
   while( true ) {
	   esquina_cycle(esquina);
	   esquinaSwitch_cycle(esquinaSwitch);
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
