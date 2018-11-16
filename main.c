/*
 * main.c
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
#include "ttc.h"


int main(){
	init_platform();
	TIMERCONFIG_1* pTmr0;
	int cnt;


	pTmr0 = gettimer();
	configtimer(pTmr0, 10000, 1);
	inittimer(pTmr0, 0);
	starttimer(pTmr0);
	gettimercnt(pTmr0);
	while(1){
		cnt++;
	}
	cleanup_platform();	//find out what this does
	return 0;
}

