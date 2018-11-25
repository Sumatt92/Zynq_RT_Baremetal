/*
 * einit.c
 *
 *  Created on: Nov 12, 2018
 *      Author: BJH
 */

#include <stdio.h>
#include "platform.h"
#include <xgpio.h>
#include "xparameters.h"
#include "sleep.h"
#include "einit.h"

int einit(void){
	init_platform();
	//einit_io();
	//einit_timers();
	//einit_can();
	//einit_xadc();
	//einit_spi();
	//einit_qspi();
	//return -1;//some test can be implemented here later to verify init states
	return 1;
}
