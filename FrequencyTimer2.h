 #ifndef _FREQUENCY_TIMER2_H_
 #define _FREQUENCY_TIMER2_H_
 #include <stdint.h>
 #include "Note.h"
 #include "Instrument.h"

// ***************** Timer0A_Init ****************
// Activate Timer0A interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in 12.5ns units
// Outputs: none
void FrequencyTimer2_Init(void);	
void FrequencyTimer2_setNotes(Note* notes);
void FrequencyTimer2_setInstruments(Instrument* instruments);
void FrequencyTimer2_setNum(uint8_t num);
void FrequencyTimer2_getNotes(Note** notes);
void FrequencyTimer2_getInstruments(Instrument** instruments);
void FrequencyTimer2_getPosition(uint8_t* position);
void FrequencyTimer2_arm(uint32_t periodCycles);
void FrequencyTimer2_disarm();
#endif // __TIMER2AINTS_H__
