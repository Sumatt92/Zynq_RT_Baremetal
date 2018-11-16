/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */
/*****************************************************
Getting Started Guide for Arty-Z7

This demo displays the status of the buttons on the
LEDs and prints a message to the serial communication
when a switch is on.

Terminal Settings:
   -Baud: 115200
   -Data bits: 8
   -Parity: no
   -Stop bits: 1

9/21/17: Created by JPEYRON
****************************************************/

#include <stdio.h>
#include "platform.h"
#include <xgpio.h>
#include "xparameters.h"
#include "sleep.h"

#define BRAM_BASE (0x40000000)	//BRAM
#define ADDRXXX0 (0x41210000)	//axigpio_1L
#define ADDRXXX1 (0x4121FFFF)	//axigpio_1H
#define ADDRXXX2 (0x41200000)	//axigpio_0L
#define ADDRXXX3 (0x4120FFFF)	//axigpio_0H


int main()
{

   XGpio input, output;
   int button_data = 0b00;
   int switch_data = 0;
   unsigned int check0h, check0l, check1h, check1l = 0;
   unsigned int* checkp0h, *checkp0l, *checkp1h, *checkp1l;

   unsigned int *checkblk2 = (unsigned int*)(BRAM_BASE+0x10);
   unsigned int *checkblk = (unsigned int*)(BRAM_BASE+0x1);
/*
   checkp0h = (unsigned int*)(ADDRXXX2+0x0008);	//shoudl contain switch
   checkp0l = (unsigned int*)ADDRXXX2; //should contain btn data
   checkp1h = (unsigned int*)(ADDRXXX0+0x0008);	//should contain null
   checkp1l = (unsigned int*)ADDRXXX0;	//should contain leds
*/

   XGpio_Initialize(&input, XPAR_AXI_GPIO_0_DEVICE_ID);	//initialize input XGpio variable
   XGpio_Initialize(&output, XPAR_AXI_GPIO_1_DEVICE_ID);	//initialize output XGpio variable

   XGpio_SetDataDirection(&input, 1, 0xF);			//set first channel tristate buffer to input
   XGpio_SetDataDirection(&input, 2, 0xF);			//set second channel tristate buffer to input

   XGpio_SetDataDirection(&output, 1, 0x0);		//set first channel tristate buffer to output

   init_platform();

   while(1){

      button_data = XGpio_DiscreteRead(&input, 1);	//get button data

      XGpio_DiscreteWrite(&output, 1, button_data);	//write button data to the LEDs

      //*checkblk2 = 0x40;
      switch_data = XGpio_DiscreteRead(&input, 2);	//get switch data

      //print message dependent on whether one or more buttons are pressed
      if(switch_data == 0b00){} //do nothing

      else if(switch_data == 0b01)
         xil_printf("switch 0 on\n\r");

      else if(switch_data == 0b10)
         xil_printf("switch 1 on\n\r");

      else
         xil_printf("both switches on\n\r");

      usleep(200);			//delay

   }
   cleanup_platform();
   return 0;
}
