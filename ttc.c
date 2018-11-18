/*
 * ttc.c
 *
 *  Created on: Nov 13, 2018
 *      Author: BJH
 */

#include "ttc.h"
#include <stdio.h>
#include <stdlib.h>
#include "mmregs.h"



typedef unsigned int u32;
typedef unsigned short int u16;

TIMERCONFIG_1* gettimer(){
	TIMERCONFIG_1* pTim = malloc(sizeof(TIMERCONFIG_1));
    //TIMERCONFIG_1* pTim;
	pTim->ID = 0;
	pTim->function = NULL;
	pTim->status = 0;
	pTim->tripon =0;
	pTim->cnt = 0;

	return pTim;
}
void killtimer(TIMERCONFIG_1* pTim){
	free(pTim);
}
int configtimer(TIMERCONFIG_1* pTim, unsigned short int sttime, unsigned char resource){
	/*resource is which timer resource to use, with 2 sets of 3 available, valid numbers 1-6 starting at tcc0
	 * timer0 going to ttc1 timer2
	 */
	u32 * p;
	if(pTim->ID!=0){
		return -1;//already configured, use other resource or use reconfigtimer function
	}
	pTim->ID = resource;
	pTim->tripon = sttime;
	switch(pTim->ID){
		case 0 :
			return -1;
		case 1 :
			p = (u32*)(TTC_0_BASE + XTTCPS_COUNT_VALUE_OFFSET);
			pTim->cnt = (u16*)p;
			return 1;
		case 2 :
			p = (u32*)(TTC_0_BASE + COUNTER_VALUE_2);
			pTim->cnt = (u16*)p;
			return 1;
		case 3 :
			p = (u32*)(TTC_0_BASE + COUNTER_VALUE_2);
			pTim->cnt = (u16*)p;
			return 1;
		case 4 :
			p = (u32*)(TTC_1_BASE + XTTCPS_COUNT_VALUE_OFFSET);
			pTim->cnt = (u16*)p;
			return 1;
		case 5 :
			p = (u32*)(TTC_1_BASE + COUNTER_VALUE_2);
			pTim->cnt = (u16*)p;
			return 1;
		case 6 :
			p = (u32*)(TTC_1_BASE + COUNTER_VALUE_2);
			pTim->cnt = (u16*)p;
			return 1;
		default :
			return -1;
	}
	//return 0; //success
}
void resettimer(TIMERCONFIG_1* pTim){
	u32* p;
	u32 base;
	if (pTim->ID < 4){
		base = TTC_0_BASE;
		if(pTim->ID == 1){p = (u32*)(base + XTTCPS_CNT_CNTRL_OFFSET);*p = *p|0b10000;}
		else if(pTim->ID == 2){p = (u32*)(base + COUNTER_CONTROL_2);*p = *p|0b10000;}
		else if(pTim->ID == 3){p = (u32*)(base + COUNTER_CONTROL_3);*p = *p|0b10000;}
	}
	if (pTim->ID >3){
		base = TTC_1_BASE;
		if(pTim->ID == 4){p = (u32*)(base + XTTCPS_CNT_CNTRL_OFFSET);*p = *p|0b10000;}
		else if(pTim->ID == 5){p = (u32*)(base + COUNTER_CONTROL_2);*p = *p|0b10000;}
		else if(pTim->ID == 6){p = (u32*)(base + COUNTER_CONTROL_3);*p = *p|0b10000;}
	}
}
int starttimer(TIMERCONFIG_1* pTim){
	u32* p;
	switch(pTim->ID){
	case 0 :
		return -1;
	case 1 :
		p = (u32*)(TTC_0_BASE + XTTCPS_CNT_CNTRL_OFFSET);
		*p = *p&0x11111110;
		return 0;
	case 2 :
		p = (u32*)(TTC_0_BASE + COUNTER_CONTROL_2);
		*p = *p&0x11111110;
		return 0;
	case 3 :
		p = (u32*)(TTC_0_BASE + COUNTER_CONTROL_3);
		*p = *p&0x11111110;
		return 0;
	case 4 :
		p = (u32*)(TTC_1_BASE + XTTCPS_CNT_CNTRL_OFFSET);
		*p = *p&0x11111110;
		return 0;
	case 5 :
		p = (u32*)(TTC_1_BASE + COUNTER_CONTROL_2);
		*p = *p&0x11111110;
		return 0;
	case 6 :
		p = (u32*)(TTC_1_BASE + COUNTER_CONTROL_3);
		*p = *p&0x11111110;
		return 0;
	default :
		return -1;
	}
}
void pausetimer(TIMERCONFIG_1* pTim){

}
__attribute__((always_inline))unsigned short int gettimercnt(TIMERCONFIG_1* pTim){
	return *(pTim->cnt);
}

int inittimer(TIMERCONFIG_1* pTim, unsigned char intr){
	//intr indicates request for interrupt off/on, intr>0 = on
	u32 base;
	u32* p;
	//u32  x;
	if(pTim->ID < 4 ){
		base = TTC_0_BASE;
	}else{
		base = TTC_1_BASE;
	}
	if((pTim->ID == 1)||(pTim->ID == 4)){
		p = (u32*)(base + XTTCPS_CLK_CNTRL_OFFSET);		// internal clk, no prescale
		*p = 0x00000000;
		p = (u32*)(base + XTTCPS_CNT_CNTRL_OFFSET);		// interval mode, output wave off
		*p = 0x00000003;//
		p = (u32*)(base + XTTCPS_INTERVAL_VAL_OFFSET);		//sets count max
		*p = (u32)(pTim->tripon);
		if(intr){
			p = (u32*)(base + XTTCPS_IER_OFFSET);		//interrupt enable
			*p = 0x00000011;
		}else{
			p = (u32*)(base + XTTCPS_IER_OFFSET);		//interrupt disable
			*p = 0x00000000;
		}
	}
    if((pTim->ID == 2)||(pTim->ID == 5)){
		p = (u32*)(base + CLOCK_CONTROL_2);				// internal clk, no prescale
		*p = 0x00000000;
		p = (u32*)(base + COUNTER_CONTROL_2);			// interval mode, output wave off
		*p = 0x00000003;//
		p = (u32*)(base + INTERVAL_COUNTER_2);			//sets count max
		*p = (u32)(pTim->tripon);
		if(intr){
			p = (u32*)(base + INTERRUPT_ENABLE_2);		//interrupt enable
			*p = 0x00000011;
		}else{
			p = (u32*)(base + INTERRUPT_ENABLE_2);		//interrupt disable
			*p = 0x00000000;
		}
	}
    if((pTim->ID == 3)||(pTim->ID == 6)){
		p = (u32*)(base + CLOCK_CONTROL_3);		// internal clk, no prescale
		*p = 0x00000000;
		p = (u32*)(base + COUNTER_CONTROL_3);		// interval mode, output wave off
		*p = 0x00000003;//
		p = (u32*)(base + INTERVAL_COUNTER_3);		//sets count max
		*p = (u32)(pTim->tripon);
		if(intr){
			p = (u32*)(base + INTERRUPT_ENABLE_3);		//interrupt enable
			*p = 0x00000011;
		}else{
			p = (u32*)(base + INTERRUPT_ENABLE_3);		//interrupt disable
			*p = 0x00000000;
		}
	}
    return 1;
}

int tim_isused(TIMERCONFIG_1* pTim){
	if(pTim->ID !=0){
		return 1;
	}
	return 0;
}
/*int reconfigtimer(TIMERCONFIG_1* pTim, unsigned short int sttime, unsigned char resource){
	return 1;
}*/
