// MAX5353TestMain.c
// Runs on LM4F120/TM4C123
// Test the functions provided in MAX5353.c by outputting
// a sine wave at a particular frequency.
// Daniel Valvano
// September 11, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

 Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// SSI0Clk (SCLK, pin 4) connected to PA2
// SSI0Fss (!CS, pin 2) connected to PA3
// SSI0Tx (DIN, pin 3) connected to PA5
// see Figure 7.19 for complete schematic
#include <stdint.h>

#include "MAX5353.h"
#include "SysTick.h"
#include "ButtonManager.h"
#include "FrequencyTimer.h"
#include "TempoTimer.h"
#include "Heartbeat.h"
#include "PLL.h"
#include "Note.h"
#define MAX 4095
// define the period at 120 beats per minute, refreshing each 12th note
#define PERIOD_BPM_120_12 3333333
// 12-bit 32-element sine wave
// multiply each value by 2 to shift into bits 12:1 of SSI packet
// three control bits in 15:13 are all zero for immediate DAC update
// book figure shows MAX5353 in unipolar rail-to-rail configuration
// that means when wave[n] = 0x0000 (LSB = 0), output = 0
//                 wave[n] = 0x1000 (LSB = 0), output = Vref
//                 wave[n] = 0x1FFE (LSB = 0), output = 2*Vref

int main(void){
	// SysTick_Init();
	PLL_Init();
	Heartbeat_Init();
	//ButtonManager_Init();
	FrequencyTimer_Init();
	TempoTimer_Init(PERIOD_BPM_120_12);
	DAC_Init(MAX/2);
	FrequencyTimer_arm(C5);
	while (1);
}
