#include "TempoTimer.h"
#include "inc/tm4c123gh6pm.h"
#include "MusicDriver.h"
#include "FrequencyTimer.h"
#include "FrequencyTimer2.h"
#include "Mixer_Timer.h"
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

void (*HeartbeatTask)(void);   // user function
void TempoTimer_Init(uint32_t period){long sr; int delay;
  sr = StartCritical(); 
  SYSCTL_RCGCTIMER_R |= 0x02;      // 0) activate TIMER1
  // Timer1AFunction = task;             // user function (this line also allows time to finish activating)
	delay = 1;
  TIMER1_CTL_R &= ~0x00000001;     // 1) disable TIMER1A during setup
  TIMER1_CFG_R = 0x00000000;       // 2) configure for 32-bit timer mode
  TIMER1_TAMR_R = 0x00000002;      // 3) configure for periodic mode, default down-count settings
  TIMER1_TAILR_R = period-1;       // 4) reload value
  TIMER1_TAPR_R = 0;               // 5) 12.5ns TIMER1A
  TIMER1_ICR_R = 0x00000001;       // 6) clear TIMER1A timeout flag
  // TIMER1_IMR_R |= 0x00000001;      // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFF1FFF)|0x00004000; // 8) priority 2
  NVIC_EN0_R |= NVIC_EN0_INT21;     // 9) enable interrupt 19 in NVIC
  TIMER1_CTL_R |= 0x00000001;      // 10) enable TIMER1A
  EndCritical(sr);
}
void TempoTimer_setHeartbeatTask(void(*task)(void)){
	HeartbeatTask = task;
}

void TempoTimer_disarm(){
	long sr = StartCritical();
  TIMER1_CTL_R &= ~0x00000001;     // 1) disable TIMER1A during setup
  TIMER1_IMR_R &= ~(0x00000001);      // 7) disarm timeout interrupt
  TIMER1_CTL_R |= 0x00000001;      // 10) enable TIMER1A
	EndCritical(sr);
}

void TempoTimer_arm(){
	long sr = StartCritical();
  TIMER1_CTL_R &= ~0x00000001;     // 1) disable TIMER1A during setup
  TIMER1_IMR_R |= 0x00000001;      // 7) arm timeout interrupt
  TIMER1_CTL_R |= 0x00000001;      // 10) enable TIMER1A
	EndCritical(sr);
}

void Timer1A_Handler(void){
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER1A timeout
	long sr;
	if (HeartbeatTask){
		(*HeartbeatTask)();
	}
	Note* currentNote;
	Note* currentBassNote;
	Instrument* currentInstrument;
	Instrument* currentBassInstrument;
	sr = StartCritical();
	MusicDriver_getMelody(&currentNote, &currentInstrument);
	MusicDriver_getBass(&currentBassNote, &currentBassInstrument);
	FrequencyTimer_setNotes(currentNote);
	FrequencyTimer_setInstruments(currentInstrument);
	FrequencyTimer_setNum(1);
	FrequencyTimer2_setNotes(currentBassNote);
	FrequencyTimer2_setInstruments(currentBassInstrument);
	FrequencyTimer2_setNum(1);
	EndCritical(sr);
	FrequencyTimer_arm(currentNote->periodCycles);
	FrequencyTimer2_arm(currentBassNote->periodCycles);
	MixerTimer_arm((currentNote->periodCycles)*2);
}