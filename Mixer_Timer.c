#include <stdint.h>
#include <stdlib.h>
#include "inc/tm4c123gh6pm.h"
#include "TempoTimer.h"
#include "FrequencyTimer.h"
#include "FrequencyTimer2.h"
#include "Mixer_Timer.h"
#include "Note.h"
#include "Instrument.h"
#include "MAX5353.h"
#define PF4       (*((volatile uint32_t *)0x40025040))

/*
NOTE: Will always assume melody note has the faster frequency!
*/
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
void (*PeriodicTask3)(void);   // user function

uint32_t magnitude;
Note* melodyNotes;
Note* bassNotes;
Instrument* melodyInstruments;
Instrument* bassInstruments;
uint8_t melodyPos, bassPos;

// ***************** FrequencyTimer_Init ****************
// Activate Timer0A interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in 12.5ns units
// Outputs: none
void MixerTimer_Init(){
	long sr;
  sr = StartCritical(); 
  SYSCTL_RCGCTIMER_R |= 0x08;      // 0) activate timer3
  //TIMER2_CTL_R &= ~0x00000001;     // 1) disable timer0A during setup
	TIMER3_CTL_R = 0x00000000;
  TIMER3_CFG_R = 0x00000000;       // 2) configure for 32-bit timer mode
  TIMER3_TAMR_R = 0x00000002;      // 3) configure for periodic mode, default down-count settings
  TIMER3_TAPR_R = 0;               // 5) 12.5ns timer3A
  TIMER3_ICR_R = 0x00000001;       // 6) clear timer3A timeout flag
	TIMER3_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI8_R = (NVIC_PRI8_R&0x00FFFFFF)|0x80000000; // 8) priority 4
  NVIC_EN1_R = NVIC_EN0_INT3;     // 9) enable interrupt 3 in NVIC
  TIMER3_CTL_R |= 0x00000001;      // 10) enable timer0A
  EndCritical(sr);
}

void MixerTimer_arm(uint32_t periodCycles){
	long sr = StartCritical();
	TIMER3_CTL_R = 0x00000000;
	if (periodCycles != 0){
		TIMER3_TAILR_R = periodCycles-1;    // 4) reload value
	}
  TIMER3_ICR_R = TIMER_ICR_TATOCINT;	// 6) clear timer2A timeout flag
  TIMER3_IMR_R |= 0x00000001;      		// 7) arm timeout interrupt
  TIMER3_CTL_R |= 0x00000001;     		// 8) enable timer2A
	EndCritical(sr);
}

void MixerTimer_disarm() {
	long sr = StartCritical();
  TIMER3_CTL_R &= ~0x00000001;     	// 1) disable timer2A during setup
  TIMER3_IMR_R &= ~0x00000001;      // 7) disarm timeout interrupt
  TIMER3_CTL_R |= 0x00000001;     	// 8) enable timer2A
	EndCritical(sr);
}

void Timer3A_Handler(void){
	TIMER3_ICR_R = TIMER_ICR_TATOCINT;
	static int8_t ind = 0;
	int8_t size = 32;
	ind = (ind + 1) % size;
	FrequencyTimer_getNotes(&melodyNotes);
	FrequencyTimer_getInstruments(&melodyInstruments);
	FrequencyTimer_getPosition(&melodyPos);
	FrequencyTimer2_getNotes(&bassNotes);
	FrequencyTimer2_getInstruments(&bassInstruments);
	FrequencyTimer2_getPosition(&bassPos);
	uint32_t melodyMag = melodyNotes->dynamicPercent * melodyInstruments->waveForm[melodyPos] / 100;
	uint32_t bassMag = bassNotes->dynamicPercent * bassInstruments->waveForm[bassPos] / 100;
	magnitude = (melodyMag + bassMag) / 2;
	DAC_Out(magnitude);
}