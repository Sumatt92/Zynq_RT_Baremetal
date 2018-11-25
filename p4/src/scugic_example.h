/*
 * scugic_example.h
 *
 *  Created on: Nov 24, 2018
 *      Author: BJH
 */

#ifndef SRC_SCUGIC_EXAMPLE_H_
#define SRC_SCUGIC_EXAMPLE_H_

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "einit.h"
#include "ttc.h"
#include "xscugic.h"
#include "xil_types.h"
#include "xparameters.h"
#include "xil_io.h"
#include "xil_exception.h"
#include "xil_cache.h"
#include "mmregs.h"



int SetUpInterruptSystem(XScuGic *XScuGicInstancePtr);
void DeviceDriverHandler(void *CallbackRef, void* int_processed);
int ScuGicExample(u16 DeviceId, XScuGic_Config *GicConfig, XScuGic* InterruptController);

#endif /* SRC_SCUGIC_EXAMPLE_H_ */
