# Explore_Zync
## Overview    
The aim of this project is to explore features of the xilinx zync z7020 running bare metal. This repository will focus on C source created in the SDK rather than the HDL/bitstream aspect of the project. 
The focus will be primarily on real time control applications and the peripherals commonly used in those applications. 

This repository should be able to serve as a starting point for engineers looking to create their own real-time control systems employing the Zync. To ensure this it is very important to make sure that this repo is rigidly and simply structured. Beyond version controll it should contain documentation, links and other resources for zync developers.
Further, this repository will serve as an exploration of github.

## Navigating This Repository  
The basic repository contents should be described in [repo_structure](
        https://github.com/Sumatt92/zynq_power_control_1/blob/master_v2/repository_structure.md
      )

## Specifics
**Hardware**  
The HW this code is being executed on is a developement board, the Arty z7 from digilent, programmed via usb.
Additional hardware will be added as needed to support the developement of peripheral drivers.

**RTL/Bitstream/VHDL**
A significant portion of the code for this project will be RTL or HDL developed in the vivado design suite.This will be included although
it may not be organized until a later time. That is to say, at present there is not a clear idea of how to contain and present those files
in this repository so they may not be as structured as the c source code. This should be remedied at a future time.  

**Peripherals/Drivers**
This project should serve as an example of the use of the following drivers/peripherals and functionality:
*  UART (rs232 or generic 232-esq serial w/o handshake)
*  Timers
*  A variety of interrelated interrupts driving real-time behaviour 
*  SPI running >=6mhz
*  QSPI flash use, including boot
*  Tightly coupled acceleration of PS with PL fabric
*  Less-tightly coupled PL logic that offloads certain tasks from the PS (pwm and/or hysteretic control of external system)
*  Manipulation of cacheing to improve determinacy of certain real-time tasks (non-cached or always cached data/instructions)
*  Use of a medium-speed off-board communication protocol, most likely 100mbit ethernet
*  Real-time control of a high speed power electronics, either SMPS or 3ph motor drive
*  Filtering and processing of ADC data, both from onboard ADC and a high-speed external ADC

## Status
11/22/2018  
A bitstream has been generated from a block diagram built in the ip integrator of vivado. This presently contains the ps (a9's), an axi to gpio interface, an axi to block memory interface, a block memory generator and a small piece of vhdl wrapped into a block symbol. The vdhl simply writes a test value into the block memory for the hps to read through an axi-block_memory interface. This could serve as a medium bandwith channel of communication between the hard processor and a large piece of custom logic in the PL. 
![block diagram](https://github.com/Sumatt92/Zynq_RT_Baremetal/blob/master_v2/block_1.jpg)

The bitstream has been exported to the SDK. A bsp package has been auto-generated. The main function is defined in a file called helloworld.c . The current revision is called p4, using p4_bsp and basline_1_wrapper_hw_platform_1. The main function is a test of the interrupt controller driver (the GIC, generic interrupt controller), and the ttc (a timer). The timer triggers an interrupt which is then offloaded to a defined handler. 

The timer is controlled by a custom driver whereas the GIC is operated through the xilinx driver. The main file is largely copy+pasted from the example code [xscugic_example.c](https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/scugic/examples/xscugic_example.c).


## Useful Files
  * [repo_structure](
        https://github.com/Sumatt92/zynq_power_control_1/blob/master_v2/repository_structure.md
      )

