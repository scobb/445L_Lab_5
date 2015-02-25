// Timer0A.c
// Runs on LM4F120/TM4C123
// Use Timer0A in periodic mode to request interrupts at a particular
// period.
// Daniel Valvano
// September 11, 2013

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers"
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2013
   Volume 1, Program 9.8

  "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013
   Volume 2, Program 7.5, example 7.6

 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
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
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "TempoTimer.h"
#include "FrequencyTimer.h"
#define PF4       (*((volatile uint32_t *)0x40025040))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
void (*PeriodicTask)(void);   // user function

// ***************** FrequencyTimer_Init ****************
// Activate Timer0A interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in 12.5ns units
// Outputs: none
void FrequencyTimer_Init(){
	long sr;
  sr = StartCritical(); 
  SYSCTL_RCGCTIMER_R |= 0x01;      // 0) activate timer0
  TIMER0_CTL_R &= ~0x00000001;     // 1) disable timer0A during setup
  TIMER0_CFG_R = 0x00000000;       // 2) configure for 32-bit timer mode
  TIMER0_TAMR_R = 0x00000002;      // 3) configure for periodic mode, default down-count settings
  TIMER0_TAPR_R = 0;               // 5) 12.5ns timer0A
  TIMER0_ICR_R = 0x00000001;       // 6) clear timer0A timeout flag
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x60000000; // 8) priority 3
  NVIC_EN0_R = NVIC_EN0_INT19;     // 9) enable interrupt 19 in NVIC
  TIMER0_CTL_R |= 0x00000001;      // 10) enable timer0A
  EndCritical(sr);
}
// TODO - this approach or pass the handler?
void FrequencyTimer_arm(uint32_t periodCycles){
	long sr = StartCritical();
  TIMER0_CTL_R &= ~0x00000001;     		// 1) disable timer0A during setup
  TIMER0_TAILR_R = periodCycles-1;    // 4) reload value
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;	// 6) clear timer0A timeout flag
  TIMER0_IMR_R |= 0x00000001;      		// 7) arm timeout interrupt
  TIMER0_CTL_R |= 0x00000001;     		// 8) enable timer0A
	EndCritical(sr);
}

void FrequencyTimer_disarm() {
	long sr = StartCritical();
  TIMER0_CTL_R &= ~0x00000001;     	// 1) disable timer0A during setup
  TIMER0_IMR_R &= ~0x00000001;      // 7) disarm timeout interrupt
  TIMER0_CTL_R |= 0x00000001;     	// 8) enable timer0A
	EndCritical(sr);
}
	

void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// acknowledge timer0A timeout
	// step through the array, send the Speaker the right value
}