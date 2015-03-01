 #ifndef _MIXER_TIMER_H
 #define _MIXER_TIMER_H
 #include <stdint.h>
 #include "Note.h"
 #include "Instrument.h"

// ***************** Timer0A_Init ****************
// Activate Timer0A interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in 12.5ns units
// Outputs: none
void MixerTimer_Init(void);
void MixerTimer_arm(uint32_t periodCycles);
void MixerTimer_disarm();
#endif // __TIMER3AINTS_H__
