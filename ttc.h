/*
 * ttc.h
 *
 *  Created on: Nov 13, 2018
 *      Author: BJH
 */

#ifndef TTC_H_
#define TTC_H_

//this file contains the relative offsets of the control registers for ttc's;

#define XTTCPS_CLK_CNTRL_OFFSET		0x00000000
#define CLOCK_CONTROL_2				0x00000004
#define CLOCK_CONTROL_3 			0x00000008
#define XTTCPS_CNT_CNTRL_OFFSET 	0x0000000C
#define COUNTER_CONTROL_2			0x00000010
#define COUNTER_CONTROL_3			0x00000014
#define XTTCPS_COUNT_VALUE_OFFSET	0x00000018
#define COUNTER_VALUE_2				0x0000001C
#define COUNTER_VALUE_3				0x00000020
#define XTTCPS_INTERVAL_VAL_OFFSET  0x00000024
#define INTERVAL_COUNTER_2			0x00000028
#define INTERVAL_COUNTER_3			0X0000002C
#define XTTCPS_MATCH_0_OFFSET		0x00000030
#define MATCH_1_COUNTER_2			0x00000034
#define MATCH_1_COUNTER_3			0x00000038
#define XTTCPS_MATCH_1_OFFSET		0x0000003C
#define MATCH_2_COUNTER_2			0x00000040
#define MATCH_2_COUNTER_3			0x00000044
#define XTTCPS_MATCH_2_OFFSET		0x00000048
#define MATCH_3_COUNTER_2			0x0000004C
#define MATCH_3_COUNTER_3			0x00000050
#define XTTCPS_ISR_OFFSET			0x00000054
#define INTERRUPT_REGISTER_2		0x00000058
#define INTERRUPT_REGISTER_3		0x0000005C
#define XTTCPS_IER_OFFSET			0x00000060
#define INTERRUPT_ENABLE_2			0x00000064
#define INTERRUPT_ENABLE_3			0x00000068
#define EVENT_CONTROL_TIMER_1		0x0000006C
#define EVENT_CONTROL_TIMER_2 		0x00000070
#define EVENT_CONTROL_TIMER_3		0x00000074
#define EVENT_REGISTER_1			0x00000078
#define EVENT_REGISTER_2			0x0000007C
#define EVENT_REGISTER_3			0x00000080

/*TIMERCONFIG_1 is a timer configuration object, a filler at this point that contains only a few configuration
 * options
 */

typedef struct{
	unsigned char ID;	/*lower 3 bits denote the hardware this is on. bit 2 indicates ttc module 1 or 0. bit 1..0
 *indicates which of the three sub-timers the instance is on. EXAMPLE: 0b001 is timer_1 of ttc_0
 * EXAMPLE2 0b110 is timer_2 of ttc_1; counting of modules is done from 0*/
	unsigned int tripon; //MSB enables interrupt when '1'. Lower 16 bits are the timer value to trip int at;
	void(*function)(); //points to isr
	unsigned short int* cnt;
	unsigned int status; //bit0:on/off, 1=on;
}TIMERCONFIG_1;

#define ZEROED_TCONF (0, 0, NULL, 0)
TIMERCONFIG_1* gettimer();
void killtimer(TIMERCONFIG_1* pTim);
int configtimer(TIMERCONFIG_1* pTim, unsigned short int sttime, unsigned char resource);
void resettimer(TIMERCONFIG_1* pTim);
int starttimer(TIMERCONFIG_1* pTim);
unsigned short int gettimercnt(TIMERCONFIG_1* pTim);
int inittimer(TIMERCONFIG_1* pTim, unsigned char intr);
int tim_isused(TIMERCONFIG_1* pTim);


#endif /* TTC_H_ */
