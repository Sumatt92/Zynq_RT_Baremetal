

#include "head_wrap.h"
#include "mmregs.h"
#include "einit.h"
#include "ttc.h"

#define INTC_DEVICE_ID		XPAR_SCUGIC_0_DEVICE_ID
#define INTC_DEVICE_INT_ID	INT_ID_TIMER_1_1

volatile static int InterruptProcessed = FALSE;

void handler(void *CallbackRef);
int main()
{

    init_platform();
    int cnt =0;
    unsigned int * p;
    unsigned short int a=0, b=0;
	static TIMERCONFIG_1* pTmr0;			//Timer config params
	XScuGic InterruptController; 	     /* Instance of the Interrupt Controller */
	static XScuGic_Config *GicConfig;    /* The configuration parameters of the controller */


	pTmr0 = gettimer();
	sethandler(pTmr0, (void*)handler, NULL);
	configtimer(pTmr0, 50000, 1, GicConfig, &InterruptController);
	inittimer(pTmr0, 1);
	a=gettimercnt(pTmr0);

	starttimer(pTmr0);

	while(1){
		cnt++;
		a=gettimercnt(pTmr0);
		a = *(pTmr0->cnt);
		cnt++;
		b=gettimercnt(pTmr0);
		cnt++;
		cnt--;
		int Status;
	}
    cleanup_platform();
    return 0;
}
#ifdef nopers
int ScuGicExample(u16 DeviceId)
{
	int Status;

	GicConfig = XScuGic_LookupConfig(DeviceId);
	if (NULL == GicConfig) {
		return XST_FAILURE;
	}
	Status = XScuGic_CfgInitialize(&InterruptController, GicConfig, GicConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	Status = XScuGic_SelfTest(&InterruptController);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	/*
	 * Setup the Interrupt System
	 */
	Status = SetUpInterruptSystem(&InterruptController);
	/*
	 * Connect a device driver handler that will be called when an
	 * interrupt for the device occurs, the device driver handler performs
	 * the specific interrupt processing for the device
	 */
	Status = XScuGic_Connect(&InterruptController, INTC_DEVICE_INT_ID,
			   (Xil_ExceptionHandler)DeviceDriverHandler,
			   (void *)&InterruptController);

	XScuGic_Enable(&InterruptController, INTC_DEVICE_INT_ID);

	return XST_SUCCESS;
}

/******************************************************************************/
/**
*
* This function connects the interrupt handler of the interrupt controller to
* the processor.  This function is seperate to allow it to be customized for
* each application.  Each processor or RTOS may require unique processing to
* connect the interrupt handler.
*
* @param	XScuGicInstancePtr is the instance of the interrupt controller
*		that needs to be worked on.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
int SetUpInterruptSystem(XScuGic *XScuGicInstancePtr)
{

	/*
	 * Connect the interrupt controller interrupt handler to the hardware
	 * interrupt handling logic in the ARM processor.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler) XScuGic_InterruptHandler,
			XScuGicInstancePtr);

	/*
	 * Enable interrupts in the ARM
	 */
	Xil_ExceptionEnable();

	return XST_SUCCESS;
}

/******************************************************************************/
/**
*
* This function is designed to look like an interrupt handler in a device
* driver. This is typically a 2nd level handler that is called from the
* interrupt controller interrupt handler.  This handler would typically
* perform device specific processing such as reading and writing the registers
* of the device to clear the interrupt condition and pass any data to an
* application using the device driver.  Many drivers already provide this
* handler and the user is not required to create it.
*
* @param	CallbackRef is passed back to the device driver's interrupt
*		handler by the XScuGic driver.  It was given to the XScuGic
*		driver in the XScuGic_Connect() function call.  It is typically
*		a pointer to the device driver instance variable.
*		In this example, we do not care about the callback
*		reference, so we passed it a 0 when connecting the handler to
*		the XScuGic driver and we make no use of it here.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void DeviceDriverHandler(void *CallbackRef)
{
	/*
	 * Indicate the interrupt has been processed using a shared variable
	 */
	InterruptProcessed = TRUE;
}
#endif
void handler(void *CallbackRef){
	/*
	 * Indicate the interrupt has been processed using a shared variable
	 */
	InterruptProcessed = TRUE;
}
