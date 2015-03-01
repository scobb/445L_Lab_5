#include <stdint.h>
#include <stdlib.h>
#include "inc/tm4c123gh6pm.h"
#include "TempoTimer.h"
#include "FrequencyTimer2.h"
#include "Note.h"
#include "Instrument.h"
#include "MAX5353.h"
#define PF4       (*((volatile uint32_t *)0x40025040))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
void (*PeriodicTask2)(void);   // user function
Note* myNote2;
Instrument* myInstrument2;
uint8_t myNum2;

// ***************** FrequencyTimer_Init ****************
// Activate Timer0A interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in 12.5ns units
// Outputs: none
void FrequencyTimer2_Init(){
	long sr;
  sr = StartCritical(); 
  SYSCTL_RCGCTIMER_R |= 0x04;      // 0) activate timer2
  //TIMER2_CTL_R &= ~0x00000001;     // 1) disable timer0A during setup
	TIMER2_CTL_R = 0x00000000;
  TIMER2_CFG_R = 0x00000000;       // 2) configure for 32-bit timer mode
  TIMER2_TAMR_R = 0x00000002;      // 3) configure for periodic mode, default down-count settings
  TIMER2_TAPR_R = 0;               // 5) 12.5ns timer2A
  TIMER2_ICR_R = 0x00000001;       // 6) clear timer2A timeout flag
	TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x60000000; // 8) priority 3
  NVIC_EN0_R = NVIC_EN0_INT23;     // 9) enable interrupt 23 in NVIC
  TIMER2_CTL_R |= 0x00000001;      // 10) enable timer2A
  EndCritical(sr);
}

void FrequencyTimer2_arm(uint32_t periodCycles){
	long sr = StartCritical();
  //TIMER2_CTL_R &= ~0x00000001;     		// 1) disable timer2A during setup
	TIMER2_CTL_R = 0x00000000;
	if (periodCycles != 0){
		TIMER2_TAILR_R = periodCycles-1;    // 4) reload value
	}
  TIMER2_ICR_R = TIMER_ICR_TATOCINT;	// 6) clear timer2A timeout flag
  TIMER2_IMR_R |= 0x00000001;      		// 7) arm timeout interrupt
  TIMER2_CTL_R |= 0x00000001;     		// 8) enable timer2A
	EndCritical(sr);
}

void FrequencyTimer2_disarm() {
	long sr = StartCritical();
  TIMER2_CTL_R &= ~0x00000001;     	// 1) disable timer2A during setup
  TIMER2_IMR_R &= ~0x00000001;      // 7) disarm timeout interrupt
  TIMER2_CTL_R |= 0x00000001;     	// 8) enable timer2A
	EndCritical(sr);
}

void FrequencyTimer2_setNotes(Note* notes){
	myNote2 = notes;
}
void FrequencyTimer2_setInstruments(Instrument* instruments){
	myInstrument2 = instruments;
}
void FrequencyTimer2_setNum(uint8_t num){
	myNum2 = num;
}

void FrequencyTimer2_getNotes(Note** notes){
	*notes = myNote2;
}

void FrequencyTimer2_getInstruments(Instrument** instruments){
	*instruments = myInstrument2;
}

void Timer2A_Handler(void){
  TIMER2_ICR_R = TIMER_ICR_TATOCINT;// acknowledge timer2A timeout
	// two(notes[0].periodCycles, notes[1].periodCycles);
	static int8_t ind = 0;
	int8_t size = 32;
	ind = (ind + 1) % size;
	DAC_Out(myNote2->dynamicPercent * myInstrument2->waveForm[ind] / 100);
}